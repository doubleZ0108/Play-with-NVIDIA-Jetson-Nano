rm -rf build
mkdir build && cd build
cp ../../Resources/table.pcd .
cmake ..
make