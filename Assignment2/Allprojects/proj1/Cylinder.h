#pragma once
#include "src/vector/vector3/vector3.h"
#include "ray.h"
#include "object.h"

struct  Cylinder : public Object {
	vector3 _base;
	vector3 _apex;
	float _baseRadius;
	float _apexRadius;
	vector3 _normal;

	Cylinder();
	Cylinder(vector3 &base, vector3 &apex, float bR, float aR);


	bool checkRayColision(Ray &ray, float *dist, vector3 *hitpoint);
	bool pointInShadow(Ray &ray);
	vector3 getNormal(Ray &ray, vector3 &hitPoint);
	void calculate_bounding_box();
};