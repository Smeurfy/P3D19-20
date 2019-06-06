#pragma once
#include "src/vector/vector3/vector3.h"
#include "ray.h"
#define EPSILON 1e-10

struct AABB {
	double xmin = 0;
	double xmax = 0;
	double ymin = 0;
	double ymax = 0;
	double zmin = 0;
	double zmax = 0;

	AABB();
	AABB(const double xmin, const double xmax, const double ymin, const double ymax, const double zmin, const double zmax);
	AABB(const vector3 pmin, const vector3 pmax);

	bool intersect(const Ray &ray, double &t0, double &t1, vector3 &tmin, vector3 &tmax);
	bool inside(const vector3 &p);
	void set_bounding_box(const vector3 &min, const vector3 &max);
};