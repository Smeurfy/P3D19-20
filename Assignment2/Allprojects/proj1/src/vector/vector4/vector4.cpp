#include "vector4.h"

// -- Constructor --
vector4::vector4() {}

vector4::vector4(float a, float b, float c, float d) {
	_x = a;
	_y = b;
	_z = c;
	_w = d;
}

// -- Data --
float* vector4::data() {
	float* v = new float[4];

	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
	v[3] = _w;

	return v;
}

const float vector4::getVTreshhold() {
	return _vThreshold;
}

// -- Read --
vector4 vector4::readVc4() {
	std::string aAux, bAux, cAux, dAux;
	float a, b, c, d;

	std::cout << "A vector 4D have the structure v = (a, b, c, d)\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);
	std::cout << "Please introduce your c:\n";
	getline(std::cin, cAux);
	std::cout << "Please introduce your d:\n";
	getline(std::cin, dAux);

	a = std::stof(aAux);
	b = std::stof(bAux);
	c = std::stof(cAux);
	d = std::stof(dAux);

	vector4 v(a, b, c, d);
	std::cout << "The vector " << "(" << a << ", " << b << ", " << c << ", " << d << ") " << "was created\n";

	return v;
}


// -- Print --
void vector4::printVc4() {
	std::cout << "(" << _x << "," << _y << "," << _z << "," << _w << ")" << "\n";
}

const void vPrint(const std::string s, const vector4& v){
	std::cout << s << " = (" << v._x << ", " << v._y << ", " << v._z << ", " << v._w << ")" << std::endl;
}

// Normalize
const vector4 vNormalize(const vector4& v){
	vector4 vn;
	float s = 1 / (v._w * sqrt(v._x*v._x + v._y*v._y + v._z*v._z));
	vn._x = v._x * s;
	vn._y = v._y * s;
	vn._z = v._z * s;
	vn._w = 1.0f;
	return vn;
}

// Overloading operator =
vector4 vector4::operator=(const vector4& v) {
	vector4 vCopy(v._x, v._y, v._z, v._w);

	return vCopy;
}


// Overloading operator ==
bool vector4::operator==(const vector4& vc4) {
	return _x == vc4._x && _y == vc4._y && _z == vc4._z && _w == vc4._w;
}

const bool vEqual(const vector4& v0, const vector4& v1){
	vector4 vecAux;
	const float vThreshold = vecAux.getVTreshhold();
	return (fabs(v0._x - v1._x) < vThreshold && fabs(v0._y - v1._y) < vThreshold &&
		fabs(v0._z - v1._z) < vThreshold && fabs(v0._w - v1._w) < vThreshold);
}

// Overloading operator +
const vector4 operator+(const vector4& vc1, const vector4& vc2) {
	float a = vc1._x + vc2._x;
	float b = vc1._y + vc2._y;
	float c = vc1._z + vc2._z;
	float d = vc1._w + vc2._w;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}


// Overloading operator -
const vector4 operator-(const vector4& vc1, const vector4& vc2) {
	float a = vc1._x - vc2._x;
	float b = vc1._y - vc2._y;
	float c = vc1._z - vc2._z;
	float d = vc1._w - vc2._w;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}


// Overloading operator *
const vector4 operator* (const vector4& vc, const float k){
	float a = vc._x * k;
	float b = vc._y * k;
	float c = vc._z * k;
	float d = vc._w * k;

	vector4 auxVc(a, b, c, d);
	return auxVc;
}

const vector4 operator* (const float k, const vector4& vc) {
	return vc * k;
}

// learp
/*const vector4 learp(const vector4& p0, const vector4& p1, const float k) {
	if (0 <= k && k <= 1) {
		// (1-a)p0 + ap1
		return vector4(((1 - k) * p0) + ((k)* p1));
	} 
	else {
		std::cout << "Invalide k, k should be between 0 and 1.\n You use: " << k << "\n";
	}
}*/