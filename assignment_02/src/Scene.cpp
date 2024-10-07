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
#include <omp.h>
#endif

//-----------------------------------------------------------------------------

Image Scene::render()
{
    // allocate new image.
    Image img(camera.width, camera.height);

    // Function rendering a full column of the image
    auto raytraceColumn = [&img, this](int x)
    {
        for (int y = 0; y < int(camera.height); ++y)
        {
            Ray ray = camera.primary_ray(x, y);

            // compute color by tracing this ray
            vec3 color = trace(ray, 0);

            // avoid over-saturation
            color = min(color, vec3(1, 1, 1));

            // store pixel color
            img(x, y) = color;
        }
    };

    // If possible, raytrace image columns in parallel.
    /*
    #if HAVE_OPENMP
        std::cout << "Rendering with up to " << omp_get_max_threads() << " threads." << std::endl;
    #  pragma omp parallel for
    #else
        std::cout << "Rendering singlethreaded (compiled without OpenMP)." << std::endl;
    #endif
    */
    for (int x = 0; x < int(camera.width); ++x)
    {
        raytraceColumn(x);
    }

    // Note: compiler will elide copy.
    return img;
}

//-----------------------------------------------------------------------------

vec3 Scene::trace(const Ray &_ray, int _depth)
{
    // stop if recursion depth (=number of reflection) is too large
    if (_depth > max_depth)
        return vec3(0, 0, 0);

    // Find first intersection with an object. If an intersection is found,
    // it is stored in object, point, normal, and t.
    Object_ptr object;
    vec3 point;
    vec3 normal;
    double t;
    if (!intersect(_ray, object, point, normal, t))
    {
        return background;
    }

    // compute local Phong lighting (ambient+diffuse+specular)
    vec3 color = lighting(point, normal, -_ray.direction, object->material);

    return color;
}

//-----------------------------------------------------------------------------

bool Scene::intersect(const Ray &_ray, Object_ptr &_object, vec3 &_point, vec3 &_normal, double &_t)
{
    double t, tmin(Object::NO_INTERSECTION);
    vec3 p, n;

    for (const auto &o : objects) // for each object
    {
        if (o->intersect(_ray, p, n, t)) // does ray intersect object?
        {
            if (t < tmin) // is intersection point the currently closest one?
            {
                tmin = t;
                _object = o.get();
                _point = p;
                _normal = n;
                _t = t;
            }
        }
    }

    return (tmin != Object::NO_INTERSECTION);
}

vec3 Scene::lighting(const vec3 &_point, const vec3 &_normal, const vec3 &_view, const Material &_material)
{
    vec3 color = ambience * _material.ambient;
    for (Light light : lights)
    {
        //  normalized vector that points towards the light source
        vec3 normalized_point_light = normalize(light.position - _point);

        // this ray will be used to check whether there are objects
        // between the point and the light source or not
        vec3 displacement(0.0002, 0.0002, 0.0); // used to solve shadow acne
        Ray shadowRay(_point + displacement, normalized_point_light);
        // things that I need only to make intersect() give me the boolean that I am looking for
        Object_ptr o;
        vec3 a, b;
        double t;

        // calculate diffuse and specular reflection only if the ray is not a shadow ray
        if (!intersect(shadowRay, o, a, b, t))
        {
            vec3 normalized_normal = normalize(_normal);
            for (auto &light : lights)
            {

                // Add diffuse lighting and max is calculated to avoid light coming from behind
                color += light.color * _material.diffuse * std::max(0.0, dot(normalized_normal, normalized_point_light));

                // The light doesn't come from behind and it goes into the direction of the view
                if (dot(normalized_normal, normalized_point_light) >= 0 && dot(mirror(normalized_point_light, normalized_normal), _view) >= 0)
                {
                    // Add specular lighting
                    color += light.color * _material.specular * std::pow(dot(mirror(normalized_point_light, normalized_normal), _view), _material.shininess);
                }
            }

           
        }
    }

     return color;

}

//-----------------------------------------------------------------------------

void Scene::read(const std::string &_filename)
{
    std::ifstream ifs(_filename);
    if (!ifs)
        throw std::runtime_error("Cannot open file " + _filename);

    const std::map<std::string, std::function<void(void)>> entityParser = {
        {"depth", [&]()
         { ifs >> max_depth; }},
        {"camera", [&]()
         { ifs >> camera; }},
        {"background", [&]()
         { ifs >> background; }},
        {"ambience", [&]()
         { ifs >> ambience; }},
        {"light", [&]()
         { lights.emplace_back(ifs); }},
        {"plane", [&]()
         { objects.emplace_back(new Plane(ifs)); }},
        {"sphere", [&]()
         { objects.emplace_back(new Sphere(ifs)); }},
        {"cylinder", [&]()
         { objects.emplace_back(new Cylinder(ifs)); }},
        {"mesh", [&]()
         { objects.emplace_back(new Mesh(ifs, _filename)); }}};

    // parse file
    std::string token;
    while (ifs && (ifs >> token) && (!ifs.eof()))
    {
        if (token[0] == '#')
        {
            ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (entityParser.count(token) == 0)
            throw std::runtime_error("Invalid token encountered: " + token);
        entityParser.at(token)();
    }
}

//=============================================================================
