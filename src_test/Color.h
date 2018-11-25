#ifndef _COLOR_H
#define _COLOR_H

class Color {
	double red, green, blue, special;
	
	public:
	
	Color ();
	
	Color (double, double, double, double);
	
	// method functions
	double getR() { return red; }
	double getG() { return green; }
	double getB() { return blue; }
	double getSpecial() { return special; }
	
	void setR(double redValue) { red = redValue; }
	void setG(double greenValue) { green = greenValue; }
	void setB(double blueValue) { blue = blueValue; }
	void setSpecial(double specialValue) { special = specialValue; }
	
	double brightness() {
		return(red + green + blue)/3;
	}
	
	Color colorScale(double scalar) {
		return Color (red*scalar, green*scalar, blue*scalar, special);
	}
	
	Color colorAdd(Color color) {
		return Color (red + color.getR(), green + color.getG(), blue + color.getB(), special);
	}
	
	Color colorMultiply(Color color) {
		return Color (red * color.getR(), green*color.getG(), blue*color.getB(), special);
	}
	
	Color colorAverage(Color color) {
		return Color ((red + color.getR())/2, (green + color.getG())/2, (blue + color.getB())/2, special);
	}
	
	Color clip() {
		double alllight = red + green + blue;
		double excesslight = alllight - 3;
		if (excesslight > 0) {
			red = red + excesslight*(red/alllight);
			green = green + excesslight*(green/alllight);
			blue = blue + excesslight*(blue/alllight);
		}
		if (red > 1) {red = 1;}
		if (green > 1) {green = 1;}
		if (blue > 1) {blue = 1;}
		if (red < 0) {red = 0;}
		if (green < 0) {green = 0;}
		if (blue < 0) {blue = 0;}
		
		return Color (red, green, blue, special);
	}
};

Color::Color () {
	red = 0.5;
	green = 0.5;
	blue = 0.5;
}

Color::Color (double r, double g, double b, double s) {
	red = r;
	green = g;
	blue = b;
	special = s;
}

#endif
