#include "grid.h"

Grid::Grid() {
	nx = 0;
	ny = 0;
	nz = 0;
}

void Grid::add_object(Object *object) {
	objects.push_back(object);
}

void Grid::calculate_bounding_box(){ //Slide 9
	vector3 min = vector3(INFINITY, INFINITY, INFINITY);
	vector3 max = vector3(-INFINITY, -INFINITY, -INFINITY);

	AABB objectBox;
	size_t n = objects.size();

	//Check grid's bounding box coordinates by checking every object's boundind box
	for(int j = 0; j < n; j++){
		objectBox = objects[j]->boundingBox;

		// Bounding box minimum coordinate
		if (objectBox.xmin < min._x) {
			min._x = objectBox.xmin;
		}
		if (objectBox.ymin < min._y) {
			min._y = objectBox.ymin;
		}
		if (objectBox.zmin < min._z) {
			min._z = objectBox.zmin;
		}

		// Bounding box maximum coordinate
		if (objectBox.xmax > max._x) {
			max._x = objectBox.xmax;
		}
		if (objectBox.ymax > max._y) {
			max._y = objectBox.ymax;
		}
		if (objectBox.zmax > max._z) {
			max._z = objectBox.zmax;
		}
	}

	//Offset
	min = min - EPSILON;
	max = max + EPSILON;

	boundingBox.set_bounding_box(min, max);
}

void Grid::setup_cells() {

	// Number of objects
	size_t n = objects.size();
	printf("Number of objects in the grid = %ld\n", n);

	//Compute grid's bounding box
	calculate_bounding_box();

	vector3 p0 = vector3(boundingBox.xmin, boundingBox.ymin, boundingBox.zmin);
	vector3 p1 = vector3(boundingBox.xmax, boundingBox.ymax, boundingBox.zmax);


	

	// Grid dimensions in world coordinates
	vector3 w = p1 - p0;

	// Multiplying factor
	double m = GRID_M_FACTOR;

	//Raíz cúbica
	double s = cbrt((w._x * w._y * w._z) / n);

	//Number of cells in each axis
	nx = (m * w._x / s) + 1;
	ny = (m * w._y / s) + 1;
	nz = (m * w._z / s) + 1;

	//Total number of cells
	int num_cells = nx * ny * nz;
	printf("Number of grid cells = %d\n", num_cells);
	//Requests that the vector capacity be at least enough to contain n elements.
	cells.reserve(num_cells+1);

	//Initialize cells
	std::vector<Object*> empty;
	for (int i = 0; i < num_cells; i++) {
		cells.push_back(empty);
	}

	AABB objectBox;
	int index;

	for (int j = 0; j < n; j++) {
		objectBox = objects[j]->boundingBox;

		//Slide 14
		//Compute indices of both cells that contain min and max coord of obj bbox
		int ixmin = clamp((objectBox.xmin - p0._x) * nx / (p1._x - p0._x), 0.0, nx - 1);
		int iymin = clamp((objectBox.ymin - p0._y) * ny / (p1._y - p0._y), 0.0, ny - 1);
		int izmin = clamp((objectBox.zmin - p0._z) * nz / (p1._z - p0._z), 0.0, nz - 1);
		int ixmax = clamp((objectBox.xmax - p0._x) * nx / (p1._x - p0._x), 0.0, nx - 1);
		int iymax = clamp((objectBox.ymax - p0._y) * ny / (p1._y - p0._y), 0.0, ny - 1);
		int izmax = clamp((objectBox.zmax - p0._z) * nz / (p1._z - p0._z), 0.0, nz - 1);

		//Insert obj to the overlaped cells
		for (int iz = izmin; iz <= izmax; iz++){
			for (int iy = iymin; iy <= iymax; iy++){
				for (int ix = ixmin; ix <= ixmax; ix++) {
					index = ix + nx * iy + nx * ny * iz;
					cells[index].push_back(objects[j]);
				}
			}
		}
	}
	printf("Grid cells are ready\n");
}

bool Grid::checkRayColision(Ray &ray, Object **hitobject, vector3 *hitpoint) {

	//Ray origin coords
	float ox = ray._o._x;
	float oy = ray._o._y;
	float oz = ray._o._z;

	//Ray direction coords
	float dx = ray._d._x;
	float dy = ray._d._y;
	float dz = ray._d._z;

	//Grid bounding box coords
	float x0 = boundingBox.xmin;
	float y0 = boundingBox.ymin;
	float z0 = boundingBox.zmin;
	float x1 = boundingBox.xmax;
	float y1 = boundingBox.ymax;
	float z1 = boundingBox.zmax;

	//Units for ray movement
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;


	/****** CHECK RAY INTERSECTION WITH BOUNDING BOX ******/ //Slide 35
	float a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	float b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	float c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;

	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	if (t0 > t1)
		return(false);
	/****** END ******/


	//Initial Cell coordinates
	int ix, iy, iz;

	// Check if ray is inside the grid bounding box
	if (boundingBox.inside(ray._o)) {  //Does the ray start inside the grid?
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else {
		vector3 p = ray._o + ray._d * t0;  //Initial hit point with grid's bounding box
		ix = clamp((p._x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p._y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p._z - z0) * nz / (z1 - z0), 0, nz - 1);
	}


	//Ray parameter increments per cell in the x, y, and z directions
	double dtx = (tx_max - tx_min) / nx;
	double dty = (ty_max - ty_min) / ny;
	double dtz = (tz_max - tz_min) / nz;

	double 	tx_next, ty_next, tz_next; //Positions in the grid
	int 	ix_step, iy_step, iz_step; //To travel along the ray
	int 	ix_stop, iy_stop, iz_stop; //To check if we are outside the grid


	// Compute tnext (depends on ray direction)
	// For x direction 
	if (dx > 0) {
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = +1;
		ix_stop = nx;
	}
	else {
		tx_next = tx_min + (nx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dx == 0.0) {
		tx_next = INFINITY;
		ix_step = -1;
		ix_stop = -1;
	}


	// For y direction
	if (dy > 0) {
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else {
		ty_next = ty_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dy == 0.0) {
		ty_next = INFINITY;
		iy_step = -1;
		iy_stop = -1;
	}


	// For z direction
	if (dz > 0) {
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else {
		tz_next = tz_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}

	if (dz == 0.0) {
		tz_next = INFINITY;
		iz_step = -1;
		iz_stop = -1;
	}



	std::vector<Object*> objects; //Holds the cell's objects

	//Grid traversal cycle  SLIDE 22
	while (true) {
		objects = cells[ix + nx * iy + nx * ny * iz]; //Contains cell specific objects

		if (tx_next < ty_next && tx_next < tz_next) {
			if (objects.size() != 0) {

				bool hit = false;
				float dist;
				vector3 hitPoint;
				Object *closeObj = nullptr;
				float closestDist = FLT_MAX;
				vector3 closestHitPoint;

				//The usual intersection algorithm, but this time for the cell's objects only
				for (auto &obj : objects) {
					if (obj->checkRayColision(ray, &dist, &hitPoint) == true) {

						if (dist < closestDist) {
							hit = true;
							closestDist = dist;
							closeObj = obj;
							closestHitPoint = hitPoint;
						}
					}
				}
				if (hit == true && closestDist <= tx_next) {
					if (hitobject != nullptr)
						*hitobject = closeObj;
					if (hitpoint != nullptr)
						*hitpoint = closestHitPoint;
					return true;
				}
			}
			tx_next += dtx;
			ix += ix_step;

			if (ix == ix_stop) /* Outside grid */
				return (false);
		}
		else {
			if (ty_next < tz_next) {
				if (objects.size() != 0) {
					
					bool hit = false;
					float dist;
					vector3 hitPoint;
					Object *closeObj = nullptr;
					float closestDist = FLT_MAX;
					vector3 closestHitPoint;

					//The usual intersection algorithm, but this time for the cell's objects only
					for (auto &obj : objects) {
						if (obj->checkRayColision(ray, &dist, &hitPoint) == true) {

							if (dist < closestDist) {
								hit = true;
								closestDist = dist;
								closeObj = obj;
								closestHitPoint = hitPoint;
							}
						}
					}
					if (hit == true && closestDist <= tx_next) {
						if (hitobject != nullptr)
							*hitobject = closeObj;
						if (hitpoint != nullptr)
							*hitpoint = closestHitPoint;
						return true;
					}
				}

				ty_next += dty;
				iy += iy_step;

				if (iy == iy_stop) /* Outside grid */
					return (false);
			}
			else {
				if (objects.size() != 0) {

					bool hit = false;
					float dist;
					vector3 hitPoint;
					Object *closeObj = nullptr;
					float closestDist = FLT_MAX;
					vector3 closestHitPoint;

					//The usual intersection algorithm, but this time for the cell's objects only
					for (auto &obj : objects) {
						if (obj->checkRayColision(ray, &dist, &hitPoint) == true) {

							if (dist < closestDist) {
								hit = true;
								closestDist = dist;
								closeObj = obj;
								closestHitPoint = hitPoint;
							}
						}
					}
					if (hit == true && closestDist <= tx_next) {
						if (hitobject != nullptr)
							*hitobject = closeObj;
						if (hitpoint != nullptr)
							*hitpoint = closestHitPoint;
						return true;
					}
				}

				tz_next += dtz;
				iz += iz_step;

				if (iz == iz_stop) /* Outside grid */
					return (false);
			}
		}
	}
}



bool Grid::checkShadowRayColision(Ray &ray) {

	//Ray origin coords
	float ox = ray._o._x;
	float oy = ray._o._y;
	float oz = ray._o._z;

	//Ray direction coords
	float dx = ray._d._x;
	float dy = ray._d._y;
	float dz = ray._d._z;

	//Grid bounding box coords
	float x0 = boundingBox.xmin;
	float y0 = boundingBox.ymin;
	float z0 = boundingBox.zmin;
	float x1 = boundingBox.xmax;
	float y1 = boundingBox.ymax;
	float z1 = boundingBox.zmax;

	//Units for ray movement
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;


	/****** CHECK RAY INTERSECTION WITH BOUNDING BOX ******/
	float a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	float b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	float c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;

	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	if (t0 > t1)
		return(false);
	/****** END ******/


	//Initial Cell coordinates
	int ix, iy, iz;

	// Check if ray is inside the grid bounding box
	if (boundingBox.inside(ray._o)) {  //Does the ray start inside the grid?
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else {
		vector3 p = ray._o + ray._d * t0;  //Initial hit point with grid's bounding box
		ix = clamp((p._x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p._y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p._z - z0) * nz / (z1 - z0), 0, nz - 1);
	}


	//Ray parameter increments per cell in the x, y, and z directions
	double dtx = (tx_max - tx_min) / nx;
	double dty = (ty_max - ty_min) / ny;
	double dtz = (tz_max - tz_min) / nz;

	double 	tx_next, ty_next, tz_next; //Positions in the grid
	int 	ix_step, iy_step, iz_step; //To travel along the ray
	int 	ix_stop, iy_stop, iz_stop; //To check if we are outside the grid


									   // Compute tnext (depends on ray direction)
									   // For x direction 
	if (dx > 0) {
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = +1;
		ix_stop = nx;
	}
	else {
		tx_next = tx_min + (nx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dx == 0.0) {
		tx_next = INFINITY;
		ix_step = -1;
		ix_stop = -1;
	}


	// For y direction
	if (dy > 0) {
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else {
		ty_next = ty_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dy == 0.0) {
		ty_next = INFINITY;
		iy_step = -1;
		iy_stop = -1;
	}


	// For z direction
	if (dz > 0) {
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else {
		tz_next = tz_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}

	if (dz == 0.0) {
		tz_next = INFINITY;
		iz_step = -1;
		iz_stop = -1;
	}



	std::vector<Object*> objects; //Holds the cell's objects

	//Grid traversal cycle
	while (true) {
		objects = cells[ix + nx * iy + nx * ny * iz];
		if (objects.size() != 0) {
			
			//intersect Ray with all objects to check if there is shadow
			for (auto &obj : objects) {
				if (obj->pointInShadow(ray) == true) {
					return true;
				}
			}
		}
		if (tx_next < ty_next && tx_next < tz_next) {

			tx_next += dtx;
			ix += ix_step;

			if (ix == ix_stop)
				return (false);
		}
		else {
			if (ty_next < tz_next) {

				ty_next += dty;
				iy += iy_step;

				if (iy == iy_stop)
					return (false);
			}
			else {
				tz_next += dtz;
				iz += iz_step;

				if (iz == iz_stop)
					return (false);
			}
		}
	}
}