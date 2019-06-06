#include "aabb.h"

AABB::AABB(){
}

AABB::AABB(double x0, double x1, double y0, double y1, double z0, double z1) {
	xmin = x0;
	xmax = x1;
	ymin = y0;
	ymax = y1;
	zmin = z0;
	zmax = z1;
}

AABB::AABB(const vector3 p0, const vector3 p1) {
	xmin = p0._x;
	xmax = p1._x;
	ymin = p0._y;
	ymax = p1._y;
	zmin = p0._z;
	zmax = p1._z;
}

//Kay and Kajiya Algorithm
bool AABB::intersect(const Ray &ray, double &t0, double &t1, vector3 &tmin, vector3 &tmax) {

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / ray._d._x;
	if (a >= 0) {
		tx_min = (xmin - ray._o._x) * a;
		tx_max = (xmax - ray._o._x) * a;
	}
	else {
		tx_min = (xmax - ray._o._x) * a;
		tx_max = (xmin - ray._o._x) * a;
	}

	double b = 1.0 / ray._d._y;
	if (b >= 0) {
		ty_min = (ymin - ray._o._y) * b;
		ty_max = (ymax - ray._o._y) * b;
	}
	else {
		ty_min = (ymax - ray._o._y) * b;
		ty_max = (ymin - ray._o._y) * b;
	}

	double c = 1.0 / ray._d._z;
	if (c >= 0) {
		tz_min = (zmin - ray._o._z) * c;
		tz_max = (zmax - ray._o._z) * c;
	}
	else {
		tz_min = (zmax - ray._o._z) * c;
		tz_max = (zmin - ray._o._z) * c;
	}

	// Find largest entering t value
	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;
	if (tz_min > t0)
		t0 = tz_min;

	// Find smallest exiting t value
	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;
	if (tz_max < t1)
		t1 = tz_max;


	// Store values of t.
	tmin = vector3(tx_min, ty_min, tz_min);
	tmax = vector3(tx_max, ty_max, tz_max);

	return (t0 < t1 && t1 > EPSILON);
}

bool AABB::inside(const vector3 &p) {
	return  (p._x > xmin && p._x < xmax) &&
		(p._y > ymin && p._y < ymax) &&
		(p._z > zmin && p._z < zmax);
}

void AABB::set_bounding_box(const vector3 &min, const vector3 &max) {
	xmin = min._x;
	ymin = min._y;
	zmin = min._z;
	xmax = max._x;
	ymax = max._y;
	zmax = max._z;
}

