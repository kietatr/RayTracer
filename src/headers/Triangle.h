//
//  Triangle.h
//  Created by Kiet Tran on 12/7/18.
//

#ifndef Triangle_h
#define Triangle_h

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"
#include "Ray.h"

class Triangle : public Object {
	Vect A, B, C;
	Vect normal; //perpendicular to the surface
	double distance; // b/w the Triangle center to the scene center
	Color color;
	
	
public:
	
	Triangle ();
	Triangle (Vect, Vect, Vect, Color);
	
	//method functions
	double getTriangleDistance ();
	Color getColor ();
	
	//ray-Triangle intersection
	//normal at any point on the Triangle = normal of the entire Triangle
	Vect getTriangleNormal ();
	
	Vect getNormalAt (Vect);
	
	// ray intersecting with the Triangle
	double findIntersection (Ray);
};

#endif /* Triangle_h */

