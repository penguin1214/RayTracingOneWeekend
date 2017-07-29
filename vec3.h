//
// Created by Jinglei Yang on 7/28/2017.
//

#ifndef RAYTRACINGONEWEEKEND_VEC3_H
#define RAYTRACINGONEWEEKEND_VEC3_H

#include <math.h>
#include <iostream>
#include <stdlib.h>

/*
 * @member: x, y, z => e[3] | x(), y(), z()
 * @methods: uniform(), length()
 * @operator reloading: vec3(+)vec3, vec3(-)vec3, scalar(*)vec3, vec3(*)scalar,
 *                      vec3(*)vec3, -(vec3)
 */
class vec3 {

public:
    // constructor
    vec3(){}

    vec3(float e0, float e1, float e2) {
        e[0] = e0; e[1] = e1; e[2] = e2;
    }

    vec3(float f) {
        e[0] = f; e[1] = f; e[2] = f;
    }

    inline float x() const { return e[0];}
    inline float y() const { return e[1];}
    inline float z() const { return e[2];}

    // member
    float e[3];

    // operator reloading
    inline vec3&operator += (const vec3& v);
    inline vec3&operator -= (const vec3& v);
    inline vec3&operator *= (const vec3& v);
    inline vec3&operator /= (const vec3& v);

    inline vec3&operator *= (const float f);
    inline vec3&operator /= (const float f);


    inline float length() const{
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

};


inline vec3&vec3::operator += (const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3&vec3::operator-=(const vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline vec3&vec3::operator*=(const vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3&vec3::operator/=(const vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3&vec3::operator*=(const float f) {
    e[0] *= f;
    e[1] *= f;
    e[2] *= f;
    return *this;
}

inline vec3&vec3::operator/=(const float f) {
    e[0] /= f;
    e[1] /= f;
    e[2] /= f;
    return *this;
}

// non-member function

inline vec3 operator+(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1], v1.e[2]+v2.e[2]);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1], v1.e[2]-v2.e[2]);
}


inline vec3 operator/(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[0]/v2.e[0], v1.e[1]/v2.e[1], v1.e[2]/v2.e[2]);
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[0]*v2.e[0], v1.e[1]*v2.e[1], v1.e[2]*v2.e[2]);
}

inline vec3 operator*(const vec3& v, float f) {
    return vec3(v.e[0]*f, v.e[1]*f, v.e[2]*f);
}

inline vec3 operator/(const vec3& v, float f) {
    return vec3(v.e[0]/f, v.e[1]/f, v.e[2]/f);
}

// dot product
inline float dot(const vec3& v1, const vec3& v2) {
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

// cross product
inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1],
    -(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0]),
    v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]);
}

// unit vector
// remove a member function uniform(), since when a const vec3 object call uniform(),
// the compiler would throw an error, because if uniform() is a non-const function,
// calling a non-const function DO NOT guarantee the const object's constness.
inline vec3 unit(const vec3&v) {
    return vec3(v.e[0]/v.length(), v.e[1]/v.length(), v.e[2]/v.length());
}

inline std::istream& operator>>(std::istream& is, vec3& v) {
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, vec3& v) {
    os << v.e[0] << " " << v.e[1] << " " << v.e[2];
    return os;
}

#endif //RAYTRACINGONEWEEKEND_VEC3_H
