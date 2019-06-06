#include "ray.h"

int Ray::rayCount = 0;

Ray::Ray() {
	_o = vector3(0.0f, 0.0f, 0.0f);
	_d = vector3(0.0f, 0.0f, 0.0f);
	id = ++rayCount;
} //empty

Ray::Ray(vector3 o, vector3 d) {
	_o = o;
	_d = d.normalizado();
	id = ++rayCount;
}

void Ray::setO(vector3 o) {
	_o = o;
}

void Ray::setD(vector3 d) {
	_d = d;
}

bool Ray::isEmpty() 
{
	if (_o == vector3(0, 0, 0) && _d == vector3(0, 0, 0)) {
		return true;
	}
	else
		return false;
}