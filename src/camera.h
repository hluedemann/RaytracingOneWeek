#ifndef CAMER_H
#define CAMER_H

#include "ray.h"
#include "material.h"


class Camera
{
public:
    Camera(vec3 lookFrom, vec3 lookAt, vec3 vup, float vfov, float aspect, float aperature, float focusDist)
    {
        m_lensRadius = aperature / 2;
        float theta = vfov * M_PI / 180.0f;
        float halfHeight = std::tan(theta / 2.0f);
        float halfWidth = aspect * halfHeight;

        m_w = unitVector(lookFrom - lookAt);
        m_u = unitVector(cross(vup, m_w));
        m_v = cross(m_w, m_u);

        m_origin = lookFrom;
        m_loverLeft = m_origin - halfWidth * focusDist * m_u - halfHeight * focusDist * m_v - focusDist * m_w;
        m_horizontal = 2.0f * halfWidth * focusDist * m_u;
        m_vertical = 2.0f * halfHeight * focusDist * m_v;
    }

    inline Ray getRay(float s, float t) const
    {
        vec3 rd = m_lensRadius * getRandomInUnitSphere();
        vec3 offset =  m_u * rd.x() + m_u * rd.y();

        return Ray(m_origin + offset, m_loverLeft + s * m_horizontal + t * m_vertical - m_origin - offset);
    }

private:
    vec3 m_origin;
    vec3 m_loverLeft;
    vec3 m_horizontal;
    vec3 m_vertical;

    vec3 m_w, m_u, m_v;
    float m_lensRadius;
};


#endif // CAMER_H
