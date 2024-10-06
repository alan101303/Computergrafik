//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

//== INCLUDES =================================================================
#include "Scene.h"

#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Mesh.h"

#include <limits>
#include <map>
#include <functional>
#include <stdexcept>

#if HAVE_OPENMP
#  include <omp.h>
#endif

//-----------------------------------------------------------------------------


Image Scene::render()
{
    // allocate new image.
    Image img(camera.width, camera.height);

    // Function rendering a full column of the image
    auto raytraceColumn = [&img, this](int x) {
        for (int y=0; y<int(camera.height); ++y)
        {
            Ray ray = camera.primary_ray(x,y);

            // compute color by tracing this ray
            vec3 color = trace(ray, 0);

            // avoid over-saturation
            color = min(color, vec3(1, 1, 1));

            // store pixel color
            img(x,y) = color;
        }
    };

    // If possible, raytrace image columns in parallel.

#if HAVE_OPENMP
    std::cout << "Rendering with up to " << omp_get_max_threads() << " threads." << std::endl;
#  pragma omp parallel for
#else
    std::cout << "Rendering singlethreaded (compiled without OpenMP)." << std::endl;
#endif

    for (int x=0; x<int(camera.width); ++x) {
        raytraceColumn(x);
    }

    // Note: compiler will elide copy.
    return img;
}

//-----------------------------------------------------------------------------

vec3 Scene::trace(const Ray& _ray, int _depth)
{
    // stop if recursion depth (=number of reflection) is too large
    if (_depth > max_depth) return vec3(0,0,0);

    // Find first intersection with an object. If an intersection is found,
    // it is stored in object, point, normal, and t.
    Object_ptr  object;
    vec3        point;
    vec3        normal;
    double      t;
    if (!intersect(_ray, object, point, normal, t))
    {
        return background;
    }

    // compute local Phong lighting (ambient+diffuse+specular)
    vec3 color = lighting(point, normal, -_ray.direction, object->material);


    /** \todo
     * Compute reflections by recursive ray tracing:
     * - check whether `object` is reflective by checking its `material.mirror`
     * - check recursion depth
     * - generate reflected ray, compute its color contribution, and mix it with
     * the color computed by local Phong lighting (use `object->material.mirror` as weight)
     * - check whether your recursive algorithm reflects the ray `max_depth` times
     */

    return color;
}

//-----------------------------------------------------------------------------

bool Scene::intersect(const Ray& _ray, Object_ptr& _object, vec3& _point, vec3& _normal, double& _t)
{
    double  t, tmin(Object::NO_INTERSECTION);
    vec3    p, n;

    for (const auto &o: objects) // for each object
    {
        if (o->intersect(_ray, p, n, t)) // does ray intersect object?
        {
            if (t < tmin) // is intersection point the currently closest one?
            {
                tmin = t;
                _object = o.get();
                _point  = p;
                _normal = n;
                _t      = t;
            }
        }
    }

    return (tmin != Object::NO_INTERSECTION);
}

vec3 Scene::lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material)
{
    //Global ambient contribution
    vec3 ambientLight = ambience * _material.ambient;
    //Initialize variables for later
    vec3 diffuseReflection(0);
    vec3 specularReflection(0);

    for (Light light : lights) {
        //a normalized vector that points towards the light source
        vec3 lDir = normalize(light.position - _point);

        //this ray will be used to check whether there are objects
        //between the point and the light source or not
        vec3 displacement(0.0002,0.0002,0.0); //used to solve shadow acne
        Ray shadowRay(_point + displacement, lDir);
        //things that I need only to make intersect() give me the boolean that I am looking for
        Object_ptr o;
        vec3 a, b;
        double t;

        //calculate diffuse and specular reflection only if the ray is not a shadow ray
        if (!intersect(shadowRay, o, a, b, t)) {
            //max is calculated to avoid light coming from behind
            diffuseReflection +=
                light.color * _material.diffuse *
                    std::max(0.0, dot(_normal, lDir));

            if (dot(_normal, lDir) < 0 || dot(mirror(lDir,_normal),_view) < 0) {
                //if the light comes from behind or doesn't go in the direction of the view,
                //no illumination: do nothing.
            } else {
                specularReflection +=
                    light.color * _material.specular *
                        std::pow(
                            dot(mirror(lDir, _normal), _view),
                                _material.shininess
                            );
            }
        }

    }

    //Calculate diffuse reflection and specular reflection for each light source
    //and add them to the right variable
    // for (const Light &light : lights) { //iterate each light source
    //
    //     //Calculate the length of the projection of the light on the normal
    //     //If negative, the light comes from behind
    //     //The length of _normal is 1, so it doesn't appear in the formula
    //     double lengthProj = dot(normalize(light.position - _point), _normal); //todo: do the first vector has the right direction?
    //     const Ray shadow_ray(_point + _normal*0.0001, vec3(1));
    //     Object_ptr object;
    //     vec3 a , b;
    //     double d;
    //     if (lengthProj < 0.0 || intersect(shadow_ray, object, a, b, d)) {
    //         continue; //exit from the for loop
    //     }
    //
    //     //calculate diffuse reflection
    //     diffuseReflection += lengthProj * (light.color * _material.diffuse);
    //
    //     //calculate specular reflection
    //     const vec3 dirRefl = mirror(light.position - _point, _normal);
    //     double rDotV = dot(dirRefl, _view); //todo: maybe error
    //     if (rDotV > 0.0) {
    //         specularReflection += (light.color * _material.specular) * pow(rDotV, _material.shininess);
    //     }
    // }

     /** \todo
     * Compute the Phong lighting:
     * - start with global ambient contribution
     * - for each light source (stored in vector `lights`) add diffuse and specular contribution
     * - only add diffuse and specular light if object is not in shadow
     *
     * You can look at the classes `Light` and `Material` to check their attributes. Feel free to use
     * the existing vector functions in vec3.h e.g. mirror, reflect, norm, dot, normalize
     */

    // visualize the normal as a RGB color for now.
    // vec3 color = (_normal + vec3(1)) / 2.0;

    return ambientLight + diffuseReflection + specularReflection;
}

//-----------------------------------------------------------------------------

void Scene::read(const std::string &_filename)
{
    std::ifstream ifs(_filename);
    if (!ifs)
        throw std::runtime_error("Cannot open file " + _filename);

    const std::map<std::string, std::function<void(void)>> entityParser = {
        {"depth",      [&]() { ifs >> max_depth; }},
        {"camera",     [&]() { ifs >> camera; }},
        {"background", [&]() { ifs >> background; }},
        {"ambience",   [&]() { ifs >> ambience; }},
        {"light",      [&]() { lights .emplace_back(ifs); }},
        {"plane",      [&]() { objects.emplace_back(new    Plane(ifs)); }},
        {"sphere",     [&]() { objects.emplace_back(new   Sphere(ifs)); }},
        {"cylinder",   [&]() { objects.emplace_back(new Cylinder(ifs)); }},
        {"mesh",       [&]() { objects.emplace_back(new     Mesh(ifs, _filename)); }}
    };

    // parse file
    std::string token;
    while (ifs && (ifs >> token) && (!ifs.eof())) {
        if (token[0] == '#') {
            ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (entityParser.count(token) == 0)
            throw std::runtime_error("Invalid token encountered: " + token);
        entityParser.at(token)();
    }
}


//=============================================================================
