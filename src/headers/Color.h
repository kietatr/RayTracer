//
//  Color.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Color_h
#define Color_h

class Color{
	double red, green, blue;
	double reflectivity, transparency;
	
public:
	
	Color ();
	Color (double, double, double, double, double);
	
	
	//method functions
	double getR ();
	double getG ();
	double getB ();
	double getReflectivity();
	double getTransparency();
	
	void setR (double);
	void setG (double);
	void setB (double);
	
	double brightness ();
	Color colorScale (double);
	
	Color colorAdd (Color);
	Color colorMultiply (Color);
	Color colorAverage (Color);
	Color clip();
	
};

#endif /* Color_h */

