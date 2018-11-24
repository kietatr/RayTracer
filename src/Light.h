//
//  Light.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Light_h
#define Light_h

#include "Vect.h"
#include "Color.h"

class Light{
	Vect position;
	Color color;
	
public:
	
	// declarations
	Light();
	
	Light (Vect, Color);
	
	//method functions
	
	Vect getLigthPosition () {return position;}
	Color getLightColor () {return color;}
	
};

Light::Light () {
	position = Vect(0,0,0);
	color = Color(1,1,1,0);
}

Light::Light (Vect p, Color c) {
	position = p;
	color = c;
}


#endif /* Vect_h */

