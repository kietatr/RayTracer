    /////////////////////////
    // Cook-Torrance
    /////////////////////////

    if (depth < MAX_RECURSION_DEPTH) {
        Color reflection_color (0,0,0,0,0);
        Color refraction_color (0,0,0,0,0);

        float glassR0 = 0.4;
        float eta = 0.67;
        Vect glassEta (0.65, 0.67, 0.68);

        for (int i = 0; i < light_sources.size(); i++) {
            // distance from intersection point to the light source
            Vect light_distance = light_sources.at(i)->getLightPosition().subtract(inter_position);
            // direction from intersection point to the light source = normalize(source - intersection)
            Vect L = light_distance.normalize();
            Vect E = inter_ray_direction.normalize();
            Vect N = closest_object_normal.normalize();
            
            float dotLN = L.dot(N);
            if (dotLN > 1.0) dotLN = 1.0;
            if (dotLN < 0.0) dotLN = 0.0;

            // float F = glassR0 + (1 - glassR0) * pow((1 - dotLN), 5);
            float F = mix(pow((1 - dotLN), 5), 1.0, glassR0);

            ////// REFLECTION //////

            if (closest_object_color.getReflectivity() > 0.0) {
                Vect reflection_dir = E.reflect(N);
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
                        reflection_color = getColorAt(reflection_intersection_pos, reflection_dir, scene_objects, closest_object_with_reflection, light_sources, accuracy, ambient_light, depth + 1);
                    }
                }
            }

            ////// REFRACTION //////

            if (closest_object_color.getTransparency() > 0.0) { 
                Vect refraction_dir = E.refract(N, eta);
                Ray refraction_ray (inter_position, refraction_dir);

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
            
            // Final color = mix reflect and refract according to Fresnel value
            final_color = final_color.colorAdd(mixColor(reflection_color, refraction_color, F));
        }