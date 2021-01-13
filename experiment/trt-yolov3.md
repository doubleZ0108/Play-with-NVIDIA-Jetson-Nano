# Jetson Nano使用TensorRT加速yolov3-tiny目标识别
[toc]

------

## 环境配置
- 安装protobuf
```bash
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple protobuf==3.8.0
```
- 安装onnx
```bash
sudo apt-get install protobuf-compiler libprotoc-dev 
```
- 安装pillow
```bash
sudo pip3 install Pillow
```
- 安装pycuda：如果下述脚本无法安装，请看[[Jetson Nano安装pycuda(踩坑传)]]
```bash
export PATH=/usr/local/cuda/bin:\${PATH}
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:\${LD_LIBRARY_PATH}
sudo pip3 install pycuda
```
- 安装numpy
```bash
sudo pip3 install numpy
```

---

## 运行TRT-yolov3
> 📦[Github: TRT-yolov3](https://github.com/yqlbu/TRT-yolov3)

1. 下载配置文件和权重文件到`TRT-yolov3/yolov3_onnx/`中
	1. [https://objectstorage.ca-toronto-1.oraclecloud.com/n/yzpqsgba6ssd/b/bucket-20200425-1646-weights/o/yolov3-tiny.cfg](https://objectstorage.ca-toronto-1.oraclecloud.com/n/yzpqsgba6ssd/b/bucket-20200425-1646-weights/o/yolov3-tiny.cfg) 
	2. [https://hidden-boat-623a.keviny-cloud.workers.dev/DeepLearning/yolov3-weights/yolov3-tiny.weights](https://hidden-boat-623a.keviny-cloud.workers.dev/DeepLearning/yolov3-weights/yolov3-tiny.weights) 
> 也可以使用`TRT-yolov3/yolov3_onnx/download.sh`进行下载 或 查看该文件有选择性的下载（你懂的，异常缓慢，记得自己找办法加速，我帮你找好了两个）
2. 修改`download.sh`文件，只保留如下部分，执行该脚本`sudo ./download.sh`
```shell
#!/bin/bash

set -e

echo
echo "Creating YOLOv3-Tiny-288 and YOLOv3-Tiny-416 configs..."
cat yolov3-tiny.cfg | sed -e '8s/width=416/width=288/' | sed -e '9s/height=416/height=288/' > yolov3-tiny-288.cfg
echo >> yolov3-tiny-288.cfg
ln -sf yolov3-tiny.weights yolov3-tiny-288.weights
cp yolov3-tiny.cfg yolov3-tiny-416.cfg
echo >> yolov3-tiny-416.cfg
ln -sf yolov3-tiny.weights yolov3-tiny-416.weights

echo
echo "Done."
```
> 以下只以`yolov3-tiny-416为例`，这两个步骤都比较慢 请耐心等待
3. 将`.cfg`转换为`.onnx`
```bash
python3 yolov3_to_onnx.py --model yolov3-tiny-416
```
4. 将`.onnx`转换为`.trt`
```bash
python3 onnx_to_tensorrt.py --model yolov3-tiny-416
```
---

## 测试(识别)
【视频】
```bash
python3 detector.py --file --filename data/test.mp4 --model yolov3-tiny-416 --runtime
```
![](https://doublez-site-bed.oss-cn-shanghai.aliyuncs.com/img/20210113162003.png)

【摄像头】
将[trt-yolov3-detector-camera.py](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/script/trt-yolov3-detector-camera.py)脚本放到`TRT-yolov3/`目录下，并更换第十行的绝对路径
直接执行该脚本即可调用摄像头进行识别了

---
## 模型替换(详细)
> 如果TRT-yolov3已经成功跑通则理论上可以跳过着part，这part是我自己踩坑的过程中，在发现TRT-yolov3项目之前找到模型转换方法的部分分解动作，如果想更详细的一步步了解如何从`.cfg`转化到`.trt`的，可以继续阅读

核心思想是将yolo原始的`.cfg`配置文件转换为TensorRT要用的`.trt`文件

### yolov3-tiny -> onnx
1. 创建[yolov3_tiny_to_onnx.py](https://github.com/yqlbu/TRT-yolov3/blob/master/yolov3_onnx/yolov3_to_onnx.py)文件
2. 准备模型配置`.cfg`文件和权重`.weights`文件在该py脚本同一目录
> 我采用的是直接将`yolov3-tiny`两个文件重新命名
> 两文件需同名，例如`yolov3-tiny-416.cfg`和`yolov3-tiny-416.weights`
4. 执行如下脚本生成`.onnx`模型配置文件
```bash
python3 yolov3_tiny_to_onnx.py --model yolov3-tiny-416
```

【关于这里`.cfg`的说明】
> 我将原始的py文件进行了一点修改，原始py只能读取288、416、608层的配置文件，这里删除了这个限制，但暂时不清楚会有什么问题
> 但是cfg文件仍然有一定的格式约束
1. 每层之间只有一个空行
```cfg
[convolutional]
batch_normalize=1

[maxpool]
size=2
```
2. 第一层[net]中最后两项更改为
```cfg
steps=400000
scales=.1
```
3. 该cfg文件结尾有且仅有两行空行
![](https://doublez-site-bed.oss-cn-shanghai.aliyuncs.com/img/20210113162017.png)

### onnx -> trt
1. 创建[onnx_to_tensorrt.py](https://github.com/yqlbu/TRT-yolov3/blob/master/yolov3_onnx/onnx_to_tensorrt.py)文件
2. 执行如下脚本，生成`.trt`模型文件
```bash
python3 onnx_to_tensorrt.py —model yolov3-tiny-416
```

---
## Resource
* [Jetson Nano 使用yolov3-tiny及TensorRT加速，达到接近实时目标检测与识别_云逸的博客-CSDN博客](https://blog.csdn.net/weixin_43562948/article/details/104724461)
* [trt-yolov3:Jetson Nano上的yolov3-tiny识别（已完结）_我总饿肚子的博客-CSDN博客](https://blog.csdn.net/qq_36780295/article/details/108496746)
* 自己没有详细看，但从头到尾的逻辑比较清晰：[（超详细）用TensorRT加速yolov3-tiny,加速后3ms/帧_面对疾风吧~的博客-CSDN博客](https://blog.csdn.net/qq_43229471/article/details/103084715)