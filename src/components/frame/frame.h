/*
Class Frame that holds all relevant info and data for a registration frame
*/

#ifndef FRAME_H
#define FRAME_H

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class Frame
{
	typedef pcl::PointCloud<pcl::PointXYZ> Cloud;
	typedef Cloud::Ptr CloudPtr;

public:
	//members
	CloudPtr _cloud;

	//constructors
	Frame();
	Frame(CloudPtr);

	//functions
};

#endif // FRAME_H
