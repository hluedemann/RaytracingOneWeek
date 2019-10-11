
#include <stdexcept>
#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "camera.h"
#include "material.h"




vec3 getColor(const Ray &ray, Hitable *world, int depth)
{
    HitRecord record;
    if(world->hit(ray, 0.001f, MAXFLOAT, record))
    {
        Ray scattered;
        vec3 attenuation;

        if(depth < 50 && record.materialPtr->scatter(ray, record, attenuation, scattered))
        {
            return attenuation * getColor(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0.0f, 0.0f, 0.0f);
        }
    }
    else
    {
        vec3 unitDirection = unitVector(ray.getDirection());
        float t = 0.5f * (unitDirection.y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}



HitableList* randomScene()
{
    int n = 500;
    Hitable **list = new Hitable*[n+1];
    list[0] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));

    int i = 1;
    for(int a = -11; a < 11; a++)
    {
        for(int b = -11; b < 11; b++)
        {
            float chooseMat = drand48();
            vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
            if((center -vec3(4, 0.2, 0)).length() > 0.9)
            {
                if(chooseMat < 0.8)
                {
                    list[i++] = new Sphere(center, 0.2, new Lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                else if(chooseMat < 0.95)
                {
                    list[i++] = new Sphere(center, 0.2, new Metal(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48()));
                }
                else
                {
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(vec3(0,1,0), 1.0, new Dielectric(1.5f));
    list[i++] = new Sphere(vec3(-4, 1, 0), 1.0f, new Lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(vec3(4, 1, 0), 1.0f, new Metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new HitableList(list, i);
}


int main()
{

    int nx = 2400;
    int ny = 1200;
    int ns = 10;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    Hitable *list[4];
    list[0] = new Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(vec3(0.8f, 0.3f, 0.3f)));
    list[1] = new Sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(vec3(0.8f, 0.8f, 0.0f)));
    list[2] = new Sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(vec3(0.8f, 0.6f, 0.2f), 0.3));
    list[3] = new Sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5));
    HitableList *world = randomScene();

    vec3 lookFrom(13,2,3);
    vec3 lookAt(0,0,0);
    float distToFocus = 10.0;
    float aperture = 0.1;

    Camera camerea(lookFrom, lookAt, vec3(0,1,0), 20.0f, float(nx) / float(ny), aperture, distToFocus);

    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 color(0.0f, 0.0f, 0.0f);

            for(int s = 0; s < ns; s++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);


                Ray ray = camerea.getRay(u, v);
                vec3 p = ray.getPointAtParameter(2.0f);
                color += getColor(ray, world, 0);
            }

            color /= float(ns);

            color = vec3(std::sqrt(color[0]), std::sqrt(color[1]), std::sqrt(color[2]));

            int ir = int(255.99f * color[0]);
            int ig = int(255.99f * color[1]);
            int ib = int(255.99f * color[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }


    return 0;
}
