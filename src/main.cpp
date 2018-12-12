//
//  main.cpp
//  authors: Ojashvi Rautela and Kiet Tran 
//  date: 11/22/18
// 

#include <App.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <conio.h> // getch()
#endif

vector<Object*> scene_objects;

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
	double ambientlight = 0.15;
	double accuracy = 1e-8; //to ensure intersection is outside object
	
	//image properties
	int dpi = 72;
	int num_pix = width*height; // no. of pixels in the image
	RGB *pixels = new RGB[num_pix];
	
	// three directions
	Vect X (1,0,0);
	Vect Y (0,1,0);
	Vect Z (0,0,1);
	
	// Scene Camera
	Vect cam_pos (0, 2, 7);  // camera position
	Vect look_at (0, 1, 0); //point our camera looks at

	Vect cam_dir = look_at.subtract(cam_pos).normalize();
	Vect cam_right = cam_dir.cross(Y).normalize();
	Vect cam_down = cam_dir.cross(cam_right).normalize();
	
	Camera scene_cam (cam_pos, cam_dir, cam_right, cam_down);

	// Scene Color
	Color white_light (0.8, 0.8, 0.8, 0, 0);
	Color yellow_light (0.7, 0.7, 0.0, 0, 0);
	Color red_reflective (1, 0, 0, 2.0, 1.2);
	Color green_reflective (0, 1, 0, 2.0, 1.0);
	Color blue_reflective (0, 0, 1, 2.0, 0.7);
	Color yellow_reflective (1, 1, 0, 2.0, 0.5);
	Color cyan_reflective (0, 1, 1, 2.0, 1.0);
	Color magenta_reflective (1, 0, 1, 2.0, 0.7);
	Color plane_purple (0, 0, 0.5, 1.777, 0.5);
	
	// Light sources
	vector<Source*> light_sources;
	Light scene_light (Vect(-7, 10, 10), white_light);
	light_sources.push_back(dynamic_cast<Source*> (&scene_light));
	// Light scene_light2 (Vect(5, 6, -6), yellow_light);
	// light_sources.push_back(dynamic_cast<Source*> (&scene_light2));
	
	// Scence objects
	Plane scene_floor (Y, -1, plane_purple);
	scene_objects.push_back(dynamic_cast<Object*> (&scene_floor));
	Sphere sphere1 (Vect(0, 1, 0), 2, red_reflective);
	scene_objects.push_back(dynamic_cast<Object*> (&sphere1));
	Sphere sphere2 (Vect(3, 3, 2), 1, green_reflective);
	scene_objects.push_back(dynamic_cast<Object*> (&sphere2));
	Sphere sphere3 (Vect(-1, 0, 3), 0.5, blue_reflective);
	scene_objects.push_back(dynamic_cast<Object*> (&sphere3));
	Sphere sphere4 (Vect(-3, -0.75, 1.5), 0.25, yellow_reflective);
	scene_objects.push_back(dynamic_cast<Object*> (&sphere4));
	Sphere sphere5 (Vect(-6, 0.5, -5), 1.5, cyan_reflective);
	scene_objects.push_back(dynamic_cast<Object*> (&sphere5));

	vector<Object*> cubeTriangles = drawCube(Vect(7, 0, -10), 2, 2, 2, magenta_reflective);
	scene_objects.insert(end(scene_objects), begin(cubeTriangles), end(cubeTriangles));

	// // Draw the coordinate system for debugging
	// Triangle x_tri (Vect(0, 0, 1), Vect(2, 0, 0), Vect(0, 0, -1), Color(1,0,0,0,0));
	// Triangle y_tri (Vect(1, 0, 0), Vect(0, 2, 0), Vect(-1, 0, 0), Color(0,1,0,0,0));
	// Triangle z_tri (Vect(0, 1, 0), Vect(0, 0, 2), Vect(0, -1, 0), Color(0,0,1,0,0));
	// scene_objects.push_back(dynamic_cast<Object*> (&x_tri));
	// scene_objects.push_back(dynamic_cast<Object*> (&y_tri));
	// scene_objects.push_back(dynamic_cast<Object*> (&z_tri));
	
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
							
							Color inter_color = getColorAt(inter_position, cam_ray_direction, scene_objects, closest_object, light_sources, accuracy, ambientlight, 0);
							
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

	string imagePath = "../images/scene_aadepth_" + to_string(aadepth) + ".jpeg";

	saveImage(imagePath.c_str(), width, height, dpi, pixels);
	
	cout << "Rendering done! " <<endl;
	cout << "Rendered image saved to " << imagePath << endl;

	delete pixels, tempRed, tempGreen, tempBlue;

	t2 = clock();
	double diff = ((double) t2 - (double) t1) / CLOCKS_PER_SEC;
	cout << "Rendering time: " << diff << " seconds" << endl;

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		cout << "Press any key to close...";
		getch();
	#endif

	return 0;
}
