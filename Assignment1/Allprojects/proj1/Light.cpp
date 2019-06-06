#include "Light.h"

Light::Light(){} //empty

Light::Light(vector3 &pos, vector3 &color) {
	_pos  = pos;
	_color = color;
}

vector3 Light::compute_L(vector3 &hitPoint) 
{
	vector3 aux = _pos - hitPoint;
	aux = aux.normalizado();
	return aux;
}
