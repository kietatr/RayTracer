#include "Color.h"

Color::Color () {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
	alpha = 0;
}

Color::Color (double r, double g, double b, double a) {
	red = r;
	green = g;
	blue = b;
	alpha = a;
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

double Color::getAplha () {
	return alpha;
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

void Color::setAlpha (double a) {
	alpha = a;
}
