//
//  Plane.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Plane_h
#define Plane_h

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Plane : public Object {
	Vect normal; //perpendicular to the surface
	double distance; // b/w the plane center to the scene center
	Color color;
	
	
public:
	
	// declarations
	Plane();
	
	Plane (Vect, double, Color);
	
	//method functions
	double getPlaneDistance () {return distance;}
	Color getPlaneColor () {return color;}
	
	//ray-plane intersection
	//normal at any point on the plane = normal of the entire plane
	Vect getPlaneNormal () {return normal;}
	
	// ray intersecting with the plane
	double findIntersection(Ray);
};

Plane::Plane () {
	normal = Vect(1,0,0); // default : x direction
	distance = 0.0;
	color = Color(0.5,0.5,0.5,0);
}

Plane::Plane (Vect nor, double dis, Color col) {
	normal = nor;
	distance = dis;
	color = col;
}


//returns distance from ray origin to the intersection point
double Plane::findIntersection(Ray ray){
	//ray being intersected already defined during prespective routine
	Vect ray_dir = ray.getRayDirection();
	
	double dp = ray_dir.dot(normal);
	
	if (dp == 0){
		//ray perp to the normal = parallel to the plane
		return -1;
	}
	
	else {
		
		//opposition direction to that of ray
		
		//
		Vect v = ray.getRayOrigin().add(normal.multiply(distance).negative());
		double val = normal.dot(v);
		
		return (-1*val/dp);
		
	}
	
}
#endif /* Vect_h */

