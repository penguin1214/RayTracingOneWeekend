#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

using namespace std;

vec3 color(const ray& r, const vec3 start_val, const vec3 end_val);

float hit_sphere(const ray &r, const vec3 &center, float radius);

int main() {
    ofstream myfile;
    myfile.open("image.ppm");
    int width = 200;
    int height = 100;
    myfile << "P3\n" << width << " " << height << "\n255\n";
    vec3 lower_left_corner = vec3(-2.0, -1.0, -1.0);
    vec3 horizontal = vec3(4.0, 0.0, 0.0);
    vec3 vertical = vec3(0.0, 2.0, 0.0);
    vec3 origin = vec3(0.0, 0.0, 0.0);

    for (int i = height-1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            float u = float(j) / float(width);  // u, v cord??
            float v = float(i) / float(height);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r, vec3(1.0, 1.0, 1.0), vec3(0.5, 0.7, 1.0));
            int ir = int(255.99*col.e[0]);
            int ig = int(255.99*col.e[1]);
            int ib = int(255.99*col.e[2]);
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

vec3 color(const ray& r, const vec3 start_val, const vec3 end_val) {
    float t = hit_sphere(r, vec3(0,0,-1), 0.5);
    if (t > 0.0) {
        // hit! compute norm
        vec3 norm = unit(r.point_at_parameter(t) - vec3(0,0,-1));
        return 0.5*vec3(norm.x()+1, norm.y()+1, norm.z()+1);
    }
    vec3 unit_dir = unit(r.d);
    t = 0.5*(unit_dir.y() + 1.0);
    return (1.0-t)*start_val + t*end_val;
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