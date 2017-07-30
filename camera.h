//
// Created by Jinglei Yang on 7/29/2017.
//

#ifndef RAYTRACINGONEWEEKEND_CAMERA_H
#define RAYTRACINGONEWEEKEND_CAMERA_H

#include "ray.h"

class camera {
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
        float theta = vfov*M_PI/180;    // convert to radian
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        vec3 u,v,w;
        w = unit(lookfrom-lookat);
        u = unit(cross(vup, w));
        v = unit(cross(w, u));
        lower_left_corner = vec3(-half_width, -half_height, -1.0);
        lower_left_corner = origin - half_width*u - half_height*v -w;
        horizontal = 2*half_width*u;
        vertical = 2*half_height*v;
    }

    ray get_ray(float u, float v) {
        return ray(origin, lower_left_corner+u*horizontal+v*vertical-origin);
    }
};
#endif //RAYTRACINGONEWEEKEND_CAMERA_H
