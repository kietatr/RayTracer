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
	
	//method function
	virtual Color getColor () {return Color (0.0, 0.0, 0.0, 0.0); }
	
	//intersect b/w a ray and the object
	virtual double findIntersection(Ray ray){
		return 0;
	}
	
};

Object::Object () {}


#endif /* Vect_h */

