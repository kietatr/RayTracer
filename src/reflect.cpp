	if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) { 
        // REFFLECT
        // compute reflection direction (not need to normalize because all vectors
        // are already normalized)
        Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit); 
        refldir.normalize(); 
        Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1); 

        // REFRACT
        float facingratio = -raydir.dot(nhit); 
        // change the mix value to tweak the effect
        float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1); 
        Vec3f refraction = 0; 
        // if the sphere is also transparent compute refraction ray (transmission)
        if (sphere->transparency) { 
            float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface? 
            float cosi = -nhit.dot(raydir); 
            float k = 1 - eta * eta * (1 - cosi * cosi); 
            Vec3f refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k)); 
            refrdir.normalize(); 
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1); 
        } 
        // the result is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = ( 
            reflection * fresneleffect + 
            refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor; 
    }

    ////////////////////////////////////////////////////////

	////// REFLECTION //////
	if (closest_object_color.getReflectivity() > 0 && closest_object_color.getReflectivity() <= 1) {
		// reflection from objects with specular intensity (0-1 = specular)
		Vect reflection_dir = (inter_ray_direction.reflect(closest_object_normal)).normalize();

		Ray reflection_ray (inter_position, reflection_dir);

		// Determine what the ray intersects with first
		vector<double> reflection_intersections;

		for (int i = 0; i < scene_objects.size(); i++) {
			reflection_intersections.push_back(scene_objects.at(i)->findIntersection(reflection_ray));
		}

		int closest_object_with_reflection = closestObject(reflection_intersections);

		if (closest_object_with_reflection != -1) { // Reflection ray hit something
			if (reflection_intersections.at(closest_object_with_reflection) > accuracy) {
				Vect reflection_intersection_position = inter_position.add(reflection_dir.multiply(reflection_intersections.at(closest_object_with_reflection)));
				
				Vect reflection_intersection_ray_direction = reflection_dir;

				// RECURSION
				Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, closest_object_with_reflection, light_sources, accuracy, ambient_light);

				final_color = final_color.colorAdd(reflection_intersection_color.colorScale(closest_object_color.getReflectivity()));
			}
		}
	}