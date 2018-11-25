#ifndef _VECT_H
#define _VECT_H

#include "math.h"

class Vect {
	double x, y, z;
	
	public:
	
	Vect ();
	
	Vect (double, double, double);
	
	// method functions
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	
	double magnitude () {
		return sqrt((x*x) + (y*y) + (z*z));
	}
	
	Vect normalize () {
		double magnitude = sqrt((x*x) + (y*y) + (z*z));
		return Vect (x/magnitude, y/magnitude, z/magnitude);
	}
	
	Vect negative () {
		return Vect (-x, -y, -z);
	}
	
	double dot(Vect v) {
		return x*v.getX() + y*v.getY() + z*v.getZ();
	}
	
	Vect cross(Vect v) {
		return Vect (y*v.getZ() - z*v.getY(), z*v.getX() - x*v.getZ(), x*v.getY() - y*v.getX());
	}
	
	Vect add (Vect v) {
		return Vect (x + v.getX(), y + v.getY(), z + v.getZ());
	}

	Vect subtract (Vect v) {
		return Vect (x - v.getX(), y - v.getY(), z - v.getZ());
	}

	Vect multiply (double scalar) {
		return Vect (x*scalar, y*scalar, z*scalar);
	}
};

Vect::Vect () {
	x = 0;
	y = 0;
	z = 0;
}

Vect::Vect (double i, double j, double k) {
	x = i;
	y = j;
	z = k;
}

#endif
