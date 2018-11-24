//
//  Sphere.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Sphere_h
#define Sphere_h

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Sphere : public Object {
	Vect center;
	double radius;
	Color color;
	
public:
	
	// declarations
	Sphere();
	
	Sphere (Vect, double, Color);
	
	//method functions
	
	Vect getSphereCenter () {return center;}
	double getSphereRadius () {return radius;}
	Color getColor () {return color;}
	
	Vect getNormalAt(Vect);
	double findIntersection(Ray); ////why virtual
};

Sphere::Sphere () {
	center = Vect(0,0,0);
	radius = 1.0;
	color = Color(0.5,0.5,0.5,0);
}

Sphere::Sphere (Vect cen, double rad, Color col) {
	center = cen;
	radius = rad;
	color = col;
}

Vect Sphere::getNormalAt(Vect point){
	//normal always points away from the sphere
	Vect normal = point.subtract(center).normalize();; //pointing away from center
	return normal;
}

double Sphere::findIntersection(Ray ray){
	
	//http://paulbourke.net/geometry/circlesphere/
	//sphere : x^2 + y^2 + z^2  = r^2
	//point on line p1, p2=  p1 + m (p2-p1)
	//Substituting the equation of the line into the sphere gives a quadratic equation
	//au^2 + bu + c = 0 (where u gives the point of intersection)
	
	Vect ray_origin = ray.getRayOrigin();
	Vect ray_dir = ray.getRayDirection();
	Vect ray_length = ray_origin.subtract(center); //from sphere center
	
	//a from quad. eq.
	double a = 1; //normalized length of the ray line
	
	//b from quad. eq.
	double b = (ray_length.dot(ray_dir)) * 2;
	
	//c from quad. eq.
	double c = pow(ray_length.getX(),2) + pow(ray_length.getY(),2) + pow(ray_length.getZ(),2) - radius*radius;
	
	//solving for quad eq.
	double discriminant = b*b - 4*a*c;
	
	if (discriminant >0) {
		//ray intersects the sphere at 2 points (goes through the sphere)
		double p1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;  //to deal with accuracy
		if (p1 > 0) {
			return p1;
		}
		else { //second smallest positive root
			double p2 = ((sqrt(discriminant)- b)/2) - 0.000001;
			return p2;
		}
	}
	
	else {
		//does not intersect or is a tangent
		return -1;
	}
}



#endif /* Vect_h */

