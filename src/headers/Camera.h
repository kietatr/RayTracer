//
//  Camera.h
//  
//
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Camera_h
#define Camera_h

#include "Vect.h"

class Camera{
	//to define the coordinate frame of the scene
	//later used to compute presepective
	
	Vect cam_pos, cam_dir, cam_right, cam_down;
	
public:
	
	// declarations
	Camera();
	
	Camera (Vect, Vect, Vect, Vect);
	
	//method functions
	
	Vect getCameraPosition ();
	Vect getCameraDirection ();
	Vect getCameraRight ();
	Vect getCameraDown ();
	
};
#endif /* Camera_h */
