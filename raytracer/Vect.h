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
	
	double getVectX() {return x; }
	double getVectY() {return y; }
	double getVectZ() {return z; }
	
	
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


#endif /* Vect_h */

