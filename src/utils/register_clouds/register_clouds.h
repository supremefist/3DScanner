/*
 * register_clouds.h
 *
 *  Created on: 31 May 2013
 *      Author: riaan
 */

#ifndef REGISTER_CLOUDS_H_
#define REGISTER_CLOUDS_H_

#include "../../components/frame/frame.h"
#include <pcl/point_representation.h>

namespace scanner {

// Define a new point representation for < x, y, z, curvature >
class MyPointRepresentation : public pcl::PointRepresentation <PointNormalT>
{
  using pcl::PointRepresentation<PointNormalT>::nr_dimensions_;
public:
  MyPointRepresentation ()
  {
    // Define the number of dimensions
    nr_dimensions_ = 4;
  }

  // Override the copyToFloatArray method to define our feature vector
  virtual void copyToFloatArray (const PointNormalT &p, float * out) const
  {
    // < x, y, z, curvature >
    out[0] = p.x;
    out[1] = p.y;
    out[2] = p.z;
    out[3] = p.curvature;
  }
};

class CloudRegistration {
public:
	void setReference(CloudPtr cloud);
	void setSlave(CloudPtr cloud);
	CloudPtr performRegistration();

private:
	CloudPtr reference;
	CloudPtr slave;
};

}

#endif /* REGISTER_CLOUDS_H_ */
