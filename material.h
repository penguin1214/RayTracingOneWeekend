//
// Created by Jinglei Yang on 7/29/2017.
//

#ifndef RAYTRACINGONEWEEKEND_MATERIAL_H
#define RAYTRACINGONEWEEKEND_MATERIAL_H

#include "ray.h"
#include "hitable.h"


vec3 random_in_unit_sphere() {
    // pick random point in cube and check if it's in the sphere
    vec3 p;
    do{
        p = vec3((2*((double)rand()/(RAND_MAX))-1), (2*((double)rand()/(RAND_MAX))-1), (2*((double)rand()/(RAND_MAX))-1));
    } while (dot(p, p) >= 1.0);
    return p;
}

vec3 reflect(const vec3& v, const vec3& norm) {
    return v - 2*dot(v,norm)*norm;
}

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian: public material {
public:
    vec3 albedo;

    // constructor
    lambertian(const vec3& albedo) : albedo(albedo) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.norm + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
};

class metal: public material {
public:
    vec3 albedo;
    float fuzz;

    metal(const vec3& albedo, const float f) : albedo(albedo) {if (f<1) {fuzz = f;} else {fuzz=1.0;}}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected_dir = reflect(unit(r_in.direction()), rec.norm) + fuzz*random_in_unit_sphere();
        scattered = ray(rec.p, reflected_dir);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.norm) > 0);
    }
};

#endif //RAYTRACINGONEWEEKEND_MATERIAL_H
