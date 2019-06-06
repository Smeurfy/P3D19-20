#pragma once
#include "src/vector/vector3/vector3.h"
#include "ray.h"
#include "object.h"

struct  Plane : public Object{
	vector3 _p1;
	vector3 _p2;
	vector3 _p3;
	vector3 _n; //norma
	float _t;
	float _d;
	
	Plane();
	Plane(vector3 &p1, vector3 &p2, vector3 &p3);
	Plane(float focal_dist, vector3 normalPlane);

	bool checkRayColision(Ray &ray, float *dist, vector3 *hitpoint);
	vector3 getNormal(Ray &Ray, vector3 &point);
	bool pointInShadow(Ray ray);
	void calculate_bounding_box();
};