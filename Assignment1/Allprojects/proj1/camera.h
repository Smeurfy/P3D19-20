#pragma once
#include "src/vector/vector3/vector3.h"
#include "ray.h"

struct Camera{
	vector3 _backgroundC;
	vector3 _eye;
	vector3 _at;
	vector3 _up;
	vector3 _xe;
	vector3 _ye;
	vector3 _ze;
	float _fovy;
	float nearP, farP;
	int _ResX, _ResY;
	float _df;
	float _w, _h;

	Camera();

	void df();
	void h_calc();
	void w_calc();
	void ze_calc();
	void xe_calc();
	void ye_calc();

	Ray calcPrimRay(float x, float y);
};