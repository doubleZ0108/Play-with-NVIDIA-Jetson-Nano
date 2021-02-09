# Jetson Nano安装PCL(Point Cloud Library)库

1. 预装依赖库
```bash
sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
sudo apt-get update
sudo apt-get install libpcl-dev
```
> 注意：如果第三步install的是libpcl-all，会提示无法定位软件包libpcl-all；
> update可能会出错，提示：PPA仓库没有Release文件，这个问题可以忽略；
> 如果install失败，可以再执行一次update，然后install；

2. 安装PCL库
PCL有实时更新的trunk版本，也有Release版本，可择其一安装，trunk版本可能不够稳定，这里采用直接安装PCL Release版本[Releases · PointCloudLibrary/pcl · GitHub](https://github.com/PointCloudLibrary/pcl/releases)
下载后进行解压: `tar -xvf source.tar`
```bash
cd pcl && mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j2
sudo make -j2 install
```
> 必须吐槽，`make -j2`我从上午十点执行到下午4点，2G内存的nano是真的伤，好在安装过程中没有什么报错，心态才没炸
> 学长说不要用j2，直接跑`make`，内存和CPU的抉择还是要充足一点的内存orz，没亲自实践，不知道会不会效果好一点

3. 测试PCL
可以直接使用我学习时整理好的四个经典例程 [PCL实例](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/tree/master/PCL)

如果想自己摸索⬇️
我是用的是《点云库PCL学习教程》中的例程，clone下边的仓库
[GitHub - LiveStockShapeAnalysis/Point-Cloud-Processing-example: 点云库PCL从入门到精通 书中配套案例](https://github.com/LiveStockShapeAnalysis/Point-Cloud-Processing-example)
随便进入一个有`.cpp`的文件夹（要看运气的，有些例程跑不起来）
> 推荐第五章
> 1. cloud_viewer
> 4. plotter
```bash
mkdir build && cd build
cmake ..
make
```

> 第五章3pcl_visualizer_demo编译会报错
> 我直接把最后boost thread的部分注释掉，成功运行了
> 附一个PCL运行程序报错的解决方法博客
> [pcl_visualizer_demo解决undefined reference to ‘boost::this_thread::hiden::sleep_until(timespec const$_Dbojuedzw的博客-CSDN博客](https://blog.csdn.net/Dbojuedzw/article/details/105396024)

## Resources
- [Ubuntu 下 Point Cloud Library （PCL)安装_摸着石头撑船-CSDN博客](https://blog.csdn.net/luohuiwu/article/details/80722082)
