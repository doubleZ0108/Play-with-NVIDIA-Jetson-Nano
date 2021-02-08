# FLOAM_ssl

[toc]

-----

> FLOAM_ssl是基于ROS+RealSense L515的激光雷达深度点云采集及定位项目（这里总结的可能不是很到位，可以参考repo中的动图了解）
>
>  repo：https://github.com/wh200720041/FLOAM_ssl

## 我理解的项目结构

- `launch/`：运行启动文件，在这里配置`node`和`param`，可以控制运行时启动的节点服务和超参数

  > 切换官方实验室视频数据 or RealSense L515实时采集的数据
  >
  > `.launch`文件开始的两行决定使用那部分数据
  >
  > ```xml
  > <!-- 实验室视频数据 -->
  > <node pkg="rosbag" type="play" name="rosbag_play" args="--clock $(env HOME)/Downloads/L515_test.bag"/> 
  > <param name="/use_sim_time" value="true" />
  > 
  > <!-- RealSense L515实时采集的数据 -->
  > <include file="$(find realsense2_camera)/launch/rs_camera.launch">
  >   <arg name="color_width" value="1280" />
  >   <arg name="color_height" value="720" />
  >   <arg name="filters" value="pointcloud" />
  > </include>
  > ```

- `rviz/`：用来决定页面的布局和可调参数调整部分

- `src/`

  - `laserMapping`
  - `laserProcessing`
  - `octoMapping`：八叉树如何显示到ROS的可视化平台上
  - `octoEstimation`

- `CMakeLists`：编译输出的文件决定`.launch`和`.cpp`中的节点

<br/>

## 整合点云三角化重建原项目

### 如何修改并运行
主要修改 `src/octoMappingNode.cpp`文件
修改完切换到`catkin_wk/`下，执行 [FLOAM_ssl/run.sh](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/ROS/FLOAM_sslrun.sh)  脚本重新编译并运行



### 整合点云三角化代码
将[FLOAM_ssl/cloud_visualization.cpp](https://github.com/doubleZ0108/Play-with-NVIDIA-Jetson-Nano/blob/master/ROS/FLOAM_ssl/cloud_visualization.cpp) 放入`src/octoMappingNode.cpp`文件，重新编译运行

#### 基本步骤
1. 将原始PointXYZRGB 格式转化为PointXYZ（暂时去除了颜色数据）
2. 法向量估计｜Normal Estimation
3. 点云数据与法向数据拼接｜Concat cloud-data with normal-data
4. 曲面重建｜Surface Reconstruction
5. 重建结果图形可视化｜Visualization

#### 存在的问题
当前代码相当于雷达一打开，就用获取到的第一帧数据进行曲面重建，但造成的问题是曲面重建可视化窗口和原始FLOAM窗口线程冲突
关掉曲面重建可视化窗口后，原始FLOAM窗口和曲面重建可视化窗口都会刷新下一帧数据

> 以上问题暂未开始着手解决

