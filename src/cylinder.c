#include <g3x.h>
#include "../include/shape.h"
#include "../include/cylinder.h"
#include "../include/utils.h"

#define NBM 100                   // Nombre de méridiens (lignes verticales)
#define NBP 100                   // Nombre de parallèles (lignes horizontales)
#define NBC 50                    // Nombre de cercles sur les bases
static double CYLINDER_H = 2;              // Hauteur du cylindre
static double CYLINDER_R = 1;             // Rayon du cylindre

void draw_points_cylinder(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}

void draw_faces_cylinder(Shape *shape, G3Xvector scale_factor)
{
    g3x_Material(G3Xr, .2, .6, .9, 1, 1);
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < NBM; i += step)
    {
        for (int j = 0; j < NBP - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (NBM + NBC * 2) + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * (NBM + NBC * 2) + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, i * (NBM + NBC * 2) + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (NBM + NBC * 2) + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * (NBM + NBC * 2) + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * (NBM + NBC * 2) + j);
        }

        for (int k = 0; k < NBC; k += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (NBM + NBP) + NBP + min(k + step, NBC - 1));
            NormalVertex3dv(*shape, min(i + step, NBM) % NBM * (NBM + NBP) + NBP + min(k + step, NBC - 1));
            NormalVertex3dv(*shape, i * (NBM + NBP) + NBP + k);


            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (NBM + NBP) + NBP + k);
            NormalVertex3dv(*shape, min(i + step, NBM) % NBM * (NBM + NBP) + NBP + min(k + step, NBC - 1));
            NormalVertex3dv(*shape, min(i + step, NBM) % NBM * (NBM + NBP) + NBP + k);
        }

        for (int l = 0; l < NBC; l += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (NBM + NBP) + NBP + NBC + min(l + step, NBC - 1));
            NormalVertex3dv(*shape, min(i + step, NBM) % NBM * (NBM + NBP) + NBP + NBC + min(l + step, NBC - 1));
            NormalVertex3dv(*shape, i * (NBM + NBP) + NBP + NBC + l);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (NBM + NBP) + NBP + NBC + l);
            NormalVertex3dv(*shape, min(i + step, NBM) % NBM * (NBM + NBP) + NBP + NBC + min(l + step, NBC - 1));
            NormalVertex3dv(*shape, min(i + step, NBM) % NBM * (NBM + NBP) + NBP + NBC + l);
        }
    }
    glEnd();
}

Shape init_cylinder()
{
    Shape  cylinder;
    double theta = 2 * PI / NBM;
    double t     = CYLINDER_H / (NBP - 1);
    double r     = CYLINDER_R / (NBC - 1);

    unsigned int vertex_number = NBM * NBP + NBM * (NBC * 2);

    cylinder.vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cylinder.norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cylinder.draw_points = draw_points_cylinder;
    cylinder.draw_faces  = draw_faces_cylinder;

    for (int i = 0; i < NBM; i++)
    {
        for (int j = 0; j < NBP; j++)
        {
            cylinder.norm[i * (NBM + NBC * 2) + j] = (G3Xpoint) { CYLINDER_R * cos(i * theta),
                                                                  CYLINDER_R * sin(i * theta),
                                                                  (j * t) - (CYLINDER_H / 2.) };

            cylinder.vrtx[i * (NBM + NBC * 2) + j] = (G3Xpoint) { CYLINDER_R * cos(i * theta),
                                                                  CYLINDER_R * sin(i * theta),
                                                                  (j * t) - (CYLINDER_H / 2.) };
        }
        for (int k = 0; k < NBC; k++)
        {
            cylinder.norm[i * (NBM + NBP) + NBP + k] = (G3Xpoint) { (k * r) * cos(i * theta),
                                                                    (k * r) * sin(i * theta),
                                                                    CYLINDER_H / 2. };

            cylinder.vrtx[i * (NBM + NBP) + NBP + k] = (G3Xpoint) { (k * r) * cos(i * theta),
                                                                    (k * r) * sin(i * theta),
                                                                    CYLINDER_H / 2. };
        }

        for (int l = 0; l < NBC; l++)
        {
            cylinder.norm[i * (NBM + NBP) + NBP + NBC + l] = (G3Xpoint) { (l * r) * cos(i * theta),
                                                                          (l * r) * sin(i * theta),
                                                                          -CYLINDER_H / 2. };

            cylinder.vrtx[i * (NBM + NBP) + NBP + NBC + l] = (G3Xpoint) { (l * r) * cos(i * theta),
                                                                          (l * r) * sin(i * theta),
                                                                          -CYLINDER_H / 2. };
        }
    }

    return cylinder;
}

void draw_cylinder(G3Xvector scale_factor)
{
    Shape cylinder = init_cylinder();
    cylinder.draw_faces(&cylinder, scale_factor);
}

