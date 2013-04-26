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
	//members
	CloudPtr _cloud;

	//constructors
	Frame();
	Frame(CloudPtr);

	CloudPtr getCloudPtr();

	//functions
	static Frame *loadFromFilename(std::string filename);

};

}

#endif // FRAME_H
