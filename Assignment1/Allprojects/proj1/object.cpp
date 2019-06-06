#include"src/vector/vector3/vector3.h"
#include"Light.h"
#include"object.h"

vector3 Object::getDiffuse(Light &light, vector3 &normal, vector3 &lightDirection)
{
	vector3 color = vector3(0.0f,0.0f,0.0f);
	float productLN = dot(lightDirection, normal);

	color._x = productLN * _mat._rgb._x * _mat._kd * light._color._x;
	color._y = productLN * _mat._rgb._y * _mat._kd * light._color._y;
	color._z = productLN * _mat._rgb._z * _mat._kd * light._color._z;

	return color;

}

vector3 Object::getSpecular(Light &light, vector3 &normal, vector3 &lightDirection, vector3 &rayDirection)
{
	vector3 color;
	vector3 h_aux = lightDirection + rayDirection*(-1);
	vector3 h = h_aux.normalizado();

	float dotNH = dot(normal, h);
	if (dotNH > 0) {
		color = pow(dotNH, _mat._shine) * _mat._ks * light._color;
	}

	return color;
}