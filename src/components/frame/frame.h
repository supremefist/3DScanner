/*
Class Frame that holds all relevant info and data for a registration frame
*/

#ifndef FRAME_H
#define FRAME_H

#include "frame_types.h"

namespace scanner {

class Frame
{

public:
	//constructors
	Frame();
	Frame(CloudPtr);

	CloudConstPtr getCloudPtr();

	//functions
	static Frame *loadFromFilename(std::string filename);

private:
	//members
	CloudPtr _cloud;


};

}

#endif // FRAME_H
