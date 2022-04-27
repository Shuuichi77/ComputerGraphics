#include <g3x.h>
#include "../include/shape.h"
#include "../include/sphere.h"
#include "../include/utils.h"

#define NBM 100                   // Nombre de méridiens (lignes verticales)
#define NBP 100                   // Nombre de parallèles (lignes horizontales)
static double SPHERE_R = 1.0;            // Rayon de la sphère.

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
    for (int i = 0; i < NBM; i += step)
    {
        for (int j = 0; j < NBP - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * NBM + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * NBM + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, i * NBM + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * NBM + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * NBM + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * NBM + j);
        }
    }
    glEnd();
}

Shape init_sphere()
{
    Shape        sphere;
    double       theta         = 2 * PI / NBM;
    double       phi           = PI / (NBP - 1);
    unsigned int vertex_number = NBM * NBP;
    sphere.vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    sphere.norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    sphere.draw_points = draw_points_sphere;
    sphere.draw_faces  = draw_faces_sphere;

    for (int i = 0; i < NBM; i++)
    {
        for (int j = 0; j < NBP; j++)
        {
            sphere.norm[i * NBM + j] = (G3Xpoint) { SPHERE_R * cos(i * theta) * sin(j * phi),
                                                    SPHERE_R * sin(i * theta) * sin(j * phi),
                                                    SPHERE_R * cos(j * phi) };

            sphere.vrtx[i * NBM + j] = (G3Xpoint) { SPHERE_R * cos(i * theta) * sin(j * phi),
                                                    SPHERE_R * sin(i * theta) * sin(j * phi),
                                                    SPHERE_R * cos(j * phi) };
        }
    }

    return sphere;
}

void draw_sphere(G3Xvector scale_factor)
{
    Shape sphere = init_sphere();
    sphere.draw_faces(&sphere, scale_factor);
}

