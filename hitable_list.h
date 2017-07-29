//
// Created by Jinglei Yang on 7/29/2017.
//

#ifndef RAYTRACINGONEWEEKEND_HITABLE_LIST_H
#define RAYTRACINGONEWEEKEND_HITABLE_LIST_H

#include "hitable.h"
class hitable_list : public hitable {
public:
    hitable** list;
    int list_size;

    // constructor
    hitable_list() {}
    hitable_list(hitable **l, int n) {list = l; list_size = n;}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest = t_max;
    for (int i = 0; i < list_size; ++i) {
        if (list[i]->hit(r, t_min, closest, temp_rec)){
            hit_anything = true;
            closest = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //RAYTRACINGONEWEEKEND_HITABLE_LIST_H
