#include <string>
#include "frame_viewer.h"
#include <components/frame/frame.h>
#include <pcl/visualization/cloud_viewer.h>
#include <boost/thread/thread.hpp>

namespace scanner {

void FrameViewer::renderFrameFromFile(std::string filename, bool preview) {
	Frame *f = Frame::loadFromFilename(filename);

	CloudConstPtr cloud = f->getCloudPtr();

	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloud);
	if (preview) {
		while (!viewer.wasStopped()) {
		}
	} else {
		std::cout << "Starting..." << std::endl;
		if (viewer.wasStopped(2000)) {
			std::cout << "Waiting..." << std::endl;
		}
		std::cout << "Done!" << std::endl;
	}
}

}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Please provide filename of point cloud to render."
				<< std::endl;
		return 0;
	}

	scanner::FrameViewer viewer;
	viewer.renderFrameFromFile(argv[1], true);
}

