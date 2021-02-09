# 解决ROS配置中cv_bridge问题

> cv_bridge — opencv和ros连接起来的桥

## 问题描述
在Jetson Nano+ROS环境上catkin_make时出现cv_bridge问题如下
```bash
CMake Error at /home/nano/catkin_ws/devel/share/cv_bridge/cmake/cv_bridgeConfig.cmake:113 (message):
  Project 'cv_bridge' specifies
  '/home/nano/catkin_ws/src/vision_opencv/cv_bridge/include' as an include
  dir, which is not found.  It does neither exist as an absolute directory
  nor in
  '/home/nano/catkin_ws/src/vision_opencv/cv_bridge//home/nano/catkin_ws/src/vision_opencv/cv_bridge/include'.
  Check the issue tracker
  'https://github.com/ros-perception/vision_opencv/issues' and consider
  creating a ticket if the problem has not been reported yet.
Call Stack (most recent call first):
  /opt/ros/melodic/share/catkin/cmake/catkinConfig.cmake:76 (find_package)
  tx2_fcnn_node/CMakeLists.txt:57 (find_package)
```

## 解决方法
1. 卸载旧版本cv_bridge
```bash
sudo apt-get remove ros-indigo-cv-bridge
```
2. 下载最新版cv_bridge
```bash
git clone https://github.com/ros-perception/vision_opencv.git
```
3. 【可以省略】修改`vision_opencv/cv_bridge/CMakeLists.txt`，在20行左右的位置修改opencv版本
```bash
set(_opencv_version 4)
find_package(OpenCV 4 QUIET)
if(NOT OpenCV_FOUND)
  message(STATUS “Did not find OpenCV 4, trying OpenCV 3”)
  set(_opencv_version 3)
endif()
```
> 此步我并没有修改，也正确的找到opencv
> 但jetson nano默认安装的opencv环境是opencv4，可以参照 [Trouble with catkin_make hector slam - #3 by hwlim3unws - Jetson TX2 - NVIDIA Developer Forums](https://forums.developer.nvidia.com/t/trouble-with-catkin-make-hector-slam/126470/3)中**hwlim3unws**的方法 将opencv环境修改到3
> 1. sudo apt-get purge ’ * libopencv * ’ (’ and * should have not space in between. Don’t know why but this website does not reflect when ’ and * is next to each other)
> 2. sudo apt-get remove ros-*
> 3. System Settings —> Software & Updates —> ‘Other Software’ tab —> uncheck nvidia related repos
> 4. reinstall ROS using ROS website’s tutorial
> 5. ~/catkin_ws$ source devel/setup.bash
> 6. ~/catkin_ws$ catkin_make

4. 将`vision_opencv`中的`cv_bridge/`拿出来，放到工作空间(`catkin_wa/src`)中，重新编译：
```bash
cd ~/catkin_ws/src/cv_bridge
mkdir build
cd build
cmake ..
make
sudo make install
```
> 这里我才用传统make的方法，网上也有人直接`catkin_make --pkg cv_bridge`

【报错：make 66%时错误】
```bash
[ 66%] Building CXX object src/CMakeFiles/cv_bridge_boost.dir/module.cpp.o
In file included from /usr/include/python2.7/numpy/ndarrayobject.h:27:0,
                 from /home/nano/catkin_ws/src/cv_bridge/src/module.hpp:26,
                 from /home/nano/catkin_ws/src/cv_bridge/src/module.cpp:35:
/home/nano/catkin_ws/src/cv_bridge/src/module.hpp: In function ‘int do_numpy_import()’:
/usr/include/python2.7/numpy/__multiarray_api.h:1537:144: error: return-statement with no value, in function returning ‘int’ [-fpermissive]
 efine import_array() {if (_import_array() < 0) {PyErr_Print(); PyErr_SetString(PyExc_ImportError, "numpy.core.multiarray failed to import"); return NUMPY_IMPORT_ARRAY_RETVAL; } }
                                                                                                                                              ^
/usr/include/python2.7/numpy/__multiarray_api.h:1537:144: note: in definition of macro ‘import_array’
 efine import_array() {if (_import_array() < 0) {PyErr_Print(); PyErr_SetString(PyExc_ImportError, "numpy.core.multiarray failed to import"); return NUMPY_IMPORT_ARRAY_RETVAL; } }
                                                                                                                                              ^~~~~~
src/CMakeFiles/cv_bridge_boost.dir/build.make:62: recipe for target 'src/CMakeFiles/cv_bridge_boost.dir/module.cpp.o' failed
make[2]: *** [src/CMakeFiles/cv_bridge_boost.dir/module.cpp.o] Error 1
CMakeFiles/Makefile2:930: recipe for target 'src/CMakeFiles/cv_bridge_boost.dir/all' failed
make[1]: *** [src/CMakeFiles/cv_bridge_boost.dir/all] Error 2
Makefile:140: recipe for target 'all' failed
make: *** [all] Error 2
```
解决方法是，修改`/home/nano/catkin_ws/src/cv_bridge/src/module.hpp`（根据自己的路径），将最后一段（36～40）行改为
```cpp
static void do_numpy_import( )
{
	import_array( );
}
```

## Resources
- https://forums.developer.nvidia.com/t/trouble-with-catkin-make-hector-slam/126470/3
- https://www.cnblogs.com/Jessica-jie/p/6959309.html
- [can’t process package cv_bridge · Issue #205 · ros-perception/vision_opencv · GitHub](https://github.com/ros-perception/vision_opencv/issues/205)