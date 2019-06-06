#pragma once
#include "src/vector/vector3/vector3.h"

struct Material {
	vector3 _rgb;
	
	float _kd;
	float _ks;
	float _shine;
	float _t;
	float _index_of_refraction;
	
	Material();
	Material(vector3 &color, float kd, float ks, float shine, float t, float index);
};