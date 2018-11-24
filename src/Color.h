//
//  Color.h
//  Created by Ojashvi Rautela on 11/22/18.
//

#ifndef Color_h
#define Color_h

class Color{
	double red, green, blue, alpha;
	
public:
	
	Color ();
	Color (double, double , double, double);
	
	
	//method functions
	double getR ();
	double getG ();
	double getB ();
	double getAplha ();
	
	
	void setR (double);
	void setG (double);
	void setB (double);
	void setAlpha (double);
};

#endif /* Color_h */

