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
	
	// declarations
	Vect();
	
	Vect (double, double , double);
	
	//method functions
	
	double getX() {return x; }
	double getY() {return y; }
	double getZ() {return z; }
	
	//linear operations
	
	double magnitude (); //magnitude
	Vect normalize (); // normalizing a vector
	double dot (Vect); //dot product of .this with v
	Vect cross (Vect); //cross product of .this with v
	
	
	Vect negative (); //opposite direction
	Vect add (Vect); //this + v
	Vect subtract (Vect); // this - v
	Vect multiply (double);
};

Vect::Vect () {
	x = 0;
	y = 0;
	z = 0;
}

Vect::Vect (double a, double b, double c) {
	x = a;
	y = b;
	z = c;
}

double Vect::magnitude (){
	return sqrt((x*x) + (y*y) + (z*z));
}

Vect Vect::normalize (){
	return Vect (x/magnitude(), y/magnitude(), z/magnitude());
}

double  Vect::dot(Vect v){
	return (x*v.getX() + y*v.getY() + z*v.getZ());
}

Vect Vect::cross(Vect v){
	return Vect (y*v.getZ() - z*v.getY(),
				 z*v.getX() - x*v.getZ(),
				 x*v.getY() - y*v.getX());
}

Vect Vect::negative (){
	return Vect (-x, -y, -z);
}

Vect  Vect::add(Vect v){
	return Vect (x+v.getX() , y+v.getY() , z+v.getZ());
}

Vect  Vect::subtract(Vect v){
	return Vect (x-v.getX() , y-v.getY() , z-v.getZ());
}


Vect Vect::multiply (double scalar){
	return Vect (x*scalar , y*scalar , z*scalar);
}

#endif /* Vect_h */

