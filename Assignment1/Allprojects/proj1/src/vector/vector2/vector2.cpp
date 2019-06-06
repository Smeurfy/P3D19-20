#include "vector2.h"

// -- Constructor --
vector2::vector2() {}

vector2::vector2(float x, float y) {
	_x = x;
	_y = y;
}

// -- Data --
float* vector2::data() {
	float* v = new float[2];

	v[0] = _x;
	v[1] = _y;

	return v;
}


// -- Read --
vector2 vector2::readVc2() {
	std::string aAux, bAux;
	float x, y;

	std::cout << "A vector 2D have the structure v = (a, b)\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);

	x = std::stof(aAux);
	y = std::stof(bAux);

	vector2 v(x, y);
	std::cout << "The vector " << "(" << x << ", " << y << ") " << "was created\n";

	return v;
}

// -- Print --
void vector2::printVc2() {
	std::cout << "(" << _x << "," << _y << ")" << "\n";
}


// Overloading operator =
vector2 vector2::operator=(const vector2& v2) {
	vector2 vCopy(v2._x, v2._y);

	return vCopy;
}


// Overloading operator ==
bool vector2::operator==(const vector2& v2) {
	return _x == v2._x && _y == v2._y;
}


// Overloading operator +
vector2 vector2::operator+(const vector2& v2) {
	float x = _x + v2._x;
	float y = _y + v2._y;

	vector2 auxVc(x, y);
	return auxVc;
}


// Overloading operator -
vector2 vector2::operator-(const vector2& v2) {
	float x = _x - v2._x;
	float y = _y - v2._y;

	vector2 auxVc(x, y);
	return auxVc;
}


// Overloading operator *
vector2 vector2::operator*(const float k) {
	float x = _x * k;
	float y = _y * k;

	vector2 auxVc(x, y);
	return auxVc;
}