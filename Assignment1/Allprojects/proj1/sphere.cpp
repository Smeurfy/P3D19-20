#include "sphere.h"

Sphere::Sphere(){}

Sphere::Sphere(vector3 &c, float r) {
	_c = c;
	_r = r;
}

bool Sphere::checkRayColision(Ray &ray, float *dist, vector3 *hitpoint) {
	vector3 origin = ray._o;
	vector3 direction = ray._d;
	float radiusPow = pow(_r, 2);


	//distance between ray origin and centre of the sphere
	float distPow = pow(_c._x - origin._x,2) + pow(_c._y - origin._y, 2) + pow(_c._z - origin._z, 2);
	if (distPow == radiusPow) {
		return false;
	}

	float b = direction._x * (_c._x - origin._x)
		+ direction._y * (_c._y - origin._y)
		+ direction._z * (_c._z - origin._z);

	if (distPow > radiusPow && b < 0)
		return false;

	float r = (b * b) - distPow + radiusPow;
	if (r < 0)
		return false;

	float t;
	if (distPow > radiusPow)
		t = b - sqrt(r);
	else
		t = b + sqrt(r);

	vector3 hitPoint = origin + t * direction;

	*dist = t;
	*hitpoint = hitPoint;

	return true;
}

vector3 Sphere::getNormal(Ray &ray, vector3 &hitPoint)
{
	vector3 norm;
	//distance between ray origin and centre of the sphere
	float distPow = pow(_c._x - ray._o._x, 2) + pow(_c._y - ray._o._y, 2) + pow(_c._z - ray._o._z, 2);

	if (distPow >= _r * _r) 
	{
		norm = (hitPoint - _c) * (1 / _r);
	}
	else
	{
		norm = -1 * (hitPoint - _c) * (1 / _r);
	}

	return norm;
}

bool Sphere::pointInShadow(Ray shadowRay)
{
	vector3 origin = shadowRay._o;
	vector3 direction = shadowRay._d;
	float radiusPow = pow(_r, 2);

	//distance between ray origin and centre of the sphere
	float distPow = pow(_c._x - origin._x, 2) + pow(_c._y - origin._y, 2) + pow(_c._z - origin._z, 2);
	if (distPow == radiusPow) {
		return false;
	}

	float b = direction._x * (_c._x - origin._x)
		+ direction._y * (_c._y - origin._y)
		+ direction._z * (_c._z - origin._z);

	if (distPow > radiusPow && b < 0)
		return false;

	float r = (b * b) - distPow + radiusPow;
	if (r < 0)
		return false;

	return true;

}

float Sphere::exitRayIndex(Ray ray) 
{
	//distance between ray origin and centre of the sphere
	float distPow = pow(_c._x - ray._o._x, 2) + pow(_c._y - ray._o._y, 2) + pow(_c._z - ray._o._z, 2);

	//Sphere is in front of the ray
	if (distPow > _r * _r) {
		return _mat._index_of_refraction;
	}
	else
		return 1.0f;

}

float Sphere::enterRayIndex(Ray ray)
{
	//distance between ray origin and centre of the sphere
	float distPow = pow(_c._x - ray._o._x, 2) + pow(_c._y - ray._o._y, 2) + pow(_c._z - ray._o._z, 2);

	//Sphere is in front of the ray
	if (distPow > _r * _r) {
		return _mat._index_of_refraction;
	}
	else
		return 1.0f;

}
