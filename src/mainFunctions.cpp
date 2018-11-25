#include <mainFunctions.h>

// 
// Saves the rendered image into a file
// 
void saveImage (const char *filename, int w, int h, int dpi, RGB *data) {
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
		
		unsigned char color[3] = {(unsigned char)floor(b), (unsigned char)floor(g), (unsigned char)floor(r)};
		
		fwrite(color, 1, 3, f);
	}
	
	fclose(f);
}

// 
// Return the index of the object closest to the camera
// 
int closestObject(vector<double> intersections){
	int closestObjectIndex;
	int size = intersections.size();
	
	if(size == 0){
		// it no intersections
		return -1;
	}
	else if (size == 1){
		if(intersections.at(0) > 0){
		// greater than zero, then index of closest
			return 0;
		}
		else {
			// the only value is negative
			return -1;
		}
	}
	else {
		// find the max val
		double max = 0;
		for (int i = 0; i < size; i ++){
			if (max < intersections.at(i)){
				max = intersections.at(i);
			}
		}
		//then strat from max find the min pos
		if (max > 0){
			//we only want +ve intersections
			for(int i = 0; i < size; i ++){
				if(intersections.at(i) > 0 && intersections.at(i) <= max){
					max = intersections.at(i);
					closestObjectIndex = i;
				}
			}
			return closestObjectIndex;
		}
		else {
			//all intersections are -ve
			return -1;
		}
	}
}


// 
// Get the color that should be rendered at a ray-object intersection point
// (for implementing shadows, reflections, and other kinds of lighting models)
// 
Color getColorAt(Vect inter_position, Vect inter_ray_direction, vector<Object*> scene_objects, int closest_object, vector<Source*> light_sources, double accuracy, double ambientlight){
	//implemet shadows
	
	Color closest_object_color = scene_objects.at(closest_object)->getColor();
	Vect closest_object_normal = scene_objects.at(closest_object)->getNormalAt(inter_position);
	
	Color final_color = closest_object_color.colorScale(ambientlight);
	
	for (int i = 0; i < light_sources.size(); i++){
		
		//distance from intersection point to the light source
		Vect light_distance = light_sources.at(i)->getLightPosition().subtract(inter_position).normalize();
		
		///direction from intersection point to the light source = normalize(source - intersection)
		Vect light_dir = light_distance.normalize();;
		
		
		// for reflection
		float cos_angle = closest_object_normal.dot(light_dir);
		
		if (cos_angle > 0){
			//test for shadows
			
			bool shadow = false;
			float magnitude_light_distance = light_distance.magnitude();

			// The ray from intersection point to light source
			Ray shadow_ray (inter_position, light_dir);
			
			vector<double> second_intersections;
			
			for (int j = 0; j < scene_objects.size() && shadow == false; j++){
				second_intersections.push_back(scene_objects.at(j)->findIntersection(shadow_ray));
			}
			
			for(int s = 0; s < second_intersections.size(); s++){
				double second_inter = second_intersections.at(s);
				if (second_inter > accuracy){
					if (second_inter <= magnitude_light_distance){
						// second_inter = interaction of a ray going towards the source with an object
						// if less than the distance to the ligth source, then ray hits some object
						// therefore, the point of origin of ray should be in shadows
						// point of origin of this ray = first interaction surface of the incoming ray
						// See if the incoming ray hits the target, then send a ray backwards to source of incoming ray
						// if it hits/intersects with an object, then the target is in behind some object = shadow
						shadow = true;
						break;
					}
				}
				
			}
			
			if (shadow == false){
				//depends on intensity (multiplication)
				//linear algebra .... ???
				final_color = final_color.colorAdd(closest_object_color.colorMultiply(light_sources.at(i)->getLightColor()).colorScale(cos_angle));
				
				if (closest_object_color.getSpecial() > 0 && closest_object_color.getSpecial() <= 1) {
					//special = 0 to 1 : shininess
					double dot1 = closest_object_normal.dot(inter_ray_direction.negative());
					Vect scalar1 = closest_object_normal.multiply(dot1);
					Vect add1 = scalar1.add(inter_ray_direction);
					Vect scalar2 = add1.multiply(2);
					Vect add2 = scalar2.subtract(inter_ray_direction);
					
					Vect reflection_dir = add2.normalize();
					
					double specular = reflection_dir.dot(light_dir);
					
					if (specular > 0) {
						specular = pow(specular, 10);
						final_color = final_color.colorAdd(light_sources.at(i)->getLightColor().colorScale(specular*closest_object_color.getSpecial()));
					}
				}
				
			}
		}
		
	}
	return final_color.clip();
}
