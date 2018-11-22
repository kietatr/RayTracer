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
	
	Vect getCameraPosition () {return cam_pos;}
	Vect getCameraDirection () {return cam_dir;}
	Vect getCameraRight () {return cam_right;}
	Vect getCameraDown () {return cam_down;}
	
};
Camera::Camera () {
	cam_pos  = Vect(0,0,0);
	cam_dir  = Vect(0,0,1);  // straight out of the screen
	cam_right= Vect(0,0,0); // specified later
	cam_down = Vect(0,0,0);  // specified later
}

Camera::Camera (Vect pos, Vect dir, Vect right, Vect down) {
	cam_pos  = pos;
	cam_dir  = dir;
	cam_right= right;
	cam_down = down;
}

#endif /* Camera_h */
