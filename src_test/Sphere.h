#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Sphere : public Object {
	Vect center;
	double radius;
	Color color;
	
	public:
	
	Sphere ();
	
	Sphere (Vect, double, Color);
	
	// method functions
	Vect getSphereCenter () { return center; }
	double getSphereRadius () { return radius; }
	virtual Color getColor () { return color; }
	
	virtual Vect getNormalAt(Vect point) {
		// normal always points away from the center of a sphere
		Vect normal_Vect = point.add(center.negative()).normalize();
		return normal_Vect;
	}
	
	virtual double findIntersection(Ray ray) {
		Vect ray_origin = ray.getRayOrigin();
		double ray_origin_x = ray_origin.getX();
		double ray_origin_y = ray_origin.getY();
		double ray_origin_z = ray_origin.getZ();
		
		Vect ray_direction = ray.getRayDirection();
		double ray_direction_x = ray_direction.getX();
		double ray_direction_y = ray_direction.getY();
		double ray_direction_z = ray_direction.getZ();
		
		Vect sphere_center = center;
		double sphere_center_x = sphere_center.getX();
		double sphere_center_y = sphere_center.getY();
		double sphere_center_z = sphere_center.getZ();
		
		double a = 1; // normalized
		double b = (2*(ray_origin_x - sphere_center_x)*ray_direction_x) + (2*(ray_origin_y - sphere_center_y)*ray_direction_y) + (2*(ray_origin_z - sphere_center_z)*ray_direction_z);
		double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (radius*radius);
		
		double discriminant = b*b - 4*a*c;
		
		if (discriminant > 0) {
			/// the ray intersects the sphere
			
			// the first root
			double root_1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;
			
			if (root_1 > 0) {
				// the first root is the smallest positive root
				return root_1;
			}
			else {
				// the second root is the smallest positive root
				double root_2 = ((sqrt(discriminant) - b)/2) - 0.000001;
				return root_2;
			}
		}
		else {
			// the ray missed the sphere
			return -1;
		}
	}
	
};

Sphere::Sphere () {
	center = Vect(0,0,0);
	radius = 1.0;
	color = Color(0.5,0.5,0.5, 0);
}

Sphere::Sphere (Vect centerValue, double radiusValue, Color colorValue) {
	center = centerValue;
	radius = radiusValue;
	color = colorValue;
}

#endif
