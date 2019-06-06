#pragma once
#include "src/vector/vector3/vector3.h"
#include "ray.h"
#include "object.h"

struct Sphere : public Object {
	vector3 _c;
	float _r;
	
	Sphere();
	Sphere(vector3 &c, float r);

	bool checkRayColision(Ray &ray, float *dist, vector3 *hitPoint);
	vector3 getNormal(Ray &ray, vector3 &hitPoint);

	bool pointInShadow(Ray ray);
	float exitRayIndex(Ray ray);
	float enterRayIndex(Ray ray);
	void calculate_bounding_box();
};

