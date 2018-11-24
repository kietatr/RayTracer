//
//  Color.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Color_h
#define Color_h

class Color{
	double red, green, blue, alpha;
	
public:
	
	// declarations
	Color();
	
	Color (double, double , double, double);
	
	//method functions
	
	double getR () {return red; }
	double getG () {return green; }
	double getB () {return blue; }
	double getAplha () {return alpha; }
	
	
	void setR (double r) {red = r; }
	void setG  (double g) {green = g; }
	void setB (double b) {blue = b; }
	void setAlpha (double a) {alpha = a; }
	

};

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


#endif /* Color_h */

