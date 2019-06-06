#include "material.h"

Material::Material() {} //empty

Material::Material(vector3 &color, float kd, float ks, float shine, float t, float index) {
	_rgb = color;
	_kd = kd;
	_ks = ks;
	_shine = shine;
	_t = t;
	_index_of_refraction = index;
}
