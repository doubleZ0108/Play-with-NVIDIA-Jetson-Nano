/**
read .ply file and use triangle technique to mesh it
Author: doubleZ https://www.doublez.site
**/
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
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
	
    if (pcl::io::loadPLYFile<pcl::PointXYZRGB>(argv[1], *colored_cloud) == -1)
    {
        PCL_ERROR("Couldn't read ply file.\n");
        return -1;
    }
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::copyPointCloud(*colored_cloud, *cloud);
    cout << "original plont cloud data: " << cloud->points.size() << endl;

    /* Normal Estimation*/
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud);
    n.setInputCloud(cloud);
    n.setSearchMethod(tree);
    n.setKSearch(20);
    n.compute(*normals);
    cout << "normal estimation finish..." << endl;


    /* Point Cloud Data concat Normalization Data */
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
    tree2->setInputCloud(cloud_with_normals);

    /* Surface Reconstruction */
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    pcl::PolygonMesh triangles;
    gp3.setSearchRadius(25);
    gp3.setMu(2.5);
    gp3.setMaximumNearestNeighbors(100);
    gp3.setMaximumSurfaceAngle(M_PI / 2);
    gp3.setMinimumAngle(M_PI / 18);
    gp3.setMaximumAngle(2 * M_PI / 3);
    gp3.setNormalConsistency(false);
    gp3.setInputCloud(cloud_with_normals);
    gp3.setSearchMethod(tree2);
    gp3.reconstruct(triangles);
    cout << "surface reconstruction finish..." << endl;


    // save result to disk
    pcl::io::saveVTKFile("mymesh.vtk", triangles);
    cout << "save to disk finish..." << endl;


    /* Visualization */
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0.6);
    viewer->addPolygonMesh(triangles, "my");
    viewer->setRepresentationToSurfaceForAllActors();
    //viewer->setRepresentationToPointsForAllActors();
    // viewer->setRepresentationToWireframeForAllActors();
    viewer->addCoordinateSystem(0.1);
    viewer->initCameraParameters();
    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
    }

	return 0;
}
