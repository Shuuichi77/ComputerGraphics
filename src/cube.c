#include <g3x.h>
#include "../include/shape.h"
#include "../include/cube.h"
#include "../include/utils.h"

#define NBM 100                   // Nombre de méridiens (lignes verticales)
#define NBP 100                   // Nombre de parallèles (lignes horizontales)
static double CUBE_W = 2.0;       // Côté du cube.

void draw_points_cube(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}

void draw_faces_cube(Shape *shape, G3Xvector scale_factor)
{
    g3x_Material(G3Xr, .2, .6, .9, 1, 1);
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < NBM; i += step)
    {
        g3x_Material(G3Xr, .2, .6, .9, 1, 1);

        // 1ère face
        for (int j = 0; j < NBP; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 + min(j + step, NBP));
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 +
                            min(j + step, NBP));
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 + j);
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 +
                            min(j + step, NBP));
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 + j);
        }

        // 2ème face
        for (int j = 0; j < NBP; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 + min(j + step, NBP));
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 + j);
        }

        // 3ème face
        for (int j = 0; j < NBP; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 + min(j + step, NBP));
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 + j);
        }

        // 4ème face
        for (int j = 0; j < NBP; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 + min(j + step, NBP));
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 + j);
        }

        // 5ème face
        for (int j = 0; j < NBP; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 + min(j + step, NBP));
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 + j);
        }

        // 6ème face
        for (int j = 0; j < NBP; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 + min(j + step, NBP));
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 +
                                    min(j + step, NBP));
            NormalVertex3dv(*shape,
                            (min(i + step, NBM) % (NBM + 1)) * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 + j);
        }
    }
    glEnd();
}

Shape init_cube()
{
    Shape        cube;
    unsigned int vertex_number = 6 * (NBM + 1) * (NBP + 1);
    cube.vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cube.norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cube.draw_points = draw_points_cube;
    cube.draw_faces  = draw_faces_cube;

    for (int i = 0; i <= NBM; i++)
    {
        // 1ère face
        for (int j = 0; j <= NBP; j++)
        {
            cube.norm[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 + j] = (G3Xpoint) { 0,
                                                                                          (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP };

            cube.vrtx[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 0 + j] = (G3Xpoint) { 0,
                                                                                          (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP };
        }

        // 2ème face
        for (int j = 0; j <= NBP; j++)
        {
            cube.norm[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          CUBE_W,
                                                                                          (double) (j * 2) / NBP };

            cube.vrtx[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 3 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          CUBE_W,
                                                                                          (double) (j * 2) / NBP };
        }

        // 3ème face
        for (int j = 0; j <= NBP; j++)
        {
            cube.norm[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          0,
                                                                                          (double) (j * 2) / NBP };

            cube.vrtx[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 2 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          0,
                                                                                          (double) (j * 2) / NBP };
        }

        // 4ème face
        for (int j = 0; j <= NBP; j++)
        {
            cube.norm[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 + j] = (G3Xpoint) { CUBE_W,
                                                                                          (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP };

            cube.vrtx[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 1 + j] = (G3Xpoint) { CUBE_W,
                                                                                          (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP };
        }

        // 5ème face
        for (int j = 0; j <= NBP; j++)
        {
            cube.norm[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP,
                                                                                          0 };

            cube.vrtx[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 4 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP,
                                                                                          0 };
        }

        // 6ème face
        for (int j = 0; j <= NBP; j++)
        {
            cube.norm[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP,
                                                                                          CUBE_W };
            cube.vrtx[i * ((NBM + 1) + (NBP + 1) * 5) + (NBP + 1) * 5 + j] = (G3Xpoint) { (double) (i * 2) / NBM,
                                                                                          (double) (j * 2) / NBP,
                                                                                          CUBE_W };
        }
    }

    return cube;
}

void draw_cube(G3Xvector scale_factor)
{
    Shape cube = init_cube();
    cube.draw_faces(&cube, scale_factor);
}

