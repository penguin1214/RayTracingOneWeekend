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

float schlick(float cosine, float ref_idx) {
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

bool refract(const vec3& v, const vec3& norm, float ni_over_nt, vec3& refracted) {
    vec3 unit_v = unit(v);
    float dt = dot(unit_v,norm);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt*(v - norm*dt) - norm*sqrt(discriminant);
        return true;
    } else {
        return false;
    }
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

class dielectric: public material {
public:
    // attenuation is always 1, since glass surface do not absorb
    float ref_idx;

    dielectric(float ri): ref_idx(ri) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 outward_norm;
        vec3 reflected = reflect(r_in.direction(), rec.norm);
        float ni_over_nt;
        attenuation = vec3(1.0,1.0,1.0);
        vec3 refracted;
        // add reflectivity
        float reflect_prob;
        float cosine;
        if (dot(r_in.direction(), rec.norm) > 0) {
            // when ray hit from outside
            outward_norm = -rec.norm;
            ni_over_nt = ref_idx;
            cosine = ref_idx*dot(r_in.direction(), rec.norm) / r_in.direction().length();
        } else {
            // when ray hit from inside
            outward_norm = rec.norm;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -ref_idx*dot(r_in.direction(), rec.norm) / r_in.direction().length();
        }

        if (refract(r_in.direction(), outward_norm, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            scattered = ray(rec.p, reflected);
            reflect_prob = 1.0;
        }

        float random = (double)rand()/(RAND_MAX);
        if (random < reflect_prob) {
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }
        return true;
    }
};

#endif //RAYTRACINGONEWEEKEND_MATERIAL_H
