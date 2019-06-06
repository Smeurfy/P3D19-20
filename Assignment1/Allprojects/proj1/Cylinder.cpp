#include "Cylinder.h"

Cylinder::Cylinder() {}

Cylinder::Cylinder(vector3 &base, vector3 &apex, float bR, float aR) {
	_base = base;
	_apex = apex;
	_baseRadius = bR;
	_apexRadius = aR;
}

bool Cylinder::checkRayColision(Ray &ray, float *dist, vector3 *hitpoint) {
	float t;
	vector3 h_aux = _base - _apex;
	float height = h_aux.norma();

	float a = pow(ray._d._x, 2) + pow(ray._d._z, 2);
	float b = (2 * ray._o._x * ray._d._x) + (2 * ray._o._z * ray._d._z);
	float c = pow(ray._o._x, 2) + pow(ray._o._z, 2) - _baseRadius;

	float delta = pow(b, 2) - 4 * a * c;

	if (delta < 0)
	{
		return false;

	}
	//formula resolvente 
	float t1 = (-b + sqrt(delta)) / (2 * a);
	float t2 = (-b - sqrt(delta)) / (2 * a);

	if (t1 > t2)
	{
		float tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	float y1 = ray._o._y + t1 * ray._d._y;
	float y2 = ray._o._y + t2 * ray._d._y;

	if (y1 < _base._y)
	{
		if (y2 < _base._y)
			return false;
		else
		{
			// hit the cap
			float th = t1 + (t2 - t1) * (y1 + 1) / (y1 - y2);
			if (th <= 0)
				return false;

			vector3 hitPoint = ray._o + th * ray._d;
			_normal = vector3(0, -1, 0);

			*dist = th;
			*hitpoint = hitPoint;

			return true;
		}
	}
	else if (y1 >= _base._y && y1 <= _apex._y)
	{
		// hit the cylinder bit
		if (t1 <= 0)
			return false;

		vector3 hitPoint = ray._o + t1 * ray._d;
		_normal = vector3(hitPoint._x, 0, hitPoint._z).normalizado();

		*dist = t1;
		*hitpoint = hitPoint;

		return true;
	}
	else if (y1 > _apex._y)
	{
		if (y2 > _apex._y)
			return false;
		else
		{
			// hit the cap
			float th = t1 + (t2 - t1) * (y1 - 1) / (y1 - y2);
			if (th <= 0)
				return false;

			vector3 hitPoint = ray._o + th * ray._d;
			_normal = vector3(0, 1, 0);

			*dist = th;
			*hitpoint = hitPoint;

			return true;
		}
	}

	return false;
}
bool Cylinder::pointInShadow(Ray &ray) {
	float t;
	vector3 h_aux = _base - _apex;
	float height = h_aux.norma();

	float a = pow(ray._d._x, 2) + pow(ray._d._z, 2);
	float b = (2 * ray._o._x * ray._d._x) + (2 * ray._o._z * ray._d._z);
	float c = pow(ray._o._x, 2) + pow(ray._o._z, 2) - 1;

	float delta = pow(b, 2) - 4 * a * c;

	if (delta < 0)
	{
		return false;

	}
	//formula resolvente 
	float t1 = (-b + sqrt(delta)) / (2 * a);
	float t2 = (-b - sqrt(delta)) / (2 * a);

	if (t1 > t2)
	{
		float tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	float y1 = ray._o._y + t1 * ray._d._y;
	float y2 = ray._o._y + t2 * ray._d._y;

	if (y1 < _base._y)
	{
		if (y2 < _base._y)
			return false;
		else
		{
			// hit the cap
			float th = t1 + (t2 - t1) * (y1 + 1) / (y1 - y2);
			if (th <= 0)
				return false;

			return true;
		}
	}
	else if (y1 >= _base._y && y1 <= _apex._y)
	{
		// hit the cylinder bit
		if (t1 <= 0)
			return false;

		return true;
	}
	else if (y1 > _apex._y)
	{
		if (y2 > _apex._y)
			return false;
		else
		{
			// hit the cap
			float th = t1 + (t2 - t1) * (y1 - 1) / (y1 - y2);
			if (th <= 0)
				return false;

			return true;
		}
	}

	return false;
}

vector3 Cylinder::getNormal(Ray &ray, vector3 &hitPoint) {
	return _normal;
}