//
//  Vect.cpp
//  Created by Ojashvi Rautela on 11/22/18.
//

#include "Vect.h"

Vect::Vect () {
	x = 0;
	y = 0;
	z = 0;
}

Vect::Vect (double a, double b, double c) {
	x = a;
	y = b;
	z = c;
}

double Vect::getX() {
	return x;
}

double Vect::getY() {
	return y;
}

double Vect::getZ() {
	return z;
}

double Vect::magnitude (){
	return sqrt((x*x) + (y*y) + (z*z));
}

Vect Vect::normalize (){
	return Vect (x/magnitude(), y/magnitude(), z/magnitude());
}

double  Vect::dot(Vect v){
	return (x*v.getX() + y*v.getY() + z*v.getZ());
}

Vect Vect::cross(Vect v){
	return Vect (y*v.getZ() - z*v.getY(),
				 z*v.getX() - x*v.getZ(),
				 x*v.getY() - y*v.getX());
}

Vect Vect::negative (){
	return Vect (-x, -y, -z);
}

Vect  Vect::add(Vect v){
	return Vect (x+v.getX() , y+v.getY() , z+v.getZ());
}

Vect  Vect::subtract(Vect v){
	return Vect (x-v.getX() , y-v.getY() , z-v.getZ());
}


Vect Vect::multiply (double scalar){
	return Vect (x*scalar , y*scalar , z*scalar);
}


