#include "triangle.h"
#include <iostream>

Triangle::Triangle() {}

Triangle::Triangle(vector3 &p1, vector3 &p2, vector3 &p3) {
	vector3 v1, v2;
	vector3 n; //vai dar a normal
	float d;

	_p1 = p1;
	_p2 = p2;
	_p3 = p3;

	v1 = p2 - p1;
	v2 = p3 - p1;

	n = cross(v1, v2);
	_n = n.normalizado();

	calculate_bounding_box();
}

vector3 Triangle::getNormal(Ray &ray, vector3 &hitPoint)
{
	return _n;
}

bool Triangle::checkRayColision(Ray &ray, float *dist, vector3 *hitpoint) {
	
	//Optimization
	if (ray.id == lastRay) {
		*dist = lastDist;
		*hitpoint = lastHitpoint;
		return true;
	}
	
	vector3 origin = ray._o;
	vector3 direction = ray._d;
	
	// NAO TENHO  A CERTEZA SE SAO OS VALORES CORRETOS PARA O INTERVALO
	float t0 = 0.0f;
	float t1 = FLT_MAX;

	matrix3x3 A((_p1._x - _p2._x), (_p1._x - _p3._x), (direction._x),
				(_p1._y - _p2._y), (_p1._y - _p3._y), (direction._y),
				(_p1._z - _p2._z), (_p1._z - _p3._z), (direction._z)
	);

	matrix3x3 T((_p1._x - _p2._x), (_p1._x - _p3._x), (_p1._x - origin._x),
				(_p1._y - _p2._y), (_p1._y - _p3._y), (_p1._y - origin._y),
				(_p1._z - _p2._z), (_p1._z - _p3._z), (_p1._z - origin._z)
	);
	float t = T.detM3x3() * (1 / A.detM3x3());
	if (t < t0 || t > t1) {
		return false;
	}
	
	matrix3x3 G((_p1._x - _p2._x), (_p1._x - origin._x), (direction._x),
				(_p1._y - _p2._y), (_p1._y - origin._y), (direction._y),
				(_p1._z - _p2._z), (_p1._z - origin._z), (direction._z)
	);
	float g = G.detM3x3() * (1 / A.detM3x3());
	if (g < 0|| g > 1) {
		return false;
	}

	matrix3x3 B((_p1._x - origin._x), (_p1._x - _p3._x), (direction._x),
				(_p1._y - origin._y), (_p1._y - _p3._y), (direction._y),
				(_p1._z - origin._z), (_p1._z - _p3._z), (direction._z)
	);
	float b = B.detM3x3() * (1 / A.detM3x3());
	if (b < 0 || b > (1 - g)) {
		return false;
	}

	vector3 hitPoint = origin + t * direction;

	*dist = t;
	*hitpoint = hitPoint;

	//Optimization
	lastRay = ray.id;
	lastDist = *dist;
	lastHitpoint = *hitpoint;

	return true;
}

bool Triangle::pointInShadow(Ray &ray) 
{
	//Optimization
	if (ray.id == lastRay) {
		return true;
	}
	
	vector3 origin = ray._o;
	vector3 direction = ray._d;

	// NAO TENHO  A CERTEZA SE SAO OS VALORES CORRETOS PARA O INTERVALO
	float t0 = 0.0f;
	float t1 = FLT_MAX;

	matrix3x3 A((_p1._x - _p2._x), (_p1._x - _p3._x), (direction._x),
		(_p1._y - _p2._y), (_p1._y - _p3._y), (direction._y),
		(_p1._z - _p2._z), (_p1._z - _p3._z), (direction._z)
	);

	matrix3x3 T((_p1._x - _p2._x), (_p1._x - _p3._x), (_p1._x - origin._x),
		(_p1._y - _p2._y), (_p1._y - _p3._y), (_p1._y - origin._y),
		(_p1._z - _p2._z), (_p1._z - _p3._z), (_p1._z - origin._z)
	);
	float t = T.detM3x3() * (1 / A.detM3x3());
	if (t < t0 || t > t1) {
		return false;
	}

	matrix3x3 G((_p1._x - _p2._x), (_p1._x - origin._x), (direction._x),
		(_p1._y - _p2._y), (_p1._y - origin._y), (direction._y),
		(_p1._z - _p2._z), (_p1._z - origin._z), (direction._z)
	);
	float g = G.detM3x3() * (1 / A.detM3x3());
	if (g < 0 || g > 1) {
		return false;
	}

	matrix3x3 B((_p1._x - origin._x), (_p1._x - _p3._x), (direction._x),
		(_p1._y - origin._y), (_p1._y - _p3._y), (direction._y),
		(_p1._z - origin._z), (_p1._z - _p3._z), (direction._z)
	);
	float b = B.detM3x3() * (1 / A.detM3x3());
	if (b < 0 || b >(1 - g)) {
		return false;
	}

	//Optimization
	lastRay = ray.id;

	return true;
}

void Triangle::calculate_bounding_box() {
	vector3 min = vector3(INFINITY, INFINITY, INFINITY);
	vector3 max = vector3(-INFINITY, -INFINITY, -INFINITY);

	std::vector<vector3> points;
	points.push_back(_p1);
	points.push_back(_p2);
	points.push_back(_p3);

	for (int i = 0; i < points.size(); i++) {
		if (points[i]._x < min._x)
			min._x = points[i]._x;
		if (points[i]._y < min._y)
			min._y = points[i]._y;
		if (points[i]._z < min._z)
			min._z = points[i]._z;
		if (points[i]._x > max._x)
			max._x = points[i]._x;
		if (points[i]._y > max._y)
			max._y = points[i]._y;
		if (points[i]._z > max._z)
			max._z = points[i]._z;
	}


	boundingBox.set_bounding_box(min, max);
}