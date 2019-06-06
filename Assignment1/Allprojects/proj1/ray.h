#pragma once
#include <iostream>;
#include "src/vector/vector3/vector3.h"

struct Ray {
	vector3 _o; //origin
	vector3 _d; //direction

	Ray();
	Ray(vector3 o, vector3 d);

	void setO(vector3);
	void setD(vector3);

	bool isEmpty();
};