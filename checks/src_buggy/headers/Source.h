//
//  Source.h
//  
//
//  Created by Ojashvi Rautela on 11/24/18.
//

#ifndef Source_h
#define Source_h

#include "Vect.h"
#include "Color.h"

class Source{
	
public:
	
	Source();
	
	virtual Vect getLightPosition();
	virtual Color getLightColor();
	
};

#endif /* Source_h */
