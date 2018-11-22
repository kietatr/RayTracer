// Setup the frickin canvas
var theCanvas = document.getElementById('theCanvas');
var width = 700 * 0.5;
var height = 500 * 0.5;

theCanvas.width = width;
theCanvas.height = height;
theCanvas.style.cssText = 'width:' + (width * 2) + 'px; height:' + (height*2) + 'px';

var ctx = theCanvas.getContext("2d");
var data = ctx.getImageData(0, 0, width, height);

var scene = {};

scene.camera = {
	point: {x: 0, y: 1.8, z: 10},
	fieldOfView: 45, // angle in degrees
	vector: {x: 0, y: 3, z: 0}
}

scene.lights = [
	{x: -30, y: -10, z: 20}
];

scene.objects = [
    {
        type: 'sphere',
        point: {x: 0, y: 3.5, z: -3},
        color: {x: 0, y: 255, z: 0},
        specular: 0.2,
        lambert: 0.7,
        ambient: 0.1,
        radius: 3
    },
    {
        type: 'sphere',
        point: {x: -4, y: 2, z: -1},
        color: {x: 255, y: 255, z: 255},
        specular: 0.1,
        lambert: 0.9,
        ambient: 0.0,
        radius: 0.5
    },
    {
        type: 'sphere',
        point: {x: -4, y: 5, z: -1},
        color: {x: 0, y: 0, z: 255},
        specular: 0.2,
        lambert: 0.7,
        ambient: 0.1,
        radius: 0.3
    }
];

function toRadians(angle) {
	return angle * (Math.PI / 180);
}

function render(scene) {
	var camera = scene.camera,
        objects = scene.objects,
        lights = scene.lights;

    var eyeVector = Vector.unitVector(Vector.subtract(camera.vector, camera.point));
    var eyeVectorRight = Vector.unitVector(Vector.crossProduct(eyeVector, Vector.UP));
    var eyeVectorUp = Vector.unitVector(Vector.crossProduct(eyeVectorRight, eyeVector));

    var fovRadians = toRadians(camera.fieldOfView / 2);
    var heightWidthRatio = height / width,
        halfWidth = Math.tan(fovRadians),
        halfHeight = heightWidthRatio * halfWidth,
        camerawidth = halfWidth * 2,
        cameraheight = halfHeight * 2,
        pixelWidth = camerawidth / (width - 1),
        pixelHeight = cameraheight / (height - 1);

    var index, color;
    var ray = {
        point: camera.point
    };

    for (var x = 0; x < width; x++) {
        for (var y = 0; y < height; y++)  {
        	var xcomp = Vector.scale(eyeVectorRight, (x * pixelWidth) - halfWidth),
                ycomp = Vector.scale(eyeVectorUp, (y * pixelHeight) - halfHeight);

            ray.vector = Vector.unitVector(Vector.add3(eyeVector, xcomp, ycomp));

            color = trace(ray, scene, 0);
            index = (x * 4) + (y * width * 4),
            data.data[index + 0] = color.x;
            data.data[index + 1] = color.y;
            data.data[index + 2] = color.z;
            data.data[index + 3] = 255;
        }
    }

    ctx.putImageData(data, 0, 0);
}

function trace(ray, scene, depth) {
	if (depth > 3) return;

    var distObject = intersectScene(ray, scene);

    if (distObject[0] === Infinity) {
        return Vector.WHITE;
    }

    var dist = distObject[0],
        object = distObject[1];

    var pointAtTime = Vector.add(ray.point, Vector.scale(ray.vector, dist));

    return surface(ray, scene, object, pointAtTime, sphereNormal(object, pointAtTime), depth);
}

function intersectScene(ray, scene) {
	var closest = [Infinity, null];

	for (var i = 0; i < scene.objects.length; i++) {

        var object = scene.objects[i];
        var dist = sphereIntersection(object, ray);

        if (dist !== undefined && dist < closest[0]) {
            closest = [dist, object];
        }

    }

    return closest;
}

function sphereIntersection(sphere, ray) {
    var eye_to_center = Vector.subtract(sphere.point, ray.point),
        // picture a triangle with one side going straight from the camera point
        // to the center of the sphere, another side being the vector.
        // the final side is a right angle.
        //
        // This equation first figures out the length of the vector side
        v = Vector.dotProduct(eye_to_center, ray.vector),
        // then the length of the straight from the camera to the center
        // of the sphere
        eoDot = Vector.dotProduct(eye_to_center, eye_to_center),
        // and compute a segment from the right angle of the triangle to a point
        // on the `v` line that also intersects the circle
        discriminant = (sphere.radius * sphere.radius) - eoDot + (v * v);
    // If the discriminant is negative, that means that the sphere hasn't
    // been hit by the ray
    if (discriminant < 0) {
        return;
    } else {
        // otherwise, we return the distance from the camera point to the sphere
        // `Math.sqrt(dotProduct(a, a))` is the length of a vector, so
        // `v - Math.sqrt(discriminant)` means the length of the the vector
        // just from the camera to the intersection point.
        return v - Math.sqrt(discriminant);
    }
}

// A normal is, at each point on the surface of a sphere or some other object,
// a vector that's perpendicular to the surface and radiates outward. We need
// to know this so that we can calculate the way that a ray reflects off of
// a sphere.
function sphereNormal(sphere, pos) {
    return Vector.unitVector(
        Vector.subtract(pos, sphere.point));
}

// # Surface
//
// ![](http://farm3.staticflickr.com/2851/10524788334_f2e3903b36_b.jpg)
//
// If `trace()` determines that a ray intersected with an object, `surface`
// decides what color it acquires from the interaction.
function surface(ray, scene, object, pointAtTime, normal, depth) {
    var b = object.color,
        c = Vector.ZERO,
        lambertAmount = 0;

    // **[Lambert shading](http://en.wikipedia.org/wiki/Lambertian_reflectance)**
    // is our pretty shading, which shows gradations from the most lit point on
    // the object to the least.
    if (object.lambert) {
        for (var i = 0; i < scene.lights.length; i++) {
            var lightPoint = scene.lights[0];
            // First: can we see the light? If not, this is a shadowy area
            // and it gets no light from the lambert shading process.
            if (!isLightVisible(pointAtTime, scene, lightPoint)) continue;
            // Otherwise, calculate the lambertian reflectance, which
            // essentially is a 'diffuse' lighting system - direct light
            // is bright, and from there, less direct light is gradually,
            // beautifully, less light.
            var contribution = Vector.dotProduct(Vector.unitVector(
                Vector.subtract(lightPoint, pointAtTime)), normal);
            // sometimes this formula can return negatives, so we check:
            // we only want positive values for lighting.
            if (contribution > 0) lambertAmount += contribution;
        }
    }

    // **[Specular](https://en.wikipedia.org/wiki/Specular_reflection)** is a fancy word for 'reflective': rays that hit objects
    // with specular surfaces bounce off and acquire the colors of other objects
    // they bounce into.
    if (object.specular) {
        // This is basically the same thing as what we did in `render()`, just
        // instead of looking from the viewpoint of the camera, we're looking
        // from a point on the surface of a shiny object, seeing what it sees
        // and making that part of a reflection.
        var reflectedRay = {
            point: pointAtTime,
            vector: Vector.reflectThrough(ray.vector, normal)
        };
        var reflectedColor = trace(reflectedRay, scene, ++depth);
        if (reflectedColor) {
            c = Vector.add(c, Vector.scale(reflectedColor, object.specular));
        }
    }

    // lambert should never 'blow out' the lighting of an object,
    // even if the ray bounces between a lot of things and hits lights
    lambertAmount = Math.min(1, lambertAmount);

    // **Ambient** colors shine bright regardless of whether there's a light visible -
    // a circle with a totally ambient blue color will always just be a flat blue
    // circle.
    return Vector.add3(c,
        Vector.scale(b, lambertAmount * object.lambert),
        Vector.scale(b, object.ambient));
}

// Check whether a light is visible from some point on the surface of something.
// Note that there might be an intersection here, which is tricky - but if it's
// tiny, it's actually an intersection with the object we're trying to decide
// the surface of. That's why we check for `> -0.005` at the end.
//
// This is the part that makes objects cast shadows on each other: from here
// we'd check to see if the area in a shadowy spot can 'see' a light, and when
// this returns `false`, we make the area shadowy.
function isLightVisible(pt, scene, light) {
    var distObject =  intersectScene({
        point: pt,
        vector: Vector.unitVector(Vector.subtract(pt, light))
    }, scene);
    return distObject[0] > -0.005;
}

// Here we do a little fun magic, just for the heck of it. We have three spheres
    // in the scene - `scene.objects[0]` is the big one, kind of like 'Earth'.
    //
    // The other two are little, so let's make them orbit around the big one
    // and look cool!

    // The orbits of the two planets. We use some basic trigonetry to do the orbits:
    // using `Math.sin()` and `Math.cos()`, it's simple to get a
    // [unit circle](http://en.wikipedia.org/wiki/Unit_circle)
    // for each planet. Here's [an article I wrote](http://macwright.org/2013/03/05/math-for-pictures.html)
    // for getting to know `sin` and `cos`.
// var planet1 = 0;
// var planet2 = 0;

var planet1 = 0.0;
var planet2 = 0.0;

function tick() {
    // make one planet spin a little bit faster than the other, just for
    // effect.
    planet1 += 0.1;
    planet2 += 0.2;

    // set the position of each moon with some trig.
    scene.objects[1].point.x = Math.sin(planet1) * 3.5;
    scene.objects[1].point.z = -3 + (Math.cos(planet1) * 3.5);

    scene.objects[2].point.x += Math.sin(planet2) * 4;
    scene.objects[2].point.z += -3 + (Math.cos(planet2) * 4);

    // finally, render the scene!
    render(scene);

    // and as soon as we're finished, render it again and move the planets
    // again
    if (playing) setTimeout(tick, 10);
}

var playing = false;

function play() {
    playing = true;
    tick();
}

function stop() {
    playing = false;
}

render(scene);

// Then let the user control a cute playing animation!
document.getElementById('play').onclick = play;
document.getElementById('stop').onclick = stop;