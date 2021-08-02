# 从零入门的NVIDIA Jetson Nano之旅

[toc]

------

## 写在前面

第一次接触边缘计算设备，不同于资料众多普及广泛的[树莓派](https://www.raspberrypi.org)，[NVIDIA Jetson](https://www.nvidia.cn/autonomous-machines/embedded-systems/)系列的入门级设备[Nano](https://www.nvidia.cn/autonomous-machines/embedded-systems/jetson-nano/)拥有GPU计算能力和NVIDIA系GPU的属性，可以提供更干净、更亲眼所见的环境和GPU使用体验

在不到两个月的玩耍时间中，一点点的探索小家伙的能力，总结了一些简单的新手入门之路，在此分享

仓库后一部分将我使用Nano所尝试的事情做下总结，主要包括一些配置和在目标识别、PCL、ROS等方面的简单实验

> 除了本仓库，我还在[知乎专栏](https://www.zhihu.com/column/c_1332045298588737536)中分享NVIDIA Jetson Nano的一些内容

<br/>

## 新手入门

强烈推荐大家在拿到Nano的第一天先读下这篇文章[NVIDIA Jetson Nano新手手册：一场当没有人告诉你该做什么你要能够知道该做什么的无畏冒险](https://cloud.tencent.com/developer/article/1425189)，你会对它能干什么以及每一步大致要怎么走有一个基础印象，除此之外，还有一些资源强烈推荐：

-  **linux论坛Nano博客**：[Jetson Nano - eLinux.org](https://www.elinux.org/Jetson_Nano)
-  **常见问题汇总**：[关于 NVDIA Jetson NANO常见问题汇总](https://cloud.tencent.com/developer/article/1514453)
- **NVIDIA Jetson Nano论坛**：[Latest Jetson Nano topics - NVIDIA Developer Forums](https://forums.developer.nvidia.com/c/agx-autonomous-machines/jetson-embedded-systems/jetson-nano/76)

而其中我最推荐给你的是[🌟Jetson社区创新项目](https://developer.nvidia.com/embedded/community/jetson-projects#bee_saving_tree)，社区中是各路大神用Jetson打造的创新项目，CV、机器人、无人机、无人车、甚至是带娃神器应有尽有，随便截一张图如下：

<div align="center"><img src="https://doublez-site-bed.oss-cn-shanghai.aliyuncs.com/img/20210731202032.png" width="50%;" /></div>

<br/>

## 我的实践

### 配置文档

- [从零开始配置NVIDIA Jetson Nano(踩坑史)](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/setup/setup.md)
- [JetPack — 边缘计算设备构建AI应用全面解决方案](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/doc/jetpack.md)
- [Jetson Nano安装pycuda(踩坑传)](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/doc/pycuda.md)
- [Jetson Nano边缘计算最佳实践：jetson-inference](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/experiment/jetson-inference.md)

### 实验

- **基于Yolo的目标识别**
  - [Jetson Nano 使用Yolov3进行目标检测](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/experiment/yolov3.md)
  - [Jetson Nano使用TensorRT加速yolov3-tiny目标识别](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/experiment/trt-yolov3.md)
- **PCL**
  - [Jetson Nano安装PCL(Point Cloud Library)库](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/PCL/install.md)
  - [PCL库点云可视化与重建实例](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/PCL/README.md)
- **ROS**
  - [Jetson Nano安装ROS，有你想知道的所有填坑方法(自信)](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/ROS/install.md)
  - [解决ROS配置中cv_bridge问题](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/doc/cv_bridge-solver.md)
  - [Jetson Nano配置ROS在rviz上显示自定义轨迹](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/tree/master/ROS/rviz/showpath)
  - [FLOAM_ssl整合点云重建定制化](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/tree/master/ROS/FLOAM_ssl)
  - [Linux配置S-PTAM环境](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/tree/master/ROS/SPTAM)

<br/>

## 关于作者

| 姓名 \| Name👤            | 张喆 \| doubleZ                                              |
| ------------------------ | ------------------------------------------------------------ |
| 学校 \| University🏫      | 同济大学 \| Tongji Univ.                                     |
| 实验环境 \| Environment💼 | 创乐（上海）信息科技有限公司 \| Invix                        |
| 联系方式 \| Email✉️       | [doublez@alumni.tongji.edu.cn](mailto:doublez@alumni.tongji.edu.cn) |

![image-20210111192053545](README.assets/image-20210111192053545.png)

