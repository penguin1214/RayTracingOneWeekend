//
// Created by Jinglei Yang on 7/29/17.
//

#ifndef RAYTRACINGONEWEEKEND_RAY_H
#define RAYTRACINGONEWEEKEND_RAY_H

#include "vec3.h"

class ray {
public:
    vec3 o;
    vec3 d;

    // constructor
    ray() {}
    ray(const vec3& a, const vec3& b) {o = a; d = b;}
    vec3 origin() const { return o;}
    vec3 direction() const { return d;}
    vec3 point_at_parameter(float t) const { return o+d*t;}
};

#endif //RAYTRACINGONEWEEKEND_RAY_H
