//
//  Triangle.cpp
//  Created by Kiet Tran on 12/7/18.
//
#include "Triangle.h"

Triangle::Triangle () {
	A = Vect(1,0,0);
	B = Vect(0,1,0);
	C = Vect(0,0,1);
	color = Color(0.5, 0.5, 0.5, 0, 0);
	normal = getTriangleNormal();
	distance = getTriangleDistance();
}

Triangle::Triangle (Vect a, Vect b, Vect c, Color col) {
	A = a;
	B = b;
	C = c;
	color = col;
	normal = getTriangleNormal();
	distance = getTriangleDistance();
}

double Triangle::getTriangleDistance () {
	// normal = getTriangleNormal();
	return normal.dot(A);
}

Vect Triangle::getNormalAt (Vect point){
	return getTriangleNormal();
}

Color Triangle::getColor () {
	return color;
}

Vect Triangle::getTriangleNormal (){
	Vect AC = C.subtract(A);
	Vect AB = B.subtract(A);
	return AC.cross(AB).normalize();
}

double Triangle::findIntersection(Ray ray){
	//returns distance from ray origin to the intersection point
	// Equations https://samsymons.com/blog/math-notes-ray-Triangle-intersection/
	// Triangle = (p−p0).n=0   (know that p0 is in the Triangle; p0 = normal*distace from origin)
	// point on a ray = ray_origin+(ray_dir ∗ t)
	// Substituting the equation of the line into the Triangle gives a quadratic equation
	//((ray_origin + ray_dir ∗ t)−p0).n=0 (solving for t will give the intersection)
	// t = -(ray_origin−p0).n / ray_dir.n
	
	Vect ray_dir = ray.getRayDirection();
	Vect ray_origin = ray.getRayOrigin();
	
	double a = ray_dir.dot(normal);
	
	if (a == 0){
		//ray perp to the normal = parallel to the Triangle
		return -1;
	}
	else {
		// 1. Find intersection of ray with plane first
		// 2. Then check if the intersection point lies inside the triangle

		// 1. Ray-Plane intersection
		//ray_origin - p0
		//ray_origin - point on Triangle (normal gives the direct, distance gives the magn)
		Vect v = ray.getRayOrigin().subtract(normal.multiply(distance));
		
		//v in direction of normal
		double b = normal.dot(v);

		//t
		double distToPlane = -b/a;
		
		// 2. Check if intersection point is inside triangle

		// Ray-Plane intersection point
		Vect I = ray_origin.add(ray_dir.multiply(distToPlane));
		
		// I is inside triangle if
		// [AB x IB] * n >= 0
		// [BC x IC] * n >= 0
		// [CA x IA] * n >= 0
		
		Vect AB = A.subtract(B); Vect IB = I.subtract(B);
		double test1 = (AB.cross(IB)).dot(normal);

		Vect BC = B.subtract(C); Vect IC = I.subtract(C);
		double test2 = (BC.cross(IC)).dot(normal);
		
		Vect CA = C.subtract(A); Vect IA = I.subtract(A);
		double test3 = (CA.cross(IA)).dot(normal);
		
		if (test1 >= 0 && test2 >= 0 && test3 >= 0) {
			// I is inside triangle 
			return distToPlane;
		}
		else {
			// I is outside triangle 
			return -1;
		}
	}
}

