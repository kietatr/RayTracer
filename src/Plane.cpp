//
//  Plane.cpp
//  Created by Ojashvi Rautela on 11/22/18.
//
#include "Plane.h"

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

double Plane::getPlaneDistance () {
	return distance;
}

Vect Plane::getNormalAt (Vect point){
	return normal;
}

Color Plane::getColor () {
	return color;
}

Vect Plane::getPlaneNormal (){
	return normal;
}

double Plane::findIntersection(Ray ray){
	//returns distance from ray origin to the intersection point
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

