#include "frame.h"

#include <exception>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include "frame_types.h"
#include <pcl/io/pcd_io.h>

namespace scanner {

Frame::Frame() {

}

Frame::Frame(CloudPtr cloud_in) {
	_cloud = cloud_in;
}

Frame* Frame::loadFromFilename(std::string filename) {
	pcl::PointCloud<PointT>::Ptr cloud(
			new pcl::PointCloud<PointT>);

	if (pcl::io::loadPCDFile < PointT > (filename, *cloud) == -1) { //* load the file
		throw "Could not load PCD from file: " + filename;
	}

	return new Frame(cloud);
}

void Frame::writePCD(std::string filename) {
	pcl::io::savePCDFileASCII (filename, *_cloud);
}

void Frame::filter() {
	pcl::VoxelGrid < PointT > grid;
	grid.setLeafSize(0.05, 0.05, 0.05);
	grid.setInputCloud(_cloud);
	CloudPtr filtered_cloud(new Cloud);
	grid.filter(*filtered_cloud);
	_cloud = filtered_cloud;
}

CloudPtr Frame::getCloudPtr() {
	return _cloud;
}

}

