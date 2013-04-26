#include "frame.h"

#include <exception>
#include <pcl/io/pcd_io.h>

namespace scanner {

Frame::Frame() {

}

Frame::Frame(CloudPtr cloud_in) {
	_cloud = cloud_in;
}

Frame* Frame::loadFromFilename(std::string filename) {
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(
			new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile < pcl::PointXYZ > (filename, *cloud) == -1) { //* load the file
		throw "Could not load PCD from file: " + filename;
	}

	return new Frame(cloud);
}

}

