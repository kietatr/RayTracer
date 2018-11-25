//
//  Camera.h
//  
//
//  Created by Ojashvi Rautela on 11/22/18.
//

#include "Camera.h"

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

Vect Camera::getCameraPosition () {
	return cam_pos;
}

Vect Camera::getCameraDirection () {
	return cam_dir;
}

Vect Camera::getCameraRight () {
	return cam_right;
}

Vect Camera::getCameraDown () {
	return cam_down;
}
