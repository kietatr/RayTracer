//
//  Vect.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Vect_h
#define Vect_h

#include "math.h"

class Vect{
	double x, y, z;
	
	public:
	
	Vect ();
	Vect (double, double , double);
	
	//method functions
	
	double getX ();
	double getY ();
	double getZ ();
	
	//linear operations
	
	double magnitude (); //magnitude
	Vect normalize (); // normalizing a vector
	double dot (Vect); //dot product of .this with v
	Vect cross (Vect); //cross product of .this with v
	
	
	Vect negative (); //opposite direction
	Vect add (Vect); //this + v
	Vect subtract (Vect); // this - v
	Vect multiply (double);
	Vect reflect (Vect);
};

#endif /* Vect_h */

