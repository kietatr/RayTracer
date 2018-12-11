#ifndef App_h
#define App_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// new classes created from scratch
#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"

//classes for objects on screen
#include "Object.h"
#include "Source.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

#define MAX_RECURSION_DEPTH 5

struct RGB {
	double r;
	double g;
	double b;
};

void saveImage (const char *filename, int w, int h, int dpi, RGB *data);

int closestObject(vector<double> intersections);

Color getColorAt(Vect inter_position, Vect inter_ray_direction, vector<Object*> scene_objects, int closest_object, vector<Source*> light_sources, double accuracy, double ambient_light, const int &depth);

vector<Object*> drawCube(Vect center, double xWidth, double yWidth, double zWidth, Color color);

double mix(const double &a, const double &b, const double &mix);

Color mixColor(Color a, Color b, float mix);

#endif
