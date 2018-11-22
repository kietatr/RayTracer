//
//  Ray.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Ray_h
#define Ray_h

#include "Vect.h"

class Ray{
	Vect origin, dir;
	
	public:
	
	// declarations
	Ray();
	
	Ray (Vect, Vect);
	
	//method functions
	
	Vect getRayOrigin () {return origin;}
	Vect getRayDirection () {return dir;}
	
};
Ray::Ray () {
	origin = Vect(0,0,0);
	dir = Vect(1,0,0);
}

Ray::Ray (Vect o, Vect d) {
	origin = o;
	dir = d;
}


#endif /* Vect_h */

