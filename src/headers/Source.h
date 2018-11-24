//
//  Source.hpp
//  
//
//  Created by Ojashvi Rautela on 11/24/18.
//

#ifndef Source_hpp
#define Source_hpp
#include "Vect.h"
#include "Color.h"

class Source{
	
public:
	
	Source();
	
	virtual Vect getLightPosition();
	virtual Color getColor();
	
};

#endif /* Source_hpp */
