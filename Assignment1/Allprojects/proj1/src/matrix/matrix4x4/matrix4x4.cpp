#include "matrix4x4.h"


// -- Constructor --
matrix4x4::matrix4x4(float a, float b, float c, float d, float e, float f, float g,
	float h, float i, float j, float k, float l, float m, float n, float o, float p) {
	_a = a;
	_b = b;
	_c = c;
	_d = d;
	_e = e;
	_f = f;
	_g = g;
	_h = h;
	_i = i;
	_j = j;
	_k = k;
	_l = l;
	_m = m;
	_n = n;
	_o = o;
	_p = p;
}

matrix4x4::matrix4x4(vector4& vc1, vector4& vc2, vector4& vc3, vector4& vc4) {
	_a = vc1._x;
	_b = vc2._x;
	_c = vc3._x;
	_d = vc4._x;
	_e = vc1._y;
	_f = vc2._y;
	_g = vc3._y;
	_h = vc4._y;
	_i = vc1._z;
	_j = vc2._z;
	_k = vc3._z;
	_l = vc4._z;
	_m = vc1._w;
	_n = vc2._w;
	_o = vc3._w;
	_p = vc4._w;
}

matrix4x4::matrix4x4(float lst[16]) {
	_a = lst[0];
	_b = lst[1];
	_c = lst[8];
	_d = lst[12];
	_e = lst[1];
	_f = lst[5];
	_g = lst[9];
	_h = lst[13];
	_i = lst[2];
	_j = lst[6];
	_k = lst[10];
	_l = lst[14];
	_m = lst[3];
	_n = lst[7];
	_o = lst[11];
	_p = lst[15];
}


// -- Data --
float* matrix4x4::data() {
	float* m = new float[16];

	m[0] = _a;
	m[1] = _b;
	m[2] = _c;
	m[3] = _d;
	m[4] = _e;
	m[5] = _f;
	m[6] = _g;
	m[7] = _h;
	m[8] = _i;
	m[9] = _j;
	m[10] = _k;
	m[11] = _l;
	m[12] = _m;
	m[13] = _n;
	m[14] = _o;
	m[15] = _p;

	return m;
}


// -- Read --
matrix4x4 matrix4x4::matrixRead() {
	std::string aAux, bAux, cAux, dAux, eAux, fAux, gAux, hAux, iAux, jAux, kAux, lAux, mAux, nAux, oAux, pAux;
	float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

	std::cout << "A matrix 4x4 have the structure:\n";
	std::cout << "a b c d\n";
	std::cout << "e f g h\n";
	std::cout << "i j k l\n";
	std::cout << "m n o p\n";
	std::cout << "Please introduce your a:\n";
	getline(std::cin, aAux);
	std::cout << "Please introduce your b:\n";
	getline(std::cin, bAux);
	std::cout << "Please introduce your c:\n";
	getline(std::cin, cAux);
	std::cout << "Please introduce your d:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your e:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your f:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your g:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your h:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your i:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your j:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your k:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your l:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your m:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your n:\n";
	getline(std::cin, dAux);
	std::cout << "Please introduce your o:\n";
	getline(std::cin, dAux);

	a = std::stof(aAux);
	b = std::stof(bAux);
	c = std::stof(cAux);
	d = std::stof(dAux);
	e = std::stof(eAux);
	f = std::stof(fAux);
	g = std::stof(gAux);
	h = std::stof(hAux);
	i = std::stof(iAux);
	j = std::stof(jAux);
	k = std::stof(kAux);
	l = std::stof(lAux);
	m = std::stof(mAux);
	n = std::stof(nAux);
	o = std::stof(oAux);
	p = std::stof(pAux);

	matrix4x4 mR(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
	std::cout << "A matrix 4x4 created:\n";
	mR.matrixPrint();

	return mR;
}


// -- Print --
void matrix4x4::matrixPrint() {
	std::cout << "\n";
	std::cout << "[ " << _a << " " << _b << " " << _c << " " << _d << " ]" << "\n";
	std::cout << "[ " << _e << " " << _f << " " << _g << " " << _h << " ]" << "\n";
	std::cout << "[ " << _i << " " << _j << " " << _k << " " << _l << " ]" << "\n";
	std::cout << "[ " << _m << " " << _n << " " << _o << " " << _p << " ]" << "\n";
	std::cout << "\n";
}


// -- Overloading = -
matrix4x4 matrix4x4::operator= (const matrix4x4& m) {
	//matrix4x4 mCopy(m._a, m._b, m._c, m._d, m._e, m._f, m._g, m._h, m._i, m._j, m._k, m._l, m._m, m._n, m._o, m._p);
	_a = m._a;
	_b = m._b;
	_c = m._c;
	_d = m._d;
	_e = m._e;
	_f = m._f;
	_g = m._g;
	_h = m._h;
	_i = m._i;
	_j = m._j;
	_k = m._k;
	_l = m._l;
	_m = m._m;
	_n = m._n;
	_o = m._o;
	_p = m._p;

	return *this;
}


// -- Overloading == --
bool matrix4x4::operator==(const matrix4x4& m1) {
	return _a == m1._a && _b == m1._b && _c == m1._c && _d == m1._d
		&& _e == m1._e && _f == m1._f && _g == m1._g && _h == m1._h
		&& _i == m1._i && _j == m1._j && _k == m1._k && _l == m1._l
		&& _m == m1._m && _n == m1._n && _o == m1._o && _p == m1._p;
}


// -- Overloading + --
matrix4x4 matrix4x4::operator+(const matrix4x4& m1) {
	float a = _a + m1._a;
	float b = _b + m1._b;
	float c = _c + m1._c;
	float d = _d + m1._d;
	float e = _e + m1._e;
	float f = _f + m1._f;
	float g = _g + m1._g;
	float h = _h + m1._h;
	float i = _i + m1._i;
	float j = _j + m1._j;
	float k = _k + m1._k;
	float l = _l + m1._l;
	float m = _m + m1._m;
	float n = _n + m1._n;
	float o = _o + m1._o;
	float p = _p + m1._p;

	matrix4x4 mSoma(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mSoma;
}


// -- Overloading - --
matrix4x4 matrix4x4::operator-(const matrix4x4& m1) {
	float a = _a - m1._a;
	float b = _b - m1._b;
	float c = _c - m1._c;
	float d = _d - m1._d;
	float e = _e - m1._e;
	float f = _f - m1._f;
	float g = _g - m1._g;
	float h = _h - m1._h;
	float i = _i - m1._i;
	float j = _j - m1._j;
	float k = _k - m1._k;
	float l = _l - m1._l;
	float m = _m - m1._m;
	float n = _n - m1._n;
	float o = _o - m1._o;
	float p = _p - m1._p;

	matrix4x4 mSub(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mSub;
}


// -- Overloading * --
// Scalar
matrix4x4 matrix4x4::operator*(const float x) {
	float a = _a * x;
	float b = _b * x;
	float c = _c * x;
	float d = _d * x;
	float e = _e * x;
	float f = _f * x;
	float g = _g * x;
	float h = _h * x;
	float i = _i * x;
	float j = _j * x;
	float k = _k * x;
	float l = _l * x;
	float m = _m * x;
	float n = _n * x;
	float o = _o * x;
	float p = _p * x;

	matrix4x4 mMut(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mMut;
}

// Another matrix4x4
matrix4x4 matrix4x4::operator*(const matrix4x4& m1) {
	float a = (_a * m1._a) + (_b * m1._e) + (_c * m1._i) + (_d * m1._m);
	float b = (_a * m1._b) + (_b * m1._f) + (_c * m1._j) + (_d * m1._n);
	float c = (_a * m1._c) + (_b * m1._g) + (_c * m1._k) + (_d * m1._o);
	float d = (_a * m1._d) + (_b * m1._h) + (_c * m1._l) + (_d * m1._p);

	float e = (_e * m1._a) + (_f * m1._e) + (_g * m1._i) + (_h * m1._m);
	float f = (_e * m1._b) + (_f * m1._f) + (_g * m1._j) + (_h * m1._n);
	float g = (_e * m1._c) + (_f * m1._g) + (_g * m1._k) + (_h * m1._o);
	float h = (_e * m1._d) + (_f * m1._h) + (_g * m1._l) + (_h * m1._p);

	float i = (_i * m1._a) + (_j * m1._e) + (_k * m1._i) + (_l * m1._m);
	float j = (_i * m1._b) + (_j * m1._f) + (_k * m1._j) + (_l * m1._n);
	float k = (_i * m1._c) + (_j * m1._g) + (_k * m1._k) + (_l * m1._o);
	float l = (_i * m1._d) + (_j * m1._h) + (_k * m1._l) + (_l * m1._p);

	float m = (_m * m1._a) + (_n * m1._e) + (_o * m1._i) + (_p * m1._m);
	float n = (_m * m1._b) + (_n * m1._f) + (_o * m1._j) + (_p * m1._n);
	float o = (_m * m1._c) + (_n * m1._g) + (_o * m1._k) + (_p * m1._o);
	float p = (_m * m1._d) + (_n * m1._h) + (_o * m1._l) + (_p * m1._p);

	matrix4x4 mMut(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

	return mMut;
}

// By a vector
vector4 matrix4x4::operator* (const vector4& vc) {
	float a = (_a * vc._x) + (_b * vc._y) + (_c * vc._z) + (_d * vc._w);
	float b = (_e * vc._x) + (_f * vc._y) + (_g * vc._z) + (_h * vc._w);
	float c = (_i * vc._x) + (_j * vc._y) + (_k * vc._z) + (_l * vc._w);
	float d = (_m * vc._x) + (_n * vc._y) + (_o * vc._z) + (_p * vc._w);

	vector4 res(a, b, c, d);
	return res;
}


// -- Determinant --
float matrix4x4::detM4x4() {

	return ((_a * _f * _k * _p) - (_a * _f * _l * _o) - (_a * _g * _j * _p) + (_a * _g * _l * _n) + (_a * _h * _j * _o) - (_a * _h * _k * _n)
		- (_b * _e * _k * _p) + (_b * _e * _l * _o) + (_b * _g * _i * _p) - (_b * _g * _l * _m) - (_b * _h * _i * _o) + (_b * _h * _k * _m)
		+ (_c * _e * _j * _p) - (_c * _e * _l * _n) - (_c * _f * _i * _p) + (_c * _f * _l * _m) + (_c * _h * _i * _n) - (_c * _h * _j * _m)
		- (_d * _e * _j * _o) + (_d * _e * _k * _n) + (_d * _f * _i * _o) - (_d * _f * _k * _m) - (_d * _g * _i * _n) + (_d * _g * _j * _m));
}


// -- Transpose --
matrix4x4 matrix4x4::transposeM4x4() {

	matrix4x4 mAux(_a, _e, _i, _m, _b, _f, _j, _n, _c, _g, _k, _o, _d, _h, _l, _p);

	return mAux;
}