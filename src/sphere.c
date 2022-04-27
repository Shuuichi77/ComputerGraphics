#include "../include/sphere.h"

void draw_points_sphere(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}

void draw_faces_sphere(Shape *shape, G3Xvector scale_factor)
{
    g3x_Material(G3Xr, .2, .6, .9, 1, 1);
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * shape->n1 + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * shape->n1 + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, i * shape->n1 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * shape->n1 + j);
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * shape->n1 + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * shape->n1 + j);
        }
    }
    glEnd();
}


Shape init_sphere()
{
    Shape sphere;
    sphere.n1 = NBM;
    sphere.n2 = NBP;

    double       theta         = 2 * PI / sphere.n1;
    double       phi           = PI / (sphere.n2 - 1);
    unsigned int vertex_number = sphere.n1 * sphere.n2;
    sphere.vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    sphere.norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    sphere.draw_points = draw_points_sphere;
    sphere.draw_faces  = draw_faces_sphere;

    for (int i = 0; i < sphere.n1; i++)
    {
        for (int j = 0; j < sphere.n2; j++)
        {
            sphere.norm[i * sphere.n1 + j] = (G3Xpoint) { SPHERE_R * cos(i * theta) * sin(j * phi),
                                                          SPHERE_R * sin(i * theta) * sin(j * phi),
                                                          SPHERE_R * cos(j * phi) };

            sphere.vrtx[i * sphere.n1 + j] = (G3Xpoint) { SPHERE_R * cos(i * theta) * sin(j * phi),
                                                          SPHERE_R * sin(i * theta) * sin(j * phi),
                                                          SPHERE_R * cos(j * phi) };
        }
    }

    return sphere;
}

