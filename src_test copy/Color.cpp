#include "Color.h"

Color::Color () {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
	special = 0;
}

Color::Color (double r, double g, double b, double a) {
	red = r;
	green = g;
	blue = b;
	special = a;
}

double Color::getR () {
	return red;
}

double Color::getG () {
	return green;
}

double Color::getB () {
	return blue;
}

double Color::getSpecial () {
	return special;
}

void Color::setR (double r) {
	red = r;
}

void Color::setG  (double g) {
	green = g;
}

void Color::setB (double b) {
	blue = b;
}

void Color::setSpecial (double a) {
	special = a;
}

double Color::brightness(){
	return(red + green + blue)/3;
}

Color Color::colorScale (double scale) {
	return Color (red*scale, green*scale, blue*scale, special);
}

Color Color::colorAdd (Color color){
	return Color (red + color.getR(), green + color.getG(), blue+ color.getB(), special);
}

Color Color::colorMultiply (Color color){
	return Color (red*color.getR(), green*color.getG(), blue*color.getB(), special);
}

Color Color::colorAverage (Color color){
	return Color ((red + color.getR())/2, (green + color.getG())/2, (blue+ color.getB())/2, special);
}

Color Color::clip(){
	double allLight = red + green + blue;
	double extraLight = allLight - 3;
	
	if (extraLight > 0){
		red = red + extraLight * (red/allLight);
		green = green + extraLight * (green/allLight);
		blue = blue + extraLight * (blue/allLight);
	}
	
	if (red > 1) {red = 1;}
	if (green > 1) {green = 1;}
	if (blue > 1) {blue = 1;}
	if (red < 0) {red = 0;}
	if (green < 0) {green = 0;}
	if (blue < 0) {blue = 0;}
	
	return Color (red, green, blue, special);
}

