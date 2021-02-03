#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{

        /*点云载入模块*/
        // 点云模型读入,此处读入为PCD格式点云文件.数据类型为PointXYZ.
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) == -1)
                {
                        PCL_ERROR("Couldn't read file mypointcloud.pcd\n");  //若读取失败将提示
                        return -1;
                }
        std::cerr << "点云读入   完成" << std::endl;


        /*法向估计模块*/
        // Normal estimation（法向量估计）
        pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;//创建法向估计对象
        pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);//创建法向数据指针
        pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);//创建kdtree用于法向计算时近邻搜索
        tree->setInputCloud(cloud);//为kdtree输入点云
        n.setInputCloud(cloud);//为法向估计对象输入点云
        n.setSearchMethod(tree);//设置法向估计时采用的搜索方式为kdtree
        n.setKSearch(20);//设置法向估计时,k近邻搜索的点数
        n.compute(*normals);  //进行法向估计
    
        std::cerr << "法线计算   完成" << std::endl;

        /*点云数据与法向数据拼接*/
        // 创建同时包含点和法向的数据结构的指针
        pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
        //将已获得的点数据和法向数据拼接
        pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);


        // 创建另一个kdtree用于重建
        pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
        //为kdtree输入点云数据,该点云数据类型为点和法向
        tree2->setInputCloud(cloud_with_normals);

        /*曲面重建模块*/
        // 创建贪婪三角形投影重建对象
        pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
        //创建多边形网格对象,用来存储重建结果
        pcl::PolygonMesh triangles; 

        //设置参数
        gp3.setSearchRadius(25);  // 设置连接点之间的最大距离（最大边长）用于确定k近邻的球半径（默认为0）
        gp3.setMu(2.5);  // 设置最近邻距离的乘子，已得到每个点的最终搜索半径（默认为0）
        gp3.setMaximumNearestNeighbors(100);  //设置搜索的最近邻点的最大数量
        gp3.setMaximumSurfaceAngle(M_PI / 2); // 45 degrees 最大平面角
        gp3.setMinimumAngle(M_PI / 18); // 10 degrees 每个三角的最大角度
        gp3.setMaximumAngle(2 * M_PI / 3); // 120 degrees
        gp3.setNormalConsistency(false);  //若法向量一致，设为true
        // 设置点云数据和搜索方式
        gp3.setInputCloud(cloud_with_normals);
        gp3.setSearchMethod(tree2);
        //开始重建
        gp3.reconstruct(triangles);
        std::cerr << "重建   完成" << std::endl;

        //将重建结果保存到硬盘文件中,重建结果以VTK格式存储
        pcl::io::saveVTKFile("mymesh.vtk", triangles); 

        // Additional vertex information
        std::vector<int> parts = gp3.getPartIDs();
        std::vector<int> states = gp3.getPointStates();
        fstream fs;
        fs.open("partsID.txt", ios::out);
        if (!fs)
                {
                        return -2;
                }
        fs << "点云数量为：" << parts.size() << "\n";
        for (int i = 0; i < parts.size(); i++)
                {
                        if (parts[i] != 0)
                                {
                                        fs << parts[i] << "\n";   //这的fs对吗？
                                }
                }

     
        //图形显示模块
        //创建显示对象指针
        std::cerr << "开始显示 ........" << std::endl;
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
        viewer->setBackgroundColor(0, 0, 0.6);  //设置窗口颜色
        viewer->addPolygonMesh(triangles, "my");  //设置所要显示的网格对象
        //设置网格模型显示模式
        viewer->setRepresentationToSurfaceForAllActors(); //网格模型以面片形式显示  
        //viewer->setRepresentationToPointsForAllActors(); //网格模型以点形式显示  
        // viewer->setRepresentationToWireframeForAllActors();  //网格模型以线框图模式显示
        viewer->addCoordinateSystem(0.1);  //设置坐标系,参数为坐标显示尺寸
        viewer->initCameraParameters();
        while (!viewer->wasStopped())
                {
                        viewer->spinOnce(100);
//                        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
                }


        // Finish
        return 0;
}
