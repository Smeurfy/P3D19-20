#include "plane.h"

Plane::Plane(){}

Plane::Plane(float d, vector3 normal)
{
	_n = normal;
	_d = d / _n.norma();
}

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
	
	//Optimization
	if (ray.id == lastRay) {
		*dist = lastDist;
		*hitpoint = lastHitpoint;
		return true;
	}
	
	
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

	//Optimization
	lastRay = ray.id;
	lastDist = *dist;
	lastHitpoint = *hitpoint;

	return true;
}

vector3 Plane::getNormal(Ray &Ray, vector3 &point)
{
	return _n;
}

bool Plane::pointInShadow(Ray shadowRay) 
{

	//Optimization
	if (shadowRay.id == lastRay) {
		return true;
	}

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

	//Optimization
	lastRay = shadowRay.id;

	return true;
}

void Plane::calculate_bounding_box() {}
