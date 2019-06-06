#pragma once
#include <vector>
#include "object.h"
#define EPSILON 1e-10
#define GRID_M_FACTOR 2

struct Grid : public Object {
	std::vector<std::vector<Object*>> cells;
	std::vector<Object*> objects;
	int nx;                         //Number of cells in x direction
	int ny;                         //Number of cells in y direction
	int nz;                         //Number of cells in z direction

	Grid();
	void setup_cells();
	void add_object(Object * object);
	//bool checkRayColision(Ray &ray, float *dist, vector3 *hitpoint);
	void calculate_bounding_box();

	bool checkRayColision(Ray &ray, Object **hitObject, vector3 *hitpoint);
	bool checkShadowRayColision(Ray &ray);

};