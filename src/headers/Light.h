//
//  Light.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Light_h
#define Light_h

#include "Source.h"
#include "Vect.h"
#include "Color.h"

class Light : public Source {
	
	Vect position;
	Color color;
	
public:

	Light ();
	Light (Vect, Color);
	
	//method functions
	
	Vect getLigthPosition ();
	Color getLightColor ();
	
};

#endif /* Light_h */

