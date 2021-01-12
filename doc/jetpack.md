# JetPack — 边缘计算设备构建AI应用全面解决方案
[JetPack SDK | NVIDIA Developer](https://developer.nvidia.com/zh-cn/embedded/jetpack)

NVIDIA JetPack SDK是构建AI应用的全方面解决方案。
> 包含适用于 Linux 操作系统的最新 Linux 驱动包 (L4T) 以及用于深度学习、计算机视觉、加速计算和多媒体的 CUDA-X 加速库与 API。



- **操作系统**：Linux内核、NVIDIA驱动、其他固件etc
- **TensorRT**：用于图像处理、分割和物体检测神经网络的高性能深度学习 ~推理运行时~，是NVIDIA依托于CUDA构建的并行编程模型(亲儿子)，更低延时更高吞吐量
- **cuDNN**：高性能基元，大幅优化标准例程(例如用于前向传播和反向传播的卷积层、池化层、归一化层和激活层)
- **CUDA**：C/C++构建GPU应用的全面开发环境，包括针对NVIDIA GPU的编译器、调试和优化应用性能的工具etc
- **多媒体API**
	- 摄像头API
	- 传感器驱动API
- **计算机视觉**
	- VisionWorks
	- OpenCV
	- VPI视觉编程接口
- 开发者工具等