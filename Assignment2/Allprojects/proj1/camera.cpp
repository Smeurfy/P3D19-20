#include "camera.h"

Camera::Camera() {}

Camera::Camera(vector3 background, vector3 eye, vector3 at, vector3 up, float fovy,
	float nP, float fP, int ResX, int ResY, float w, float h) 
{
	_backgroundC = background;
	_eye = eye;
	_at = at;
	_up = up;
	_fovy = fovy;
	nearP = nP;
	farP = fP;
	_ResX = ResX;
	_ResY = ResY;
	_w = w;
	_h = h;
	calc_Param();
}

void Camera::df() {
	//d = ||eye - at||
	vector3 aux = _eye - _at;
	_df = aux.norma();
}

void Camera::h_calc() {
	//h = 2d * tan(fov / 2)
	_h = ((2 * _df) * tan(_fovy / 2));
}

void Camera::w_calc() {
	//w = (ResX / ResY) * h
	_w = (((float)_ResX) / ((float)_ResY) * _h);
}

void Camera::ze_calc() {
	_ze = (1/_df) * (_eye - _at);
}

void Camera::xe_calc() {
	vector3 c = cross(_up, _ze);
	float n = c.norma();

	_xe = c * (1 / n);
}

void Camera::ye_calc() {
	_ye = cross(_ze, _xe);

}

void Camera::calc_Param() 
{
	df();
	h_calc();
	w_calc();
	ze_calc();
	xe_calc();
	ye_calc();
}

Ray Camera::calcPrimRay(float x, float y) {
	Ray ray;
	
	vector3 aux = -_df * _ze + _h * ((y / _ResY) - 0.5) * _ye +
		_w * ((x / _ResX) - 0.5) * _xe;
	
	ray._d = aux.normalizado(); 
	ray._o = _eye;

	return ray;
}

Ray Camera::calcJitteredRay(int x, int y, double i, double j) {
	Ray ray;

	vector3 aux = -_df * _ze + _h * (((y + j) / _ResY) - 0.5) * _ye +
		_w * (((x + i) / _ResX) - 0.5) * _xe;

	ray._d = aux.normalizado();
	ray._o = _eye;

	return ray;
}