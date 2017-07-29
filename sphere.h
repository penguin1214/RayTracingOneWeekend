//
// Created by Jinglei Yang on 7/29/2017.
//

#ifndef RAYTRACINGONEWEEKEND_SPHERE_H
#define RAYTRACINGONEWEEKEND_SPHERE_H

#include "hitable.h"

class sphere: public hitable {
public:

    vec3 center;
    float radius;

    // constructor
    sphere() {}
    sphere(vec3 center, float radius) : center(center), radius(radius) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float disc = b*b-a*c;
    if ((sqrt(disc)) >= 0) {
        // calculate hit point
        float temp = (-b - sqrt(b * b - a * c)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.norm = (rec.p - center) / radius; // get unit normal
            return true;
        }
    }
    return false;
}

#endif //RAYTRACINGONEWEEKEND_SPHERE_H
