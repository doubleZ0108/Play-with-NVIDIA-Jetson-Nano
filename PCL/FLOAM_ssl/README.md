# FLOAM_ssl中整合点云三角化重建

原项目repo：https://github.com/wh200720041/FLOAM_ssl

## 如何修改并运行
主要修改 `src/octoMappingNode.cpp`文件
修改完按照如下代码重新编译并运行
```bash
# cd catkin_wk/

## compile
rm -rf build
catkin_make -j2
source devel/setup.bash

## launch
roslaunch floam_ssl floam_ssl_octo_mapping.launch
```

## 整合点云三角化代码
将[FLOAM_ssl/cloud_visualization.cpp](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/PCL/FLOAM_ssl/cloud_visualization.cpp) 放入`src/octoMappingNode.cpp`文件，重新编译运行

### 基本步骤
1. 将原始PointXYZRGB 格式转化为PointXYZ（暂时去除了颜色数据）
2. 法向量估计｜Normal Estimation
3. 点云数据与法向数据拼接｜Concat cloud-data with normal-data
4. 曲面重建｜Surface Reconstruction
5. 重建结果图形可视化｜Visualization

### 存在的问题
当前代码相当于雷达一打开，就用获取到的第一帧数据进行曲面重建，但造成的问题是曲面重建可视化窗口和原始FLOAM窗口线程冲突
关掉曲面重建可视化窗口后，原始FLOAM窗口和曲面重建可视化窗口都会刷新下一帧数据
> 以上问题暂未开始着手解决