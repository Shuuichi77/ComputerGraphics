#include "../include/cube.h"

static int offset;
static int faces_additional_offset[6];

static void drawPointsCube(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_POINTS);

    for (int i = 0; i < 6 * ((shape)->n1 + 1) * ((shape)->n1 + 1); i += step)
    {
        g3x_Vertex3dv(shape->vrtx[i]);
    }

    glEnd();
}

static void drawFaceCube(Shape *shape, int i, double step, int face_additional_offset)
{
    for (int j = 0; j < shape->n1; j += step)
    {
        // First triangle (SW -> SE -> NW)
        g3x_Vertex3dv(shape->vrtx[i * offset + face_additional_offset + min(j + step, shape->n1)]);
        g3x_Vertex3dv(shape->vrtx[(min(i + step, shape->n1) % (shape->n1 + 1)) * offset +
                                  face_additional_offset + min(j + step, shape->n1)]);
        g3x_Vertex3dv(shape->vrtx[i * offset + face_additional_offset + j]);

        // Second triangle (NW -> SE -> NE)
        g3x_Vertex3dv(shape->vrtx[i * offset + face_additional_offset + j]);
        g3x_Vertex3dv(shape->vrtx[(min(i + step, shape->n1) % (shape->n1 + 1)) * offset +
                                  face_additional_offset + min(j + step, shape->n1)]);
        g3x_Vertex3dv(shape->vrtx[(min(i + step, shape->n1) % (shape->n1 + 1)) * offset +
                                  face_additional_offset + j]);
    }
}

static void drawFacesCube(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < shape->n1; i += step)
    {
        for (int j = 0; j < 6; j++)
        {
            g3x_Normal3dv(shape->norm[j]);
            drawFaceCube(shape, i, step, faces_additional_offset[j]);
        }
    }
    glEnd();
}

ShapePtr initCube()
{
    ShapePtr cube = (Shape *) malloc(sizeof(Shape));
    if (cube == NULL) { return NULL; }
    cube->n1 = NBM;
    unsigned int vertex_number = 6 * (cube->n1 + 1) * (cube->n1 + 1);
    if (NULL == (cube->vrtx = (G3Xpoint *) malloc(sizeof(G3Xpoint) * vertex_number)))
    {
        free(cube);
        return NULL;
    }

    if (NULL == (cube->norm = (G3Xvector *) malloc(sizeof(G3Xvector) * 6)))
    {
        free(cube->vrtx);
        free(cube);
        return NULL;
    }

    cube->draw_faces  = drawFacesCube;
    cube->draw_points = drawPointsCube;
    // Every vertex on the same face have the same normal, so unlike other shapes, we'll use an array of 6 elements :
    cube->norm[0] = (G3Xvector) { -1, 0, 0 };
    cube->norm[1] = (G3Xvector) { 1, 0, 0 };
    cube->norm[2] = (G3Xvector) { 0, -1, 0 };
    cube->norm[3] = (G3Xvector) { 0, 1, 0 };
    cube->norm[4] = (G3Xvector) { 0, 0, -1 };
    cube->norm[5] = (G3Xvector) { 0, 0, 1 };
    offset = (cube->n1 + 1) + (cube->n1 + 1) * 5;

    for (int i = 0; i < 6; i++)
    {
        faces_additional_offset[i] = (cube->n1 + 1) * i;
    }

    for (int i = 0; i <= cube->n1; i++)
    {
        // 1ère face
        for (int j = 0; j <= cube->n1; j++)
        {
            cube->vrtx[i * offset + faces_additional_offset[0] + j] = (G3Xpoint) { 0,
                                                                                   (double) (i * 2) / cube->n1,
                                                                                   (double) (j * 2) / cube->n1 };
        }

        // 2ème face
        for (int j = 0; j <= cube->n1; j++)
        {
            cube->vrtx[i * offset + faces_additional_offset[1] + j] = (G3Xpoint) { CUBE_W,
                                                                                   (double) (i * 2) / cube->n1,
                                                                                   (double) (j * 2) / cube->n1 };
        }

        // 3ème face
        for (int j = 0; j <= cube->n1; j++)
        {
            cube->vrtx[i * offset + faces_additional_offset[2] + j] = (G3Xpoint) { (double) (i * 2) / cube->n1,
                                                                                   0,
                                                                                   (double) (j * 2) / cube->n1 };
        }

        // 4ème face
        for (int j = 0; j <= cube->n1; j++)
        {
            cube->vrtx[i * offset + faces_additional_offset[3] + j] = (G3Xpoint) { (double) (i * 2) / cube->n1,
                                                                                   CUBE_W,
                                                                                   (double) (j * 2) / cube->n1 };
        }


        // 5ème face
        for (int j = 0; j <= cube->n1; j++)
        {
            cube->vrtx[i * offset + faces_additional_offset[4] + j] = (G3Xpoint) { (double) (i * 2) / cube->n1,
                                                                                   (double) (j * 2) / cube->n1,
                                                                                   0 };
        }

        // 6ème face
        for (int j = 0; j <= cube->n1; j++)
        {
            cube->vrtx[i * offset + faces_additional_offset[5] + j] = (G3Xpoint) { (double) (i * 2) / cube->n1,
                                                                                   (double) (j * 2) / cube->n1,
                                                                                   CUBE_W };
        }
    }

    return cube;
}
