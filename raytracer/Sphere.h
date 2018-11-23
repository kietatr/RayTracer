//
//  Sphere.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Sphere_h
#define Sphere_h

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Sphere : public Object {
	Vect center;
	double radius;
	Color color;
	
public:
	
	// declarations
	Sphere();
	
	Sphere (Vect, double, Color);
	
	//method functions
	
	Vect getSphereCenter () {return center;}
	double getSphereRadius () {return radius;}
	Color getSphereColor () {return color;}
	
};

Sphere::Sphere () {
	center = Vect(0,0,0);
	radius = 1.0;
	color = Color(0.5,0.5,0.5,0);
}

Sphere::Sphere (Vect cen, double rad, Color col) {
	center = cen;
	radius = rad;
	color = col;
}


#endif /* Vect_h */

