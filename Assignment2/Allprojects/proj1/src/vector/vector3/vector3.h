#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

struct vector3 {
	float _x, _y, _z;
	vector3();
	vector3(float, float, float);

	float* data();

	vector3 readVc3();
	void printVc3();

	float norma();
	const vector3 normalizado();

	const vector3 operator= (const vector3&);
	const bool operator== (const vector3&);

	friend float dot(const vector3&, const vector3&);
	friend  vector3 cross(const vector3&, const vector3&);

	friend const vector3 operator* (const vector3&, const float);
	friend const vector3 operator* (const float, const vector3&);
	friend const vector3 operator- (const vector3&, const vector3&);
	friend const vector3 operator- (const vector3&, const float);
	friend const vector3 operator+ (const vector3&, const vector3&);
	friend const vector3 operator+ (const vector3&, const float);
	
	friend const vector3 learp(const vector3& p0, const vector3& p1, const float k);
};