#ifndef _Light_H
#define _Light_H

#include "Source.h"
#include "Vect.h"
#include "Color.h"

class Light : public Source {
	Vect position;
	Color color;
	
	public:
	
	Light ();
	
	Light (Vect, Color);
	
	// method functions
	virtual Vect getLightPosition ();// { return position; }
	virtual Color getLightColor ();// { return color; }
	
};



#endif
