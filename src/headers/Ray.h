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
	
	Vect getRayOrigin ();
	Vect getRayDirection ();
	
};

#endif /* Vect_h */

