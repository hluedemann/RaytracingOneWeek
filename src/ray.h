#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
    Ray() = default;
    Ray(const vec3 &origin, const vec3 &direction)
        : m_origin(origin), m_direction(direction) {}

    inline vec3 getOrigin() const { return m_origin; }
    inline vec3 getDirection() const { return m_direction; }

    inline vec3 getPointAtParameter(float t) const { return m_origin + t * m_direction; }

private:
    vec3 m_origin;
    vec3 m_direction;
};

#endif // RAY_H
