# Jetson Nano安装pycuda(踩坑传)
[toc]

------

## 脚本自动安装
先使用如下脚本进行安装，如果成功则万事大吉，如果报错请继续往下看
> 我自己配置的时候遇到两种错误
> - 执行完前两行后所有指令都无法使用：sudo, ls, pip…
> - 运行错误（红色）
```bash
export PATH=/usr/local/cuda/bin:\${PATH}
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:\${LD_LIBRARY_PATH}
sudo pip3 install pycuda
```

## 手动安装
1. 请先确保`nvcc -V`正确输出
2. 下载[pycuda](https://files.pythonhosted.org/packages/5e/3f/5658c38579b41866ba21ee1b5020b8225cec86fe717e4b1c5c972de0a33c/pycuda-2019.1.2.tar.gz)源码
3. 解压文件并编译（这里等待的时间比较长）
```bash
tar zxvf pycuda-2019.1.2.tar.gz    
cd pycuda-2019.1.2/  
python3 configure.py --cuda-root=/usr/local/cuda-10.2
sudo python3 setup.py install
```
3. 如果出现如下的提示则证明安装成功
```bash
Installed /usr/local/lib/python3.6/dist-packages/pycuda-2019.1.2-py3.6-linux-aarch64.egg
Processing dependencies for pycuda==2019.1.2
Searching for pytools==2021.1
Best match: pytools 2021.1
Adding pytools 2021.1 to easy-install.pth file

......

Using /usr/lib/python3/dist-packages
Searching for dataclasses==0.8
Best match: dataclasses 0.8
Adding dataclasses 0.8 to easy-install.pth file

Using /usr/local/lib/python3.6/dist-packages
Finished processing dependencies for pycuda==2019.1.2
```

## 验证pycuda是否安装成功
运行：[test-pycuda.py](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/script/test-pycuda.py)，如果输出矩阵结果则安装正确


## Resources
- [jetson nano安装pycuda！！！_帅的发光发亮的博客-CSDN博客](https://blog.csdn.net/weixin_44501699/article/details/106470671)
- 另一种解决pycuda和onnx安装错误的帖子（我自己是没看就完成配置的）[报错：error while loading shared libraries: libprotoc.so.19_我总饿肚子的博客-CSDN博客](https://blog.csdn.net/qq_36780295/article/details/108489483)