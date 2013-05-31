/*
 * register_clouds.cpp
 *
 *  Created on: 31 May 2013
 *      Author: riaan
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "register_clouds.h"

#include <boost/make_shared.hpp>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/filter.h>

#include <pcl/features/normal_3d.h>

#include <pcl/registration/icp.h>
#include <pcl/registration/icp_nl.h>
#include <pcl/registration/transforms.h>

namespace scanner {
void CloudRegistration::setReference(CloudPtr cloud) {
	reference = cloud;
}

void CloudRegistration::setSlave(CloudPtr cloud) {
	slave = cloud;
}

CloudPtr CloudRegistration::performRegistration() {
	// Compute surface normals and curvature
	CloudWithNormals::Ptr points_with_normals_src(new CloudWithNormals);
	CloudWithNormals::Ptr points_with_normals_tgt(new CloudWithNormals);

	pcl::NormalEstimation<PointT, PointNormalT> norm_est;
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(
			new pcl::search::KdTree<pcl::PointXYZ>());
	norm_est.setSearchMethod(tree);
	norm_est.setKSearch(30);

	norm_est.setInputCloud(reference);
	norm_est.compute(*points_with_normals_src);
	pcl::copyPointCloud(*reference, *points_with_normals_src);

	norm_est.setInputCloud(slave);
	norm_est.compute(*points_with_normals_tgt);
	pcl::copyPointCloud(*slave, *points_with_normals_tgt);

	//
	// Instantiate our custom point representation (defined above) ...
	MyPointRepresentation point_representation;
	// ... and weight the 'curvature' dimension so that it is balanced against x, y, and z
	float alpha[4] = { 1.0, 1.0, 1.0, 1.0 };
	point_representation.setRescaleValues(alpha);

	//
	// Align
	pcl::IterativeClosestPointNonLinear<PointNormalT, PointNormalT> reg;
	reg.setTransformationEpsilon(1e-6);
	// Set the maximum distance between two correspondences (src<->tgt) to 10cm
	// Note: adjust this based on the size of your datasets
	reg.setMaxCorrespondenceDistance(0.1);
	// Set the point representation
	reg.setPointRepresentation(
			boost::make_shared<const MyPointRepresentation>(
					point_representation));

	reg.setInputCloud(points_with_normals_src);
	reg.setInputTarget(points_with_normals_tgt);

	//
	// Run the same optimization in a loop and visualize the results
	Eigen::Matrix4f Ti = Eigen::Matrix4f::Identity(), prev, targetToSource;
	CloudWithNormals::Ptr reg_result = points_with_normals_src;
	reg.setMaximumIterations(2);
	for (int i = 0; i < 50; ++i) {
		PCL_INFO("Iteration Nr. %d.\n", i);

		// save cloud for visualization purpose
		points_with_normals_src = reg_result;

		// Estimate
		reg.setInputCloud(points_with_normals_src);
		reg.align(*reg_result);

		//accumulate transformation between each Iteration
		Ti = reg.getFinalTransformation() * Ti;

		//if the difference between this transformation and the previous one
		//is smaller than the threshold, refine the process by reducing
		//the maximal correspondence distance
		if (fabs((reg.getLastIncrementalTransformation() - prev).sum())
				< reg.getTransformationEpsilon())
			reg.setMaxCorrespondenceDistance(
					reg.getMaxCorrespondenceDistance() - 0.001);

		prev = reg.getLastIncrementalTransformation();
	}

	//
	// Get the transformation from target to source
	targetToSource = Ti.inverse();

	//
	// Transform target back in source frame
	CloudPtr output(new Cloud);

	std::cout << "Transforming slave..." << std::endl;
	pcl::transformPointCloud(*slave, *output, targetToSource);

	//add the source to the transformed target
	std::cout << "Finalising output..." << std::endl;
	*output += *reference;

	//final_transform = targetToSource;
	return output;
}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Please provide filename of point cloud filelist."
				<< std::endl;
		return 0;
	}

	std::vector < std::string > cloud_filenames(0);
	std::string current_filename;

	// Open list of pointcloud filenames
	std::string filelist_filename = argv[1];
	std::cout << "Loading point clouds from " + filelist_filename << "..."
			<< std::endl;

	std::ifstream filelist(filelist_filename.c_str());

	// Load all pointcloud filenames
	if (filelist.is_open()) {
		while (filelist.good()) {
			getline(filelist, current_filename);
			if (current_filename != "") {
				cloud_filenames.push_back(current_filename);
			}
		}
		filelist.close();
	} else {
		std::cout << "Unable to open file" << std::endl << std::endl;
	}

	// Load first cloud as reference frame
	std::cout << "Reference: " << cloud_filenames[0] << std::endl;
	scanner::Frame *reference_frame = scanner::Frame::loadFromFilename(
			cloud_filenames[0]);

	// Filter frame
	reference_frame->filter();

	scanner::CloudRegistration registration;

	// Iterate through rest of filelist
	for (unsigned int i = 1; i < cloud_filenames.size(); i++) {
		std::cout << "Slave: " << cloud_filenames[i] << std::endl;
		// Load frame to be registered
		scanner::Frame *slave_frame = scanner::Frame::loadFromFilename(
				cloud_filenames[i]);

		// Filter frame
		slave_frame->filter();

		// Register frame
		registration.setReference(reference_frame->getCloudPtr());
		registration.setSlave(slave_frame->getCloudPtr());

		std::cout << "Registration starting..." << std::endl;
		reference_frame = new scanner::Frame(registration.performRegistration());
		std::cout << "Registration complete!" << std::endl;
	}

	std::string output_filename = "merged.pcd";
	std::cout << "Writing final output to " << output_filename << std::endl;
	reference_frame->writePCD(output_filename);

	return 0;
}
