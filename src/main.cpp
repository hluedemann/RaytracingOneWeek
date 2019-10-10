
#include <stdexcept>
#include <iostream>

#include "vec3.h"
#include "ray.h"


vec3 getColor(const Ray &ray)
{
    vec3 unitDirection = unitVector(ray.getDirection());
    float t = 0.5f * (unitDirection.y() + 1.0f);

    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}


int main()
{

    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f, 0.0f, 0.0f);

    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
            vec3 color = getColor(ray);

            int ir = int(255.99f * color[0]);
            int ig = int(255.99f * color[1]);
            int ib = int(255.99f * color[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }


    return 0;
}
