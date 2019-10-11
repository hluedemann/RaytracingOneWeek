#ifndef HITABLE_H
#define HITABLE_H


#include "ray.h"
#include "vec3.h"


class Material;

struct HitRecord
{
    float t;
    vec3 p;
    vec3 normal;
    Material *materialPtr;
};

class Hitable
{
public:
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const = 0;
};



class Sphere : public Hitable
{
public:
    Sphere() = default;
    Sphere(vec3 center, float r, Material *material) : m_center(center), m_radius(r), m_material(material)
    {}

    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

    vec3 center() const;
    void setCenter(const vec3 &center);

    float radius() const;
    void setRadius(float radius);

private:
    vec3 m_center;
    float m_radius;
    Material *m_material;

};

class HitableList : public Hitable
{
public:
    HitableList() = default;
    HitableList(Hitable **list, int count) : m_list(list), m_count(count)
    {}

    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

private:
    Hitable **m_list;
    int m_count;
};

#endif // HITABLE_H








