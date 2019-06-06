#pragma once
#include <iostream>;
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <vector>;
#include <math.h>  
#include "src/vector/vector3/vector3.h"
#include "src/vector/vector2/vector2.h"
#include "camera.h"
#include "Light.h"
#include "Object.h"
#include "triangle.h"
#include "cylinder.h"

#define DEGTORAD 0.0174532925

struct Parser
{
	Parser();

	//------------Lights------------------------
	std::vector<Light*> _lights;

	//------------Objects--------------------------
	std::vector<Object*> _objects;


	// reading a text file
	void parseNffFile(Camera *camera);

	std::vector<Object*> getObjects();
	std::vector<Light*> getLights();
};
