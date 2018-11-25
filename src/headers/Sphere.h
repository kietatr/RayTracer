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
	
	Vect getSphereCenter ();
	double getSphereRadius ();
	Color getColor ();
	
	Vect getNormalAt(Vect);
	double findIntersection(Ray); ////why virtual
};


#endif /* Sphere_h */

