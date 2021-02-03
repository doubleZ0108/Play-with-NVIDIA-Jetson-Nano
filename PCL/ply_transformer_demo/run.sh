rm -rf build
mkdir build && cd build
cp ../../Resources/o3d.ply .
cmake ..
make
