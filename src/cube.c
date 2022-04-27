#include "../include/cube.h"

void draw_points_cube(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}


void draw_faces_cube(Shape *shape, G3Xvector scale_factor)
{
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        // 1ère face
        for (int j = 0; j < shape->n2; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 0 +
                                    min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 0 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 0 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 0 + j);
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 0 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 0 + j);
        }

        // 2ème face
        for (int j = 0; j < shape->n2; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 1 +
                                    min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 1 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 1 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 1 + j);
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 1 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 1 + j);
        }

        // 3ème face
        for (int j = 0; j < shape->n2; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 2 +
                                    min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 2 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 2 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 2 + j);
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 2 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 2 + j);
        }

        // 4ème face
        for (int j = 0; j < shape->n2; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 3 +
                                    min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 3 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 3 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 3 + j);
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 3 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 3 + j);
        }

        // 5ème face
        for (int j = 0; j < shape->n2; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 4 +
                                    min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 4 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 4 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 4 + j);
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 4 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 4 + j);
        }

        // 6ème face
        for (int j = 0; j < shape->n2; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 5 +
                                    min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 5 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 5 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * ((shape->n1 + 1) + (shape->n2 + 1) * 5) + (shape->n2 + 1) * 5 + j);
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 5 +
                            min(j + step, shape->n2));
            NormalVertex3dv(*shape,
                            (min(i + step, shape->n1) % (shape->n1 + 1)) * ((shape->n1 + 1) + (shape->n2 + 1) * 5) +
                            (shape->n2 + 1) * 5 + j);
        }
    }
    glEnd();
}

Shape init_cube()
{
    Shape cube;
    cube.n1 = NBM / 2;
    cube.n2 = NBP / 2;

    unsigned int vertex_number = 6 * (cube.n1 + 1) * (cube.n2 + 1);
    cube.vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cube.norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cube.draw_points = draw_points_cube;
    cube.draw_faces  = draw_faces_cube;


    for (int i = 0; i <= cube.n1; i++)
    {
        // 1ère face
        for (int j = 0; j <= cube.n2; j++)
        {
            cube.norm[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 0 + j] = (G3Xpoint) { 0,
                                                                                                      (double) (i * 2) /
                                                                                                      cube.n1,
                                                                                                      (double) (j * 2) /
                                                                                                      cube.n2 };

            cube.vrtx[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 0 + j] = (G3Xpoint) { 0,
                                                                                                      (double) (i * 2) /
                                                                                                      cube.n1,
                                                                                                      (double) (j * 2) /
                                                                                                      cube.n2 };
        }

        // 2ème face
        for (int j = 0; j <= cube.n2; j++)
        {
            cube.norm[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 3 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    CUBE_W,
                    (double) (j * 2) / cube.n2 };

            cube.vrtx[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 3 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    CUBE_W,
                    (double) (j * 2) / cube.n2 };
        }

        // 3ème face
        for (int j = 0; j <= cube.n2; j++)
        {
            cube.norm[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 2 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    0,
                    (double) (j * 2) / cube.n2 };

            cube.vrtx[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 2 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    0,
                    (double) (j * 2) / cube.n2 };
        }

        // 4ème face
        for (int j = 0; j <= cube.n2; j++)
        {
            cube.norm[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 1 + j] = (G3Xpoint) { CUBE_W,
                                                                                                      (double) (i * 2) /
                                                                                                      cube.n1,
                                                                                                      (double) (j * 2) /
                                                                                                      cube.n2 };

            cube.vrtx[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 1 + j] = (G3Xpoint) { CUBE_W,
                                                                                                      (double) (i * 2) /
                                                                                                      cube.n1,
                                                                                                      (double) (j * 2) /
                                                                                                      cube.n2 };
        }

        // 5ème face
        for (int j = 0; j <= cube.n2; j++)
        {
            cube.norm[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 4 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    (double) (j * 2) / cube.n2,
                    0 };

            cube.vrtx[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 4 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    (double) (j * 2) / cube.n2,
                    0 };
        }

        // 6ème face
        for (int j = 0; j <= cube.n2; j++)
        {
            cube.norm[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 5 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    (double) (j * 2) / cube.n2,
                    CUBE_W };
            cube.vrtx[i * ((cube.n1 + 1) + (cube.n2 + 1) * 5) + (cube.n2 + 1) * 5 + j] = (G3Xpoint) {
                    (double) (i * 2) / cube.n1,
                    (double) (j * 2) / cube.n2,
                    CUBE_W };
        }
    }

    return cube;
}
