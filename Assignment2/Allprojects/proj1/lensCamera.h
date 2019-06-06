#pragma once
#include "src/vector/vector3/vector3.h"
#include "camera.h"
#include "plane.h"


struct  LensCamera : public Camera {

	float _aperture;
	Plane focalPlane;

	LensCamera(Camera *cam, double aperture, double focal_dist) : Camera(cam->_backgroundC, cam->_eye, cam->_at, cam->_up, 
																		cam->_fovy, cam->nearP, cam->farP, cam->_ResX, cam->_ResY,
																		cam->_w, cam->_h)
	{
		_aperture = aperture;
		focalPlane = Plane(focal_dist, cam->_ze);
	}

	vector3 calcFocalPoint(Ray ray) 
	{
		vector3 hitPoint;
		float dist;
		focalPlane.checkRayColision(ray, &dist, &hitPoint);
		return hitPoint;
	};
	vector3 calcSamplePoint() 
	{
		float rand_x, rand_y;
		bool insideCirc = false;
		vector3 samplePoint;

		while (!insideCirc) {
			// -1 to 1
			rand_x = _aperture * 2 * (((rand() / (double)RAND_MAX)) - 0.5f);
			rand_y = _aperture * 2 * (((rand() / (double)RAND_MAX)) - 0.5f);

			samplePoint = _eye + _xe * rand_x + _ye * rand_y;
			
			if (pow(samplePoint._x - _eye._x, 2) + pow(samplePoint._y - _eye._y, 2) <= pow(_aperture,2)) 
			{
				insideCirc = true;
			}

		}

		return samplePoint;
	};
};