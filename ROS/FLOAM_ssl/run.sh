## compile
rm -rf build
catkin_make -j2
source devel/setup.bash

## launch
roslaunch floam_ssl floam_ssl_octo_mapping.launch
