//
//  Object.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Object_h
#define Object_h

#include "Ray.h"
#include "Vect.h"
#include "Color.h"

class Object{
	
	public:
	
	Object();
	
	virtual Color getColor ();
	
	//intersect b/w a ray and the object
	virtual double findIntersection (Ray);
	
	virtual Vect getNormalAt(Vect);
};


#endif /* Object_h */

