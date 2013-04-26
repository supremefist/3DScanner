#include <string>
#include "frame_viewer.h"
#include <components/frame/frame.h>
#include <pcl/visualization/cloud_viewer.h>

namespace scanner {

void FrameViewer::renderFrameFromFile(std::string filename) {
	Frame *f = Frame::loadFromFilename(filename);

	CloudPtr cloud = f->getCloudPtr();

	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloud);
	while (!viewer.wasStopped()) {
	}
}

}

