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
	Color getColor () {return color;}
	
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
	// Equations https://samsymons.com/blog/math-notes-ray-plane-intersection/
	// plane = (p−p0).n=0   (know that p0 is in the plane; p0 = normal*distace from origin)
	// point on a ray = ray_origin+(ray_dir ∗ t)
	// Substituting the equation of the line into the plane gives a quadratic equation
	//((ray_origin + ray_dir ∗ t)−p0).n=0 (solving for t will give the intersection)
	// t = -(ray_origin−p0).n / ray_dir.n
	
	Vect ray_dir = ray.getRayDirection();
	
	double a = ray_dir.dot(normal);
	
	if (a == 0){
		//ray perp to the normal = parallel to the plane
		return -1;
	}
	
	else {
		//ray_origin - p0
		//ray_origin - point on plane (normal gives the direct, distance gives the magn)
		Vect v = ray.getRayOrigin().subtract(normal.multiply(distance));
		
		//v in direction of normal
		double b = normal.dot(v);
		
		//t
		return (-b/a);
		
	}
	
}
#endif /* Vect_h */

