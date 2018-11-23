//
//  main.cpp
//  Created by Ojashvi Rautela on 11/22/18.


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// new classes created from scratch
#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"

//classes for objects on screen
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"



//struct for color
struct RGB{
	double r;
	double g;
	double b;
};

// to save the image as a file
// RGB values passed between 0 to 1
void saveimage (const char *filename, int w, int h, int dpi, RGB *data) {
	FILE *f;
	int k = w*h;
	int s = 4*k;
	int filesize = 54 + s;
	
	double factor = 39.375;
	int m = static_cast<int>(factor);
	
	int ppm = dpi*m;
	
	unsigned char imagefileheader[14] = {'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char imageinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
	
	imagefileheader[ 2] = (unsigned char)(filesize);
	imagefileheader[ 3] = (unsigned char)(filesize>>8);
	imagefileheader[ 4] = (unsigned char)(filesize>>16);
	imagefileheader[ 5] = (unsigned char)(filesize>>24);
	
	imageinfoheader[ 4] = (unsigned char)(w);
	imageinfoheader[ 5] = (unsigned char)(w>>8);
	imageinfoheader[ 6] = (unsigned char)(w>>16);
	imageinfoheader[ 7] = (unsigned char)(w>>24);
	
	imageinfoheader[ 8] = (unsigned char)(h);
	imageinfoheader[ 9] = (unsigned char)(h>>8);
	imageinfoheader[10] = (unsigned char)(h>>16);
	imageinfoheader[11] = (unsigned char)(h>>24);
	
	imageinfoheader[21] = (unsigned char)(s);
	imageinfoheader[22] = (unsigned char)(s>>8);
	imageinfoheader[23] = (unsigned char)(s>>16);
	imageinfoheader[24] = (unsigned char)(s>>24);
	
	imageinfoheader[25] = (unsigned char)(ppm);
	imageinfoheader[26] = (unsigned char)(ppm>>8);
	imageinfoheader[27] = (unsigned char)(ppm>>16);
	imageinfoheader[28] = (unsigned char)(ppm>>24);
	
	imageinfoheader[29] = (unsigned char)(ppm);
	imageinfoheader[30] = (unsigned char)(ppm>>8);
	imageinfoheader[31] = (unsigned char)(ppm>>16);
	imageinfoheader[32] = (unsigned char)(ppm>>24);
	
	f = fopen(filename, "wb");
	
	fwrite(imagefileheader, 1, 14, f);
	fwrite(imageinfoheader, 1, 40, f);
	
	//color
	for(int i = 0; i < k ; i++){
		double r = (data[i].r)*255;
		double g = (data[i].g)*255;
		double b = (data[i].b)*255;
		
		unsigned char color[3] = {(int)floor(b), (int)floor(g), (int)floor(r)};
		
		fwrite(color, 1, 3, f);
	}
	
	fclose(f);
}

int current;

int main (int argc, char *argv[]){
    
    cout <<"rendering... " <<endl;
	
	//image width and height
	int width = 640;
	int height = 480;
	
	//image properties
	int dpi = 72;
	int num_pix = width*height; // no. of pixels in the image
	RGB *pixels = new RGB[num_pix];
	
	// three directions
	Vect X (1,0,0);
	Vect Y (0,1,0);
	Vect Z (0,0,1);
	
	//////////////// recheck /////////
	
	
	// Scene Camera
	Vect cam_pos (3, 1.5, -4);  // camera position
	Vect look_at (0,0,0); //point our camera looks at
	
	Vect cam_dir = look_at.subtract(cam_pos).normalize(); //direction from camera to look_at
	Vect cam_right = Y.cross(cam_dir).normalize();
	Vect cam_down = cam_right.cross(cam_dir);
	
	Camera scene_cam (cam_pos, cam_dir, cam_right, cam_down);

	// Scene Color
	Color white_light (1.0, 1.0, 1.0, 0);
	Color pretty_green (0.5, 1.0, 0.5, 0.3);
	Color gray (0.5, 0.5, 0.5, 0);
	Color black (0.0, 0.0, 0.0, 0);
	
	
	
	//Light source and color 
	Vect light_position (-7, 10, -10);
	Light scene_light (light_position, white_light);
	
	
	// scence objects
	Sphere scene_sphere (Vect(0,0,0), 1, pretty_green);
	Plane scene_plane (Y, -1, gray);
	
	
	
	for (int x =0; x < width; x++){
		for (int y =0; y < height; y++){
			// return color of the pixel
			current = y*width + x;
			
			if((x>200 && x<440) && (y>200 && y<280) ){
				pixels[current].r  = 1;
				pixels[current].g  = 0.8;
				pixels[current].b  = 0;
			}
			
			else{
				pixels[current].r  = 0;
				pixels[current].g  = 0;
				pixels[current].b  = 0;
			}
		}
	}
	
	saveimage("scene.jpg", width, height, dpi, pixels);
	
    return 0;
}


