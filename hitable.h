//
// Created by Jinglei Yang on 7/29/2017.
//

#ifndef RAYTRACINGONEWEEKEND_HITABLE_H
#define RAYTRACINGONEWEEKEND_HITABLE_H

#include "ray.h"

struct hit_record {
    float t;
    vec3 p;
    vec3 norm;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //RAYTRACINGONEWEEKEND_HITABLE_H
