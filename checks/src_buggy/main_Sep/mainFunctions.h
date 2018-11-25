//
//  mainFunctions.h
//  Created by Kiet Tran on 11/24/18.
//

#ifndef mainFunctions_h
#define mainFunctions_h

#include <vector>
#include <cstdio>
#include <cmath>

#include "Color.h"
#include "Vect.h"
#include "Object.h"
#include "Source.h"

using namespace std;

struct RGB {
	double r;
	double g;
	double b;
};

void saveimage (const char *filename, int w, int h, int dpi, RGB *data);
int closestObject(vector<double> intersections);
Color getColorAt(Vect inter_position, Vect inter_ray_direction, vector<Object*> scene_objects, int closest_object, vector<Source*> light_sources, double accuracy, double ambientlight);

#endif /* mainFunctions_h */
