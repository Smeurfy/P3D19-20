#pragma once
#include "material.h"
#include "ray.h"
#include "src/vector/vector3/vector3.h"
#include "Light.h"


struct Object {

	Material _mat;

	vector3 getDiffuse(Light &light, vector3 &normal, vector3 &lightDirection);
	vector3 getSpecular(Light &light, vector3 &normal, vector3 &lightDirection, vector3 &rayDirection);

	bool isReflective() { return _mat._ks > 0.0f; };
	bool isTranslucid() { return _mat._t > 0.0f; };

	virtual bool checkRayColision(Ray &ray, float *dist, vector3 *hitpoint) { return 0; };
	virtual vector3 getNormal(Ray &ray, vector3 &hitPoint) { vector3 a; return a; };
	virtual bool pointInShadow(Ray ray) { return 0; };

	virtual float exitRayIndex(Ray ray) { return 1.0f; };
	virtual float enterRayIndex(Ray ray) { return _mat._index_of_refraction; };
};
