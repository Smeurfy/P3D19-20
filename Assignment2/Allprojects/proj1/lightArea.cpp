#include "LightArea.h"

vector3 LightArea::compute_L_SoftShadows(vector3 hitpoint, vector3 s_light) 
{
	vector3 r = _pos + s_light._x * _a + s_light._y * _b;
	vector3 l = r - hitpoint;

	l = l.normalizado();

	return l;
}