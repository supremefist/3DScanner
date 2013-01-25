// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "3DScannerConfig.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
 
int main (int argc, char *argv[])
{
    pcl::PointCloud<pcl::PointXYZ> cloud;

    // Fill in the cloud data
	cloud.width  = 15;
	cloud.height = 1;
	cloud.points.resize (cloud.width * cloud.height);

	// Generate the data
	for (size_t i = 0; i < cloud.points.size (); ++i)
	{
	  cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
	  cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
	  cloud.points[i].z = 1.0;
	}

	pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);

  return 0;
}
