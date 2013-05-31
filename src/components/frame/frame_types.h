#ifndef FRAME_TYPES_H
#define FRAME_TYPES_H

#include <pcl/point_types.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointNormal PointNormalT;
typedef pcl::PointCloud<PointT> Cloud;
typedef pcl::PointCloud<PointT>::Ptr CloudPtr;
typedef pcl::PointCloud<PointT>::ConstPtr CloudConstPtr;
typedef pcl::PointCloud<PointNormalT> CloudWithNormals;

#endif // FRAME_H
