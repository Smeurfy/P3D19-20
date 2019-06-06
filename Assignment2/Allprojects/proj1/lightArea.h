#pragma once
#include "src/vector/vector3/vector3.h"
#include "light.h"

struct  LightArea : public Light {
	vector3 _a;
	vector3 _b;
	
	LightArea(vector3 pos, vector3 color) : Light(pos, color) 
	{

		_a = vector3(_pos._x + 0.5, _pos._y, _pos._z);
		_b = vector3(_pos._x, _pos._y + 0.5, _pos._z);

		//_a = _a - pos;
		//_b = _b - pos;

		////calculation of the normal vector with direction to origin
		//vector3 planeN = vector3(0, 0, 0) - pos;
		////normalization
		//planeN = planeN.normalizado();
		////distance d from origin to plane
		//float d = -(planeN._x * pos._x + planeN._y * pos._y + planeN._z * pos._z);
		////corner point c
		//vector3 c;
		//c._x = -(planeN._y * pos._y + planeN._z * pos._z) / planeN._x + d / planeN._x;
		//c._y = -(planeN._x * pos._x + planeN._z * pos._z) / planeN._y + d / planeN._y;
		//c._z = -(planeN._x * pos._x + planeN._y * pos._y) / planeN._z + d / planeN._z;
	};

	vector3 compute_L_SoftShadows(vector3 hitPoint, vector3 s_light);
};
