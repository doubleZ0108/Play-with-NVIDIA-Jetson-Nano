import numpy as np
import pycuda.autoinit
import pycuda.driver as cuda
from pycuda.compiler import SourceModule


mod = SourceModule("""
#define BLOCK_SIZE 16

typedef struct {
    int width;
    int height;
    int stride; 
    int __padding;    //为了和64位的elements指针对齐
    float* elements;
} Matrix;

// 读取矩阵元素
__device__ float GetElement(const Matrix A, int row, int col)
{
    return A.elements[row * A.stride + col];
}

// 赋值矩阵元素
__device__ void SetElement(Matrix A, int row, int col, float value)
{
    A.elements[row * A.stride + col] = value;
}

// 获取 16x16 的子矩阵
 __device__ Matrix GetSubMatrix(Matrix A, int row, int col) 
{
    Matrix Asub;
    Asub.width    = BLOCK_SIZE;
    Asub.height   = BLOCK_SIZE;
    Asub.stride   = A.stride;
    Asub.elements = &A.elements[A.stride * BLOCK_SIZE * row + BLOCK_SIZE * col];
    return Asub;
}

__global__ void matrix_mul(Matrix *A, Matrix *B, Matrix *C)
{
    int blockRow = blockIdx.y;
    int blockCol = blockIdx.x;
    int row = threadIdx.y;
    int col = threadIdx.x;

    Matrix Csub = GetSubMatrix(*C, blockRow, blockCol);

    // 每个线程通过累加Cvalue计算Csub的一个值
    float Cvalue = 0;

    // 为了计算Csub遍历所有需要的Asub和Bsub
    for (int m = 0; m < (A->width / BLOCK_SIZE); ++m) 
    {
        Matrix Asub = GetSubMatrix(*A, blockRow, m);
        Matrix Bsub = GetSubMatrix(*B, m, blockCol);
 
        __shared__ float As[BLOCK_SIZE][BLOCK_SIZE];
        __shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];
       
        As[row][col] = GetElement(Asub, row, col);
        Bs[row][col] = GetElement(Bsub, row, col);

        __syncthreads();
        
        for (int e = 0; e < BLOCK_SIZE; ++e)
            Cvalue += As[row][e] * Bs[e][col];

        __syncthreads();
    }

    SetElement(Csub, row, col, Cvalue);
}
""")


class MatrixStruct(object):
    def __init__(self, array):
        self._cptr = None

        self.shape, self.dtype = array.shape, array.dtype
        self.width = np.int32(self.shape[1])
        self.height = np.int32(self.shape[0])
        self.stride = self.width
        self.elements = cuda.to_device(array)                      # 分配内存并拷贝数组数据至device，返回其地址

    def send_to_gpu(self):
        self._cptr = cuda.mem_alloc(self.nbytes())                 # 分配一个C结构体所占的内存
        cuda.memcpy_htod(int(self._cptr), self.width.tobytes())    # 拷贝数据至device，下同
        cuda.memcpy_htod(int(self._cptr)+4, self.height.tobytes())
        cuda.memcpy_htod(int(self._cptr)+8, self.stride.tobytes())
        cuda.memcpy_htod(int(self._cptr)+16, np.intp(int(self.elements)).tobytes())

    def get_from_gpu(self):
        return cuda.from_device(self.elements, self.shape, self.dtype)  # 从device取回数组数据
   
    def nbytes(self):
        return self.width.nbytes * 4 + np.intp(0).nbytes


a = np.random.randn(400,400).astype(np.float32)
b = np.random.randn(400,400).astype(np.float32)
c = np.zeros_like(a)

A = MatrixStruct(a)
B = MatrixStruct(b)
C = MatrixStruct(c)
A.send_to_gpu()
B.send_to_gpu()
C.send_to_gpu()

matrix_mul = mod.get_function("matrix_mul")
matrix_mul(A._cptr, B._cptr, C._cptr, block=(16,16,1), grid=(25,25))
result = C.get_from_gpu()
print(np.dot(a,b))
print(result)


