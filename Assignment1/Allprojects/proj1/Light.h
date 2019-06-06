#pragma once
#include "src/vector/vector3/vector3.h"

struct  Light{
	vector3 _pos;
	vector3 _color;

	Light();
	Light(vector3 &pos, vector3 &color);
	vector3 compute_L(vector3 &hitPoint);
};