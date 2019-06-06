#include "vector3.h"

// -- Constructor --
vector3::vector3() {

}

// -- Constructor --
vector3::vector3(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

// -- Data --
float* vector3::data() {
	float* v = new float[3];

	v[0] = _x;
	v[1] = _y;
	v[2] = _z;

	return v;
}


// -- Read --
vector3 vector3::readVc3() {
	std::string aAux, bAux, cAux;
	float x, y, z;

	std::cout << "A vector 3D have the structure v = (a, b, c)\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);
	std::cout << "Please introduce your c:\n";
	getline(std::cin, cAux);

	x = std::stof(aAux);
	y = std::stof(bAux);
	z = std::stof(cAux);

	vector3 v(x, y, z);
	std::cout << "The vector " << "(" << x << ", " << y << ", " << z << ") " << "was created\n";

	return v;
}


// -- Print --
void vector3::printVc3() {
	std::cout << "(" << _x << "," << _y << "," << _z << ")" << "\n";
}


// -- Norma --
float vector3::norma() {
	float s = pow(_x, 2) + pow(_y, 2) + pow(_z, 2);
	float n = sqrt(s);
	return n;
}

// -- Normalizado --
const vector3 vector3::normalizado() {
	float n = norma();
	float x = _x / n;
	float y = _y / n;
	float z = _z / n;

	vector3 v(x, y, z);
	return v;
}


// Overloading operator =
const vector3 vector3::operator=(const vector3& v) {
	_x = v._x;
	_y = v._y;
	_z = v._z;
	return *this;
}


// Overloading operator ==
const bool vector3::operator==(const vector3& vc3) {
	float a = abs(_x - vc3._x);
	float b = abs(_y - vc3._y);
	float c = abs(_z - vc3._z);
	float e = (1e-5);
	if ((a < e) && (b < e) && (c < e)) {
		return true;
	}
	return false;
	//return _x == vc3._x && _y == vc3._y && _z == vc3._z;
}


// Overloading operator +
const vector3 operator+(const vector3& v1, const vector3& v2) {
	float a = v1._x + v2._x;
	float b = v1._y + v2._y;
	float c = v1._z + v2._z;

	vector3 auxVc(a, b, c);
	return auxVc;
}

const vector3 operator+(const vector3& v1, const float val) {
	float a = v1._x + val;
	float b = v1._y + val;
	float c = v1._z + val;

	vector3 auxVc(a, b, c);
	return auxVc;
}


// Overloading operator -
const vector3 operator-(const vector3& v1, const vector3& v2) {
	float a = v1._x - v2._x;
	float b = v1._y - v2._y;
	float c = v1._z - v2._z;

	vector3 auxVc(a, b, c);
	return auxVc;
}

const vector3 operator-(const vector3& v1, const float val) {
	float a = v1._x - val;
	float b = v1._y - val;
	float c = v1._z - val;

	vector3 auxVc(a, b, c);
	return auxVc;
}


// Overloading operator *
const vector3 operator*(const vector3& v, const float x) {
	float a = v._x * x;
	float b = v._y * x;
	float c = v._z * x;

	vector3 auxVc(a, b, c);
	return auxVc;
}

const vector3 operator*(const float x,const vector3& v) {
	return v * x;
}

// -- Dot Product (Intern Product) --
float dot(const vector3& v1, const vector3& v2) {
	float a = v1._x * v2._x;
	float b = v1._y * v2._y;
	float c = v1._z * v2._z;

	return a + b + c;
}


// -- Cross product (external product) --
vector3 cross(const vector3& v1, const vector3& v2) {
	float a = (v1._y * v2._z) - (v1._z * v2._y);
	float b = (v1._z * v2._x) - (v1._x * v2._z);
	float c = (v1._x * v2._y) - (v1._y * v2._x);

	vector3 auxVc(a, b, c);
	return auxVc;
}

// learp
const vector3 learp(const vector3& p0, const vector3& p1, const float k) {
	if (0 <= k && k <= 1) {
		// (1-a)p0 + ap1
		float aux = 1 - k;
		vector3 v1 = aux * p0;
		vector3 v2 = k * p1;
		vector3 v3 = v1 + v2;
		return v3;
	}
	else {
		std::cout << "Invalide k, k should be between 0 and 1.\n You use: " << k << "\n";
	}
}