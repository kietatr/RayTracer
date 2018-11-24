//
//  Plane.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Plane_h
#define Plane_h

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Plane : public Object {
	Vect normal; //perpendicular to the surface
	double distance; // b/w the plane center to the scene center
	Color color;
	
	
public:
	
	Plane ();
	Plane (Vect, double, Color);
	
	//method functions
	double getPlaneDistance ();
	Color getColor ();
	
	//ray-plane intersection
	//normal at any point on the plane = normal of the entire plane
	Vect getPlaneNormal ();
	
	Vect getNormalAt (Vect);
	
	// ray intersecting with the plane
	double findIntersection (Ray);
};

#endif /* Vect_h */

