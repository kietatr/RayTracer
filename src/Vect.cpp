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

// 
// https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
// 
// r: reflected vector
// d: incoming vector
// n: normal of the surface
// 
// r = d − 2(d⋅n)n
// 
Vect Vect::reflect (Vect normal) {
	Vect incoming (x, y, z);
	Vect normalScaled = (normal.multiply(incoming.dot(normal))).multiply(2);
	return incoming.subtract(normalScaled);
}

// 
// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
// 
// Given:
// - the current vector as the incident vector: I 
// - surface normal: N 
// - ratio of indices of refraction: eta. 
// Return: the refraction vector, R.
// 
Vect Vect::refract (Vect N, double ior) {
	Vect I (x, y, z);
	Vect R (0,0,0);

	double cosi = I.dot(N);
	if (cosi < -1) {cosi = -1;}
	if (cosi > 1) {cosi = 1;}

	double etai = 1, etat = ior; 
	Vect n = N; 
	if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n = N.negative(); } 
	double eta = etai / etat; 
	double k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0) {
		return R;
	}
	else {
		return I.multiply(eta).add(n.multiply(eta * cosi - sqrtf(k)));
	}
}
