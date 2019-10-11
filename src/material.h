#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"


vec3 getRandomInUnitSphere()
{
    vec3 p;

    do
    {
        p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1.0f, 1.0f, 1.0f);
    }
    while(p.squaredLenght() >= 1.0f);

    return p;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2.0f * dot(v, n) * n;
}

bool refract(const vec3 &v, const vec3 &n, float niOverNt, vec3 &refracted)
{
    vec3 uv = unitVector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0f - niOverNt * niOverNt * (1 - dt * dt);

    if(discriminant > 0)
    {
        refracted = niOverNt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}



class Material
{
public:
    virtual bool scatter(const Ray &rayIn, const HitRecord &record, vec3 &attenuation, Ray &scattered) const = 0;
};


class Lambertian : public Material
{
public:
    Lambertian(const vec3 &albedo) : m_albedo(albedo){}

    virtual bool scatter(const Ray &rayIn, const HitRecord &record, vec3 &attenuation, Ray &scattered) const override
    {
        vec3 target = record.p + record.normal + getRandomInUnitSphere();
        scattered = Ray(record.p, target - record.p);
        attenuation = m_albedo;

        return true;
    }

private:
    vec3 m_albedo;
};



class Metal : public Material
{
public:
    Metal(const vec3 &albedo, float f) : m_albedo(albedo), m_fuzz(f < 1 ? f : 1){}

    virtual bool scatter(const Ray &rayIn, const HitRecord &record, vec3 &attenuation, Ray &scattered) const override
    {
        vec3 reflected = reflect(unitVector(rayIn.getDirection()), record.normal);
        scattered = Ray(record.p, reflected + m_fuzz * getRandomInUnitSphere());
        attenuation = m_albedo;

        return (dot(scattered.getDirection(), record.normal) > 0);
    }

private:
    vec3 m_albedo;
    float m_fuzz;
};



class Dielectric : public Material
{
public:
    Dielectric(float reflectionIndex) : m_reflectionIndex(reflectionIndex){}

    virtual bool scatter(const Ray &rayIn, const HitRecord &record, vec3 &attenuation, Ray &scattered) const override
    {
        vec3 outwardNormal;
        vec3 reflected = reflect(rayIn.getDirection(), record.normal);
        float niOverNt;
        attenuation = vec3(1.0f, 1.0f, 1.0f);
        vec3 refracted;

        if(dot(rayIn.getDirection(), record.normal) > 0)
        {
            outwardNormal = -record.normal;
            niOverNt = m_reflectionIndex;
        }
        else
        {
            outwardNormal = record.normal;
            niOverNt = 1.0f / m_reflectionIndex;
        }
        if(refract(rayIn.getDirection(), outwardNormal, niOverNt, refracted))
        {
            scattered = Ray(record.p, refracted);
        }
        else
        {
            scattered = Ray(record.p, reflected);
            return false;
        }

        return true;
    }

private:
    float m_reflectionIndex;
};

#endif // MATERIAL_H
