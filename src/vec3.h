#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class vec3
{
public:
    vec3()
    {
        e[0] = 0.0f;
        e[1] = 0.0f;
        e[2] = 0.0f;
    }

    vec3(float e1, float e2, float e3)
    {

        e[0] = e1;
        e[1] = e2;
        e[2] = e3;
    }

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline const vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3 &v2)
    {
        e[0] += v2.x();
        e[1] += v2.y();
        e[2] += v2.z();

        return *this;
    }

    inline vec3& operator-=(const vec3 &v2)
    {
        e[0] -= v2.x();
        e[1] -= v2.y();
        e[2] -= v2.z();

        return *this;
    }

    inline vec3& operator*=(const vec3 &v2)
    {
        e[0] *= v2.x();
        e[1] *= v2.y();
        e[2] *= v2.z();

        return *this;
    }

    inline vec3& operator/=(const vec3 &v2)
    {
        e[0] /= v2.x();
        e[1] /= v2.y();
        e[2] /= v2.z();

        return *this;
    }

    inline vec3& operator*=(const float t)
    {
        e[0] += t;
        e[1] += t;
        e[2] += t;

        return *this;
    }

    inline vec3& operator/=(const float t)
    {
        float k = 1.0f / t;

        e[0] += k;
        e[1] += k;
        e[2] += k;

        return *this;
    }

    inline float length() const
    {
        return std::sqrt(e[0]*e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    inline float squaredLenght() const
    {
        return e[0]*e[0] + e[1] * e[1] + e[2] * e[2];
    }





private:
    float e[3];
};



inline std::ostream& operator<<(std::ostream &os, const vec3 &t)
{
    os << t.x() << " " << t.y() << " " << t.z();

    return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

inline vec3 operator*(const vec3 &v1, float t)
{
    return vec3(t * v1.x(), t * v1.y(), t * v1.z());
}

inline vec3 operator*(float t, const vec3 &v1)
{
    return vec3(t * v1.x(), t * v1.y(), t * v1.z());
}


inline float dot(const vec3 &v1, const vec3 &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
    return vec3( (v1.y() * v2.z() - v1.z() * v2.y()),
                 (-(v1.x() * v2.z() - v1.z() * v2.x())),
                 (v1.x() * v2.y() - v1.y() * v2.x()));
}

inline vec3 unitVector(const vec3 &v1)
{
    return 1.0f / (v1.length()) * v1;
}


#endif // VEC3_H
