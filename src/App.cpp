#include <App.h>

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
		// if no intersections
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
		//then start from max find the min pos
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

double mix(const double &a, const double &b, const double &mix) { 
	return b * mix + a * (1 - mix);
}

Color mixColor(Color a, Color b, double mix) {
	Color aMixed = a.colorScale(mix);
	Color bMixed = b.colorScale(1 - mix); 
	return aMixed.colorAdd(bMixed);
}

// 
// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
// Compute the Fresnel term for reflection (kr)
// 
double fresnel(Vect I, Vect N, double ior) { 
	double kr;

	double cosi = I.dot(N);
	if (cosi < -1) {cosi = -1;}
	if (cosi > 1) {cosi = 1;}

	double etai = 1, etat = ior; 
	if (cosi > 0) { std::swap(etai, etat); } 
	// Compute sini using Snell's law
	double sint = etai / etat * sqrt(std::max(0.0, 1 - cosi * cosi)); 
	// Total internal reflection
	if (sint >= 1) { 
		kr = 1; 
	} 
	else { 
		double cost = sqrt(std::max(0.0, 1 - sint * sint)); 
		cosi = fabs(cosi); 
		double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
		double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
		kr = (Rs * Rs + Rp * Rp) / 2; 
	} 

	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;

	return kr;
} 

// 
// Get the color that should be rendered at a ray-object intersection point
// (for implementing shadows, reflections, and other kinds of lighting models)
// 
Color getColorAt(Vect inter_position, Vect inter_ray_direction, vector<Object*> scene_objects, int closest_object, vector<Source*> light_sources, double accuracy, double ambient_light, const int &depth) {
	
	Color closest_object_color = scene_objects.at(closest_object)->getColor();
	Vect closest_object_normal = scene_objects.at(closest_object)->getNormalAt(inter_position);

	////// CHECKERED FLOOR //////
	if (closest_object_color.getReflectivity() == 0.222) {
		int square = (int) inter_position.getX() + (int) inter_position.getZ();

		if ((square % 2) == 0) {
			// 0 is going to be a black tile
			// closest_object_color = Color(0.0, 0.0, 0.0, closest_object_color.getReflectivity(), closest_object_color.getTransparency());
			closest_object_color = closest_object_color.colorAverage(Color(0.0, 0.0, 0.0, closest_object_color.getReflectivity(), closest_object_color.getTransparency()));
		}

		else {
			// 1 is going to be a white tile
			// closest_object_color = Color(1.0, 1.0, 1.0, closest_object_color.getReflectivity(), closest_object_color.getTransparency());
			closest_object_color = closest_object_color.colorAverage(Color(1.0, 1.0, 1.0, closest_object_color.getReflectivity(), closest_object_color.getTransparency()));
		}
	}
	
	// Start with applying some constant value for ambient light
	Color final_color = closest_object_color.colorScale(ambient_light);

	////// REFLECTIONS & REFRACTIONS //////

	if (depth < MAX_RECURSION_DEPTH) {

		double ior = 1.5;
		double biasAmount = 1e-4; 

		double kr = fresnel(inter_ray_direction, closest_object_normal, ior); // Fresnel term
		bool outside = inter_ray_direction.dot(closest_object_normal) < 0;
		Vect bias = closest_object_normal.multiply(biasAmount);

		Color reflection_color, refraction_color; 

		////// REFLECTION //////

		if (closest_object_color.getReflectivity() > 0.0) {

			Vect reflection_dir = inter_ray_direction.reflect(closest_object_normal).normalize();
			Vect reflectionRayOrig = outside ? inter_position.add(bias) : inter_position.subtract(bias);

			Ray reflection_ray (reflectionRayOrig, reflection_dir);

			// Determine what the reflection ray intersects with
			vector<double> reflection_intersections;

			for (int i = 0; i < scene_objects.size(); i++) {
				reflection_intersections.push_back(scene_objects.at(i)->findIntersection(reflection_ray));
			}

			int closest_object_with_reflection = closestObject(reflection_intersections);

			if (closest_object_with_reflection != -1) { // Reflection ray hit something
				if (reflection_intersections.at(closest_object_with_reflection) > accuracy) {
					Vect reflection_intersection_pos = inter_position.add(reflection_dir.multiply(reflection_intersections.at(closest_object_with_reflection)));

					// RECURSION
					reflection_color = getColorAt(reflection_intersection_pos, reflection_dir, scene_objects, closest_object_with_reflection, light_sources, accuracy, ambient_light, depth + 1);
				}
			}
		}

		////// REFRACTION //////

		if (closest_object_color.getTransparency() > 0.0) {

			Vect refraction_dir; 
			Vect refractionRayOrig;

			if (kr < 1) { 
				refraction_dir = (inter_ray_direction.refract(closest_object_normal, ior)).normalize();
				refractionRayOrig = outside ? inter_position.subtract(bias) : inter_position.add(bias);
			}

			Ray refraction_ray (refractionRayOrig, refraction_dir);

			// Determine what the refraction ray intersects with
			vector<double> refraction_intersections;

			for (int i = 0; i < scene_objects.size(); i++) {
				refraction_intersections.push_back(scene_objects.at(i)->findIntersection(refraction_ray));
			}

			int closest_object_with_refraction = closestObject(refraction_intersections);

			if (closest_object_with_refraction != -1) { // Refraction ray hit something
				if (refraction_intersections.at(closest_object_with_refraction) > accuracy) {
					Vect refraction_inter_pos = inter_position.add(refraction_dir.multiply(refraction_intersections.at(closest_object_with_refraction)));

					// RECURSION
					refraction_color = getColorAt(refraction_inter_pos, refraction_dir, scene_objects, closest_object_with_refraction, light_sources, accuracy, ambient_light, depth + 1);
				}
			}
		}

		// hitColor += reflectionColor * kr + refractionColor * (1 - kr);
		final_color = final_color.colorAdd(
			reflection_color.colorScale((kr) * closest_object_color.getReflectivity()).colorAdd(
				refraction_color.colorScale((1-kr) * closest_object_color.getTransparency())
				)
			);
	}

	////// SHADOWS //////
	for (int i = 0; i < light_sources.size(); i++){
		
		//distance from intersection point to the light source
		Vect light_distance = light_sources.at(i)->getLightPosition().subtract(inter_position);
		
		///direction from intersection point to the light source = normalize(source - intersection)
		Vect light_dir = light_distance.normalize();
		
		double cos_angle = closest_object_normal.dot(light_dir);
		
		if (cos_angle > 0){
			//test for shadows
			
			bool shadow = false;
			double magnitude_light_distance = light_distance.magnitude();

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
				final_color = final_color.colorAdd(closest_object_color.colorMultiply(light_sources.at(i)->getLightColor()).colorScale(cos_angle));
				
				if (closest_object_color.getReflectivity() > 0.0) {
					double objReflectivity = closest_object_color.getReflectivity();

					if (objReflectivity > 1.0) {objReflectivity = 1.0;}
					
					Vect reflection_dir = (inter_ray_direction.reflect(closest_object_normal)).normalize();
					
					double specular = reflection_dir.dot(light_dir);
					
					if (specular > 0) {
						specular = pow(specular, 10);
						final_color = final_color.colorAdd(light_sources.at(i)->getLightColor().colorScale(specular*objReflectivity));
					}
				}
				
			}
		}
		
	}
	return final_color.clip();
}

vector<Object*> drawCube(Vect center, double xWidth, double yWidth, double zWidth, Color color) {
	vector<Object*> triangles;

	Vect min (center.getX() - xWidth/2, center.getY() - yWidth/2, center.getZ() - zWidth/2);
	Vect max (center.getX() + xWidth/2, center.getY() + yWidth/2, center.getZ() + zWidth/2);

	// BACK SIDE
	// 
	// min1 --- min3
	//  |\       |
	//  | \      |
	//  |  \     |
	//  |   \    |
	//  |    \   |
	//  |     \  |
	//  |      \ |
	//  |       \|
	// min ---- min2

	Vect min1 (min.getX(), max.getY(), min.getZ());
	Vect min2 (max.getX(), min.getY(), min.getZ());
	Vect min3 (max.getX(), max.getY(), min.getZ());
	triangles.push_back(new Triangle(min, min1, min2, color));
	triangles.push_back(new Triangle(min1, min3, min2, color));

	// FRONT SIDE
	// 
	// max1 --- max
	//  |\       |
	//  | \      |
	//  |  \     |
	//  |   \    |
	//  |    \   |
	//  |     \  |
	//  |      \ |
	//  |       \|
	// max3 --- max2

	Vect max1 (min.getX(), max.getY(), max.getZ());
	Vect max2 (max.getX(), min.getY(), max.getZ());
	Vect max3 (min.getX(), min.getY(), max.getZ());
	triangles.push_back(new Triangle(max, max1, max2, color));
	triangles.push_back(new Triangle(max1, max3, max2, color));

	// LEFT SIDE
	// 
	// min1 --- max1
	//  |\       |
	//  | \      |
	//  |  \     |
	//  |   \    |
	//  |    \   |
	//  |     \  |
	//  |      \ |
	//  |       \|
	// min --- max3

	triangles.push_back(new Triangle(min1, min, max3, color));
	triangles.push_back(new Triangle(max1, min1, max3, color));

	// RIGHT SIDE
	// 
	// max --- min3
	//  |\       |
	//  | \      |
	//  |  \     |
	//  |   \    |
	//  |    \   |
	//  |     \  |
	//  |      \ |
	//  |       \|
	// max2 --- min2

	triangles.push_back(new Triangle(max, max2, min2, color));
	triangles.push_back(new Triangle(min3, max, min2, color));

	// TOP SIDE
	// 
	// min1 --- min3
	//  |\       |
	//  | \      |
	//  |  \     |
	//  |   \    |
	//  |    \   |
	//  |     \  |
	//  |      \ |
	//  |       \|
	// max1 --- max

	triangles.push_back(new Triangle(min1, max1, max, color));
	triangles.push_back(new Triangle(min3, min1, max, color));

	// BOTTOM SIDE
	// 
	// min --- min2
	//  |\       |
	//  | \      |
	//  |  \     |
	//  |   \    |
	//  |    \   |
	//  |     \  |
	//  |      \ |
	//  |       \|
	// max3 --- max2

	triangles.push_back(new Triangle(min, max3, max2, color));
	triangles.push_back(new Triangle(min2, min, max2, color));

	return triangles;
}
