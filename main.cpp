#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

using namespace std;

vec3 color(const ray& r, const vec3 start_val, const vec3 end_val);

int main() {
    ofstream myfile;
    myfile.open("image.ppm");
    int width = 200;
    int height = 100;
    myfile << "P3\n" << width << " " << height << "\n255\n";
    vec3 lower_left_corner = vec3(-2.0, -1.0, -1.0);
    vec3 horizontal = vec3(4.0, 0.0, 0.0);
    vec3 vertical = vec3(0.0, 2.0, 0.0);
    vec3 origin = vec3(0.0);

    for (int i = height; i > 0; --i) {
        for (int j = 0; j < width; ++j) {
            float u = float(i) / float(width);  // u, v cord??
            float v = float(j) / float(height);
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
    // do lerp
    vec3 unit_dir = unit(r.d);
    float t = 0.5*(unit_dir.y() + 1.0);
    return (1.0-t)*start_val + t*end_val;
}