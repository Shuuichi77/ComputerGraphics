#include "../include/cylinder.h"

static int side_offset;
static int faces_offset;
static int top_face_additional_offset;
static int bottom_face_additional_offset;

static void drawPointsCylinder(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_POINTS);

    for (int i = 0; i < shape->n1 * shape->n2 + shape->n1 * shape->n3 * 2; i += step)
    {
        g3x_Vertex3dv(shape->vrtx[i]);
    }

    glEnd();
}

static void drawFaceCylinder(Shape *shape, int i, double step, int face_additional_offset)
{
    for (int j = 0; j < shape->n3; j += step)
    {
        // Premier triangle (SW -> SE -> NW)
        normalAndVertex3dv(*shape, getSWIndex(step, i, j, shape->n3, faces_offset, face_additional_offset));
        normalAndVertex3dv(*shape, getSEIndex(step, i, j, shape->n1, shape->n3,
                                              faces_offset, face_additional_offset));
        normalAndVertex3dv(*shape, getNWIndex(i, j, faces_offset, face_additional_offset));

        // Second triangle (NW -> SE -> NE)
        drawTriangleNwSeNe(shape, step, i, j, shape->n1, shape->n3,
                           faces_offset, face_additional_offset);
    }
}

static void drawFacesCylinder(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        // Circular sides
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            drawTriangleSwSeNw(shape, step, i, j, shape->n1, shape->n2, side_offset, 0);
            drawTriangleNwSeNe(shape, step, i, j, shape->n1, shape->n2, side_offset, 0);
        }

        // Top face
        drawFaceCylinder(shape, i, step, top_face_additional_offset);

        // Bottom face
        drawFaceCylinder(shape, i, step, bottom_face_additional_offset);
    }
    glEnd();
}

ShapePtr initCylinder()
{
    ShapePtr cylinder = (Shape *) malloc(sizeof(Shape));
    if (cylinder == NULL) { return NULL; }

    cylinder->n1 = NBM;
    cylinder->n2 = NBP;
    cylinder->n3 = NBC;
    unsigned int vertex_number = cylinder->n1 * cylinder->n2 + cylinder->n1 * (cylinder->n3 * 2);
    if (NULL == (cylinder->vrtx = (G3Xpoint *) malloc(sizeof(G3Xpoint) * vertex_number)))
    {
        free(cylinder);
        return NULL;
    }

    if (NULL == (cylinder->norm = (G3Xvector *) malloc(sizeof(G3Xvector) * vertex_number)))
    {
        free(cylinder->vrtx);
        free(cylinder);
        return NULL;
    }

    cylinder->draw_points = drawPointsCylinder;
    cylinder->draw_faces  = drawFacesCylinder;
    double theta = 2 * PI / cylinder->n1;
    double t     = CYLINDER_H / (cylinder->n2 - 1);
    double r     = CYLINDER_R / (cylinder->n3 - 1);
    side_offset                   = (cylinder->n1 + cylinder->n3 * 2);
    faces_offset                  = (cylinder->n1 + cylinder->n2);
    top_face_additional_offset    = cylinder->n2;
    bottom_face_additional_offset = cylinder->n2 + cylinder->n3;

    for (int i = 0; i < cylinder->n1; i++)
    {
        // Circular sides
        for (int j = 0; j < cylinder->n2; j++)
        {
            cylinder->norm[i * side_offset + j] = (G3Xvector) { cos(i * theta),
                                                                sin(i * theta),
                                                                0 };

            cylinder->vrtx[i * side_offset + j] = (G3Xpoint) { CYLINDER_R * cos(i * theta),
                                                               CYLINDER_R * sin(i * theta),
                                                               (j * t) - (CYLINDER_H / 2.) };
        }

        // Top face
        for (int j = 0; j < cylinder->n3; j++)
        {
            cylinder->norm[i * faces_offset + top_face_additional_offset + j] =
                    (G3Xvector) { 0, 0, 1 };

            cylinder->vrtx[i * faces_offset + top_face_additional_offset + j] =
                    (G3Xpoint) { (j * r) * cos(i * theta),
                                 (j * r) * sin(i * theta),
                                 CYLINDER_H / 2. };
        }

        // Bottom face
        for (int j = 0; j < cylinder->n3; j++)
        {
            cylinder->norm[i * faces_offset + bottom_face_additional_offset + j] =
                    (G3Xvector) { 0, 0, -1 };

            cylinder->vrtx[i * faces_offset + bottom_face_additional_offset + j] =
                    (G3Xpoint) { (j * r) * cos(i * theta),
                                 (j * r) * sin(i * theta),
                                 -CYLINDER_H / 2. };
        }
    }

    return cylinder;
}