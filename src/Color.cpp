#include "Color.h"

Color::Color () {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
	reflectivity = 0;
	transparency = 0;
}

Color::Color (double r, double g, double b, double reflect, double transparent) {
	red = r;
	green = g;
	blue = b;
	reflectivity = reflect;
	transparency = transparent;
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

double Color::getReflectivity() {
	return reflectivity;
}

double Color::getTransparency() {
	return transparency;
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

double Color::brightness(){
	return(red + green + blue)/3;
}

Color Color::colorScale (double scale) {
	return Color (red*scale, green*scale, blue*scale, reflectivity, transparency);
}

Color Color::colorAdd (Color color){
	return Color (red + color.getR(), green + color.getG(), blue+ color.getB(), reflectivity, transparency);
}

Color Color::colorMultiply (Color color){
	return Color (red*color.getR(), green*color.getG(), blue*color.getB(), reflectivity, transparency);
}

Color Color::colorAverage (Color color){
	return Color ((red + color.getR())/2, (green + color.getG())/2, (blue+ color.getB())/2, reflectivity, transparency);
}

Color Color::clip(){
	// double allLight = red + green + blue;
	// double extraLight = allLight - 3;
	
	// if (extraLight > 0){
	// 	red = red + extraLight * (red/allLight);
	// 	green = green + extraLight * (green/allLight);
	// 	blue = blue + extraLight * (blue/allLight);
	// }
	
	if (red > 1) {red = 1;}
	if (green > 1) {green = 1;}
	if (blue > 1) {blue = 1;}
	if (reflectivity > 1) {reflectivity = 1;}
	if (transparency > 1) {transparency = 1;}

	if (red < 0) {red = 0;}
	if (green < 0) {green = 0;}
	if (blue < 0) {blue = 0;}
	if (reflectivity < 0) {reflectivity = 0;}
	if (transparency < 0) {transparency = 0;}
	
	return Color (red, green, blue, reflectivity, transparency);
}

