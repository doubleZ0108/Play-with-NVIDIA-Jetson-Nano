#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>

void cloudFilter(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud) {

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGB>);

    // (1)
    pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> outrem;
    outrem.setInputCloud(cloud);
    outrem.setRadiusSearch(0.8);
    outrem.setMinNeighborsInRadius(2);
    outrem.filter(*cloud_filtered);


    // (2)
    pcl::ConditionAnd<pcl::PointXYZRGB>::Ptr range_cond(new pcl::ConditionAnd<pcl::PointXYZRGB>());
    range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZRGB>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZRGB>("z", pcl::ComparisonOps::GT, 0.0)));
    range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZRGB>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZRGB>("z", pcl::ComparisonOps::LT, 0.8)));
    pcl::ConditionalRemoval<pcl::PointXYZRGB> condrem(range_cond);
    condrem.setInputCloud(cloud);
    condrem.setKeepOrganized(true);
    condrem.filter(*cloud_filtered);
}