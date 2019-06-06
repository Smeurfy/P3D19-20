#include "plane.h"

Plane::Plane(){}

Plane::Plane(vector3 &p1, vector3 &p2, vector3 &p3) {
	vector3 v1, v2;
	vector3 n; //vai dar a normal
	float d;

	_p1 = p1;
	_p2 = p2;
	_p3 = p3;

	
	
	v1 = p2 - p1;
	v2 = p3 - p1;

	n = cross(v1, v2);
	d = -dot(p1, n); 

	_n = n.normalizado();
	_d = d / n.norma();

	
}
bool Plane::checkRayColision(Ray &ray, float *dist, vector3 *hitpoint) {
	float t;
	vector3 o = ray._o;
	vector3 d = ray._d;

	float dotNormalDirection = dot(_n, d);

	// plane and ray are parallel
	if (dotNormalDirection == 0) {
		return false;
	}

	t = -1 * ((dot(_n, o) + _d) / dotNormalDirection);

	//intersection is behind the origin of the ray;
	if (t < 0) {
		return false;
	}

	vector3 hitPoint = o + t * d;
	*dist = t;
	*hitpoint = hitPoint;

	return true;
}

vector3 Plane::getNormal(Ray &Ray, vector3 &point)
{
	return _n;
}

bool Plane::pointInShadow(Ray shadowRay) 
{
	float t;
	vector3 o = shadowRay._o;
	vector3 d = shadowRay._d;

	float dotNormalDirection = dot(_n, d);

	// plane and ray are parallel
	if (dotNormalDirection == 0) {
		return false;
	}

	t = -1 * ((dot(_n, o) + _d) / dotNormalDirection);

	//intersection is behind the origin of the ray;
	if (t < 0) {
		return false;
	}

	return true;

}
