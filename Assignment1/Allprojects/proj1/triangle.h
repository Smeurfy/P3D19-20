#pragma once
#include "src/vector/vector3/vector3.h"
#include "ray.h"
#include "object.h"
#include "src/matrix/matrix3x3/matrix3x3.h"

struct  Triangle : public Object {
	vector3 _p1;
	vector3 _p2;
	vector3 _p3;
	vector3 _n; //norma
	
	Triangle();
	Triangle(vector3 &p1, vector3 &p2, vector3 &p3);

	bool checkRayColision(Ray &ray, float *dist, vector3 *hitpoint);
	bool pointInShadow(Ray &ray);
	vector3 getNormal(Ray &ray, vector3 &hitPoint);
};