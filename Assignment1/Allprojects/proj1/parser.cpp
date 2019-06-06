#include "parser.h";
#include "Light.h";
#include "plane.h";
#include "sphere.h";

using namespace std;

Parser::Parser(){} //empty

void Parser::parseNffFile(Camera *cam) {
	string line, token;
	//file name
	ifstream myfile("assets/mount_very_high.nff");
	stringstream completeLine;
	Material lastMaterial;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			completeLine.str("");
			completeLine.clear();
			completeLine << line;
			
			//completeLine >> ws;
			getline(completeLine, token, ' ');
			//backgorund color
			if (token == "b") 
			{
				getline(completeLine, token, ' ');
				cam->_backgroundC._x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_backgroundC._y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_backgroundC._z = strtof(token.c_str(), NULL);

			}
			else if (token == "from") 
			{
				getline(completeLine, token, ' ');
				cam->_eye._x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_eye._y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_eye._z = strtof(token.c_str(), NULL);
			}
			else if (token == "at") 
			{
				getline(completeLine, token, ' ');
				cam->_at._x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_at._y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_at._z = strtof(token.c_str(), NULL);
			}
			else if (token == "up")
			{
				getline(completeLine, token, ' ');
				cam->_up._x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_up._y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_up._z = strtof(token.c_str(), NULL);

			}
			else if (token == "angle") 
			{
				getline(completeLine, token, ' ');
				//recived in deg, need to pass to radians
				float deg = strtof(token.c_str(), NULL);
				cam->_fovy = deg * DEGTORAD;
			}
			else if (token == "hither")
			{
				getline(completeLine, token, ' ');
				cam->nearP = strtof(token.c_str(), NULL);
			}
			else if (token == "resolution")
			{
				getline(completeLine, token, ' ');
				cam->_ResX = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				cam->_ResY = strtof(token.c_str(), NULL);
			}
			else if (token == "l")
			{
				getline(completeLine, token, ' ');
				float x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float z = strtof(token.c_str(), NULL);
				vector3 aux_pos(x, y, z);

				getline(completeLine, token, ' ');
				float r = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float g = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float b = strtof(token.c_str(), NULL);
				vector3 aux_color(r, g, b);

				Light *light = new Light(aux_pos, aux_color);
				_lights.push_back(light);
			}
			else if (token == "f")
			{
				getline(completeLine, token, ' ');
				float r = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float g = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float b = strtof(token.c_str(), NULL);

				getline(completeLine, token, ' ');
				float kd = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float ks = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float shine = strtof(token.c_str(), NULL);

				getline(completeLine, token, ' ');
				float t = strtof(token.c_str(), NULL);

				getline(completeLine, token, ' ');
				float index = strtof(token.c_str(), NULL);
				vector3 color_aux(r, g, b);
				
				Material mat(color_aux, kd, ks, shine, t, index);
				lastMaterial = mat;
			}
			else if (token == "pl")
			{
				float x, y, z;
				
				getline(completeLine, token, ' ');
				x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				z = strtof(token.c_str(), NULL);
				vector3 v1(x, y, z);
				
				getline(completeLine, token, ' ');
				x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				z = strtof(token.c_str(), NULL);
				vector3 v2(x, y, z);
				
				getline(completeLine, token, ' ');
				x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				z = strtof(token.c_str(), NULL);
				vector3 v3(x, y, z);
				
				Plane *plane = new Plane(v1, v2, v3);
				plane->_mat = lastMaterial;
				_objects.push_back(plane);
			}
			else if (token == "p") {
				float x, y, z;
				//get num of vertices
				getline(completeLine, token, ' ');
				float num_vert = strtof(token.c_str(), NULL);

				if (num_vert == 3) { //triangle
					//make jump to next line
					getline(myfile, line, '\n');
					completeLine.str("");
					completeLine.clear();
					completeLine << line; //get the next line

					getline(completeLine, token, ' ');
					x = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					y = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					z = strtof(token.c_str(), NULL);
					vector3 v1(x, y, z);

					//make jump to next line
					getline(myfile, line, '\n');
					completeLine.str("");
					completeLine.clear();
					completeLine << line; //get the next line

					getline(completeLine, token, ' ');
					x = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					y = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					z = strtof(token.c_str(), NULL);
					vector3 v2(x, y, z);

					//make jump to next line
					getline(myfile, line, '\n');
					completeLine.str("");
					completeLine.clear();
					completeLine << line; //get the next line

					getline(completeLine, token, ' ');
					x = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					y = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					z = strtof(token.c_str(), NULL);
					vector3 v3(x, y, z);

					Triangle *triangle = new Triangle(v1, v2, v3);
					triangle->_mat = lastMaterial;
					_objects.push_back(triangle);
				}
				if (num_vert == 4) { //plane
					//make jump to next line
					getline(myfile, line, '\n');
					completeLine.str("");
					completeLine.clear();
					completeLine << line; //get the next line

					getline(completeLine, token, ' ');
					x = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					y = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					z = strtof(token.c_str(), NULL);
					vector3 v1(x, y, z);

					//make jump to next line
					getline(myfile, line, '\n');
					completeLine.str("");
					completeLine.clear();
					completeLine << line; //get the next line

					getline(completeLine, token, ' ');
					x = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					y = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					z = strtof(token.c_str(), NULL);
					vector3 v2(x, y, z);

					//make jump to next line
					getline(myfile, line, '\n');
					completeLine.str("");
					completeLine.clear();
					completeLine << line; //get the next line

					getline(completeLine, token, ' ');
					x = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					y = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					z = strtof(token.c_str(), NULL);
					vector3 v3(x, y, z);

					//make jump to next line
					getline(myfile, line, '\n');
					completeLine.str("");
					completeLine.clear();
					completeLine << line; //get the next line

					getline(completeLine, token, ' ');
					x = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					y = strtof(token.c_str(), NULL);
					getline(completeLine, token, ' ');
					z = strtof(token.c_str(), NULL);
					vector3 v4(x, y, z);

					Triangle *triangle1 = new Triangle(v1, v3, v2);
					triangle1->_mat = lastMaterial;
					_objects.push_back(triangle1);

					Triangle *triangle2 = new Triangle(v1, v4, v3);
					triangle2->_mat = lastMaterial;
					_objects.push_back(triangle2);
				}
			}
			else if (token == "s"){
				getline(completeLine, token, ' ');
				float x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				float z = strtof(token.c_str(), NULL);

				getline(completeLine, token, ' ');
				float r = strtof(token.c_str(), NULL);

				vector3 c_aux(x, y, z);
				Sphere *sphere = new Sphere(c_aux, r);
				sphere->_mat = lastMaterial;
				_objects.push_back(sphere);
			}
			else if (token == "c") {//Cone ou Cylinder
				float x, y, z, aR, bR;

				//make jump to next line
				getline(myfile, line, '\n');
				completeLine.str("");
				completeLine.clear();
				completeLine << line; //get the next line

				getline(completeLine, token, ' ');
				x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				z = strtof(token.c_str(), NULL);
				vector3 base(x, y, z);
				getline(completeLine, token, ' ');
				bR = strtof(token.c_str(), NULL);

				//make jump to next line
				getline(myfile, line, '\n');
				completeLine.str("");
				completeLine.clear();
				completeLine << line; //get the next line

				getline(completeLine, token, ' ');
				x = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				y = strtof(token.c_str(), NULL);
				getline(completeLine, token, ' ');
				z = strtof(token.c_str(), NULL);
				vector3 apex(x, y, z);
				getline(completeLine, token, ' ');
				aR = strtof(token.c_str(), NULL);

				if (aR != bR) { //Cone
					//not done
				}
				else { //cylinder
					Cylinder *cylinder = new Cylinder(base, apex, bR, aR);
					cylinder->_mat = lastMaterial;
					_objects.push_back(cylinder);
				}
			}
		}
		myfile.close();

		
	}

	else cout << "Unable to open file";

}

std::vector<Object*> Parser::getObjects() {
	return _objects;
}

std::vector<Light*> Parser::getLights() {
	return _lights;
}

