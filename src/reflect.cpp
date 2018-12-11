	Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir, const std::vector<Sphere> &spheres, const int &depth) 
     

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

    double mix(const double &a, const double &b, const double &mix) { 
        return b * mix + a * (1 - mix);
    } 


    Color getColorAt(Vect inter_position, Vect inter_ray_direction, vector<Object*> scene_objects, int closest_object, vector<Source*> light_sources, double accuracy, double ambient_light){

    ////// REFLECTIONS & REFRACTIONS //////

    bool inside = false; 
    if (inter_ray_direction.dot(closest_object_normal) > 0) {
        closest_object_normal = closest_object_normal.negative(); 
        inside = true;
    }

    if (closest_object_color.getReflectivity() > 0 || closest_object_color.getTransparency() > 0) {
        
        double facingratio = -inter_ray_direction.dot(closest_object_normal); 
        double fresneleffect = mix(pow(1.0 - facingratio, 3.0), 1.0, 0.7);

        ////// REFLECTION //////
        Vect reflection_dir = (inter_ray_direction.reflect(closest_object_normal)).normalize();
        Ray reflection_ray (inter_position, reflection_dir);

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
                Color reflection_color = getColorAt(reflection_intersection_pos, reflection_dir, scene_objects, closest_object_with_reflection, light_sources, accuracy, ambient_light);

                final_color = final_color.colorAdd(reflection_color.colorScale(fresneleffect * closest_object_color.getReflectivity()));
            }
        }

        ////// REFRACTION //////
        Ray refraction_ray (Vect(0,0,0), Vect(0,0,0));
        Vect refraction_dir (0,0,0);

        if (closest_object_color.getTransparency() > 0.0) { 
            double ior = 1.1;
            double eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface? 

            double cosi = -(closest_object_normal.dot(inter_ray_direction)); 
            double k = 1 - eta * eta * (1 - cosi * cosi);

            Vect refraction_dir = (inter_ray_direction.multiply(eta)).add( (closest_object_normal .multiply(eta *  cosi - sqrt(k))) );

            refraction_dir = refraction_dir.normalize(); 
            // refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
            Ray refraction_ray (inter_position, refraction_dir);
        }

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
                Color refraction_color = getColorAt(refraction_inter_pos, refraction_dir, scene_objects, closest_object_with_refraction, light_sources, accuracy, ambient_light);

                final_color = final_color.colorAdd(refraction_color.colorScale((1 - fresneleffect) * closest_object_color.getTransparency()));
            }
        }
    }