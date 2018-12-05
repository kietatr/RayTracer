//
//  main.cpp
//  authors: Ojashvi Rautela and Kiet Tran 
//  date: 11/22/18
// 

#include <App.h>

#include <conio.h> // getch()

int main (int argc, char *argv[]){
    // anti-aliasing depth
	// aadepth = 1 -> NO anti-aliasing
	// aadepth = 4 -> send 4 new rays at each pixel
	int aadepth = 1;
	cout << "\nEnter an integer for anti-aliasing depth (1 = no anti-aliasing): ";
	cin >> aadepth;

	cout << "Rendering... " <<endl;

    clock_t t1, t2;
    t1 = clock();
	
	//image width and height
	int width = 640;
	int height = 480;

	double aathreshold = 0.1;

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
	Color plane_gray (0.82, 0.871, 0.886, 0.5);
	Color plane_black (0.5, 0.5, 0.5, 0.5);
	Color black (0.0, 0.0, 0.0, 0);

	Color sphere_purple (105.0 / 255.0, 48.0 / 255.0, 109.0 / 255.0, 0.3);
	Color sphere_lightPurple (165.0 / 255.0, 102.0 / 255.0, 139.0 / 255.0, 0.3);
	Color plane_purple (14.0 / 255.0, 16.0 / 255.0, 61.0 / 255.0, 0.5);
	
	// Light source
	Light scene_light (Vect(-7, 10, -10), white_light);
	
	// Stack of light sources
	vector<Source*> light_sources;
	light_sources.push_back(dynamic_cast<Source*> (&scene_light));
	
	// Scence objects
	Sphere scene_sphere (Vect(0, 0, 0), 1, sphere_orange);
	Sphere scene_sphere_2 (Vect(1.75, -0.5, 0), 0.5, sphere_purple);
	Plane scene_plane (Y, -1, plane_purple);
	
	// Stack objects
	vector<Object*> scene_objects;
	scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere));
	scene_objects.push_back(dynamic_cast<Object*> (&scene_sphere_2));
	scene_objects.push_back(dynamic_cast<Object*> (&scene_plane));
	
	// Create the image
	double xval, yval;
	double tempRed, tempGreen, tempBlue;
	int current;
	
	// Return color of the pixel
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			current = y*width + x;

			double tempRed[aadepth*aadepth], tempGreen[aadepth*aadepth], tempBlue[aadepth*aadepth]; // start with a blank pixel
			int aaIndex; // anti-aliasing index
			double aa_ratio;

			for (int aax = 0; aax < aadepth; aax++) {
				for (int aay = 0; aay < aadepth; aay++) {

					aaIndex = aay*aadepth + aax;

					if (aadepth == 1) {
						aa_ratio = 0.5; // aadepth = 1 -> NO anti-aliasing
					}
					else if (aadepth > 1) {
						aa_ratio = (double)aax / ((double)aadepth - 1); // aadepth > 1 -> ANTI-ALIASING
					}

					// Create rays from camera to pixel
					if (width  > height) {
						// image is wider
						xval = ((x + aa_ratio)/width)*aspect_ratio - (((width - height )/(double)height/2));
						yval = ((height - y) + aa_ratio)/height;
					}
					else if (height > width) {
						// image is taller
						xval = (x + aa_ratio)/width;
						yval = (((height - y) + aa_ratio)/height)/aspect_ratio - (((height - width )/(double)width/2));
					}
					else {
						// image is a square
						xval = (x + aa_ratio)/width;
						yval = ((height - y) + aa_ratio)/height;
					}
					
					// Rays
					Vect cam_ray_origin = scene_cam.getCameraPosition();
					Vect cam_ray_direction = cam_dir.add(cam_right.multiply(xval - 0.5).add(cam_down.multiply(yval - 0.5))).normalize();
					
					Ray cam_ray (cam_ray_origin, cam_ray_direction);
					
					// Intersections with each object
					vector<double> intersections;
					
					for (int i = 0; i < scene_objects.size(); i++) {
						intersections.push_back(scene_objects.at(i)->findIntersection(cam_ray));
					}
					
					int closest_object = closestObject(intersections);
				
					if (closest_object == -1) {
						// Background = black
						tempRed[aaIndex] = 0;
						tempGreen[aaIndex] = 0;
						tempBlue[aaIndex] = 0;
					}
					
					else {
						if (intersections.at(closest_object) > accuracy) {							
							Vect inter_position = cam_ray_origin.add(cam_ray_direction.multiply(intersections.at(closest_object)));
							Vect inter_ray_direction = cam_ray_direction;
							
							Color inter_color = getColorAt(inter_position, inter_ray_direction, scene_objects, closest_object, light_sources, accuracy, ambientlight);
							
							tempRed[aaIndex] = inter_color.getR();
							tempGreen[aaIndex] = inter_color.getG();
							tempBlue[aaIndex] = inter_color.getB();
						}
					}

				}
			}

			// Average the pixels' colors
			double totalRed = 0, totalGreen = 0, totalBlue = 0;

			for (int i = 0; i < aadepth * aadepth; i++) {
				totalRed += tempRed[i];
				totalGreen += tempGreen[i];
				totalBlue += tempBlue[i];
			}

			double avgRed = totalRed / (aadepth * aadepth);
			double avgGreen = totalGreen / (aadepth * aadepth);
			double avgBlue = totalBlue / (aadepth * aadepth);

			pixels[current].r = avgRed;
			pixels[current].g = avgGreen;
			pixels[current].b = avgBlue;
		}
	}

	string imagePath = "../images/scene.jpeg";

	saveImage(imagePath.c_str(), width, height, dpi, pixels);
	
	cout << "Rendering done! " <<endl;
	cout << "Image saved to " << imagePath << endl;

	delete pixels, tempRed, tempGreen, tempBlue;

	t2 = clock();
	float diff = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
	cout << "Rendering time: " << diff << " seconds" << endl;

	cout << "Press any key to close...";
	getch();

    return 0;
}
