#include <iostream>
#include <fstream>
#include <cstdlib>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

#define MAXFLOAT 100.0
using namespace std;

vec3 color(const ray &r, hitable *world);

float hit_sphere(const ray &r, const vec3 &center, float radius);

int main() {
    ofstream myfile;
    myfile.open("image.ppm");
    int width = 200;
    int height = 100;
    int ns = 100;   // sample number

    hitable* list[2];
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    hitable* world = new hitable_list(list, 2);

    myfile << "P3\n" << width << " " << height << "\n255\n";
    camera cam;

    for (int i = height-1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            vec3 col(0,0,0);
            for (int s = 0; s < ns; ++s) {
                float random = ((double) rand() / (RAND_MAX)) + 1;
                float u = float(j+random) / float(width);  // u, v cord??
                float v = float(i+random) / float(height);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            int ir = int(255.99*col.e[0]);  // why use 255.99?
            int ig = int(255.99*col.e[1]);
            int ib = int(255.99*col.e[2]);
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

vec3 color(const ray &r, hitable *world) {
    // shading
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5*vec3(rec.norm.x()+1, rec.norm.y()+1, rec.norm.z()+1);
    } else {
        vec3 unit_dir = unit(r.d);
        float t = 0.5*(unit_dir.y() + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
    }
}

float hit_sphere(const ray &r, const vec3 &center, float radius) {
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot((r.origin()-center), r.direction());
    float c = dot(r.origin()-center, r.origin()-center) - radius*radius;
    float disc = b*b-4*a*c;
    if ((sqrt(disc)) >= 0) {
        // calculate hit point
        return (-b-sqrt(disc)) / (2.0*a);
    } else {
        return -1;
    }
}