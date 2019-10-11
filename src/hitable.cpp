#include "hitable.h"




bool Sphere::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const
{
    vec3 oc = ray.getOrigin() - m_center;
    float a = dot(ray.getDirection(), ray.getDirection());
    float b = dot(oc, ray.getDirection());
    float c = dot(oc, oc) - m_radius * m_radius;
    float discriminant = b * b - a * c;


    if(discriminant > 0)
    {
        record.materialPtr = m_material;

        float temp = (-b - std::sqrt(discriminant)) / a;

        if(temp < tMax && temp >tMin)
        {
            record.t = temp;
            record.p = ray.getPointAtParameter(temp);
            record.normal = (record.p - m_center) / m_radius;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;

        if(temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = ray.getPointAtParameter(temp);
            record.normal = (record.p - m_center) / m_radius;
            return true;
        }
    }
    return false;
}

vec3 Sphere::center() const
{
    return m_center;
}

void Sphere::setCenter(const vec3 &center)
{
    m_center = center;
}

float Sphere::radius() const
{
    return m_radius;
}

void Sphere::setRadius(float radius)
{
    m_radius = radius;
}


/////////////// HitableList ///////////////////////


bool HitableList::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const
{
    HitRecord tempRecord;
    bool hitAnything = false;

    double closestSoFar = tMax;

    for(int i = 0; i < m_count; i++)
    {
        if(m_list[i]->hit(ray, tMin, closestSoFar, tempRecord))
        {
            hitAnything = true;
            closestSoFar = tempRecord.t;
            record = tempRecord;
        }
    }
    return hitAnything;
}
