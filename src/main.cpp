//
//  main.cpp
//  Created by Ojashvi Rautela on 11/22/18.
// 

#include <mainFunctions.h>

int main (int argc, char *argv[]){
    
    cout <<"rendering... " <<endl;
	
	//image width and height
	int width = 640;
	int height = 480;
	
	double aspect_ratio = (double)width / (double)height;
	double ambientlight = 0.2;
	double accuracy = 0.000001; //to ensure intersection is outside object
	
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
	Vect look_at (0, 0, 0); //point our camera looks at

	Vect cam_dir = look_at.subtract(cam_pos).normalize();
	Vect cam_right = Y.cross(cam_dir).normalize();
	Vect cam_down = cam_right.cross(cam_dir).normalize();
	
	Camera scene_cam (cam_pos, cam_dir, cam_right, cam_down);

	// Scene Color
	Color white_light (1.0, 1.0, 1.0, 0);
	Color sphere_blue (70.0 / 255.0, 159.0 / 255.0, 254.0 / 255.0, 0.3);
	Color sphere_orange (254.0 / 255.0, 206.0 / 255.0, 70.0 / 255.0, 0.3);
	Color plane_gray (0.82, 0.871, 0.886, 0);
	Color black (0.0, 0.0, 0.0, 0);
	
	// Light source
	Light scene_light (Vect(-7, 10, -10), white_light);
	
	// Stack of light sources
	vector<Source*> light_sources;
	light_sources.push_back(dynamic_cast<Source*> (&scene_light));
	
	// Scence objects
	Sphere scene_sphere (Vect(0, 0, 0), 1, sphere_blue);
	Sphere scene_sphere_2 (Vect(1.75, -0.25, 0), 0.5, sphere_orange);
	Plane scene_plane (Y, -1, plane_gray);
	
	// Stack objects
	vector<Object*> scene_objects;
	scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere));
	scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere_2));
	scene_objects.push_back(dynamic_cast<Object*> (&scene_plane));
	
	// Create the image
	double xval, yval;
	int current;
	
	for (int x =0; x < width; x++){
		for (int y =0; y < height; y++){
			// return color of the pixel
			current = y*width + x;
			
			//start with no anti-aliasing
			//to create rays
			if (width  > height) {
				// image is wider
				xval = ((x + 0.5)/width)*aspect_ratio - (((width - height )/(double)height/2));
				
				yval = ((height - y) + 0.5)/height;
			}
			
			else if (height > width){
				// image is taller
				xval = (x + 0.5)/width;
				
				yval = (((height - y) + 0.5)/height)/aspect_ratio - (((height - width )/(double)width/2));
			}
			
			else {
				// image is a square
				xval = (x + 0.5)/width;
				yval = ((height - y) + 0.5)/height;
				
			}
			
			//rays
			Vect cam_ray_origin = scene_cam.getCameraPosition();
			Vect cam_ray_direction = cam_dir.add(cam_right.multiply(xval - 0.5).add(cam_down.multiply(yval - 0.5))).normalize();
			
			Ray cam_ray (cam_ray_origin, cam_ray_direction);
			
			//intersections with each object
			vector<double> intersections;
			
			for (int i = 0; i < scene_objects.size(); i++){
				intersections.push_back(scene_objects.at(i)->findIntersection(cam_ray));
			}
			
			int closest_object = closestObject(intersections);
		
			if(closest_object == -1){
				//background = black
				pixels[current].r  = 0;
				pixels[current].g  = 0;
				pixels[current].b  = 0;
			}
			
			else{
				//index corresponds to a scene object
				
				if(intersections.at(closest_object) > accuracy){
					
					//determines the pos and dir vectors at point of intersection
					
					Vect inter_position = cam_ray_origin.add(cam_ray_direction.multiply(intersections.at(closest_object)));
					Vect inter_ray_direction = cam_ray_direction;
					
					Color inter_color = getColorAt(inter_position, inter_ray_direction, scene_objects, closest_object, light_sources, accuracy, ambientlight);
					
					pixels[current].r  = inter_color.getR();
					pixels[current].g  = inter_color.getG();
					pixels[current].b  = inter_color.getB();
				}
			}
		}
	}

	string imagePath = "../images/scene.jpeg";

	saveImage(imagePath.c_str(), width, height, dpi, pixels);
	
	cout << "Image saved to " << imagePath << endl;

    return 0;
}
