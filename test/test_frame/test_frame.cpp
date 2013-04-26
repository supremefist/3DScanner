#include <boost/test/unit_test.hpp> 

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

BOOST_AUTO_TEST_SUITE( testFrame )

BOOST_AUTO_TEST_CASE( testMakeFrameFromBasicCloud ) {

  // Generate sample point cloud
  pcl::PointCloud<pcl::PointXYZ> cloud;

  // Fill in the cloud data
  cloud.width    = 5;
  cloud.height   = 1;
  cloud.is_dense = false;
  cloud.points.resize (cloud.width * cloud.height);

  for (size_t i = 0; i < cloud.points.size (); ++i)
  {
    cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
  }

  pcl::io::savePCDFileASCII ("random.pcd", cloud);

}

BOOST_AUTO_TEST_SUITE_END()
