## How to Run?
```bash
# compile
chmod 777 run.sh
./run.sh

# run
cd build/
./triangulation table.pcd
```

> 更换103～105行三段代码，可以切换三种展现形式

```cpp
viewer->setRepresentationToSurfaceForAllActors(); //网格模型以面片形式显示  
viewer->setRepresentationToPointsForAllActors(); //网格模型以点形式显示  
viewer->setRepresentationToWireframeForAllActors();  //网格模型以线框图模式显示
        
```

<img src="../../README.assets/PCL/triangulation-surface.png" alt="triangulation-surface" width="67%;" />

<img src="../../README.assets/PCL/triangulation-wireframe.png" alt="triangulation-wireframe" width="67%;" />