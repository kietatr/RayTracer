//
//  Object.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#include "Object.h"


Object::Object(){
}

Color Object::getColor () {
	return Color (0.0, 0.0, 0.0, 0.0);
}

double Object::findIntersection(Ray ray){
	return 0;
}

Vect Object::getNormalAt (Vect point){
	return Vect (0, 0, 0);
}

