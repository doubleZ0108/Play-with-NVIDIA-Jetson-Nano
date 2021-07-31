#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/io.h>
#include <pcl/point_cloud.h>
 
#include <pcl/PolygonMesh.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <pcl/io/vtk_lib_io.h>
 
#include<pcl/point_types.h>

void ply2mesh(std::string filename) {
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());//创建点云对象
	pcl::PolygonMesh mesh;
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	int a=pcl::io::loadPolygonFilePLY(filename, mesh); //PCL利用VTK的IO接口，可以直接读取stl,ply,obj等格式的三维点云数据,传给PolygonMesh对象
//若要读取stl文件，则使用函数loadPolygonFileSTL
	pcl::io::mesh2vtk(mesh, polydata);  //将PolygonMesh对象转化为vtkPolyData对象
	pcl::io::vtkPolyDataToPointCloud(polydata, *cloud);//将vtkPolyData对象转化为Ptr对象， 获取点云
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("The name"));
	viewer->initCameraParameters(); 
	int v1(0), v2(1);
	viewer->createViewPort(0.0, 0.0, 0.5, 1, v1);//xmin,ymin,xmax,ymax
	viewer->createViewPort(0.5, 0,  1,    1, v2);
	viewer->setBackgroundColor(0, 1, 0, v1);
	viewer->setBackgroundColor(0, 0, 1, v2);
	viewer->createViewPortCamera(v1);//创建新相机，使得两个窗口的视图操作独立
	//viewer->createViewPortCamera(v2);
	viewer->addPolygonMesh(mesh, "mesh",v1);
	viewer->addPointCloud(cloud, "points",v2);
	viewer->addCoordinateSystem(0.05);
}

int readcloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string filename) {
	// PointXYZ表示三维坐标信息
	// 读取ply文件
	if (pcl::io::loadPLYFile<pcl::PointXYZ>(filename, *cloud) == -1) {
		//PCL_ERROR("Couldnot read file.\n");
		cout << "Couldnot read file." << endl;
		system("pause");
		return -1;
	}
	cout << "已读取并显示"<<filename<<"原始点云数据" << endl;
	cout << filename<<"原始点云数据点数：" << cloud->points.size() << endl;
	return 0;
}


int main ()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());//创建点云对象
	
	readcloud(cloud, "o3d.ply");
	
	// some error still exists that cannot run
	// ply2mesh("o3d.ply");

	return 0;
}
