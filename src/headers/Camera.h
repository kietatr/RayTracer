#ifndef _Camera_H
#define _Camera_H

#include "Vect.h"

class Camera {
	Vect campos, camdir, camright, camdown;
	
	public:
	
	Camera ();
	
	Camera (Vect, Vect, Vect, Vect);
	
	// method functions
	Vect getCameraPosition ();// { return campos; }
	Vect getCameraDirection ();// { return camdir; }
	Vect getCameraRight ();// { return camright; }
	Vect getCameraDown ();// { return camdown; }
	
};

#endif
