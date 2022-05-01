#include <assert.h>
#include "../include/node.h"

float const default_mat[4] = { 0.25, 0.5, 0.6, 1.0 };

void applyHomothety(SceneTree *node, double hx, double hy, double hz)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_Homothetie3d(hx, hy, hz));
}

void applyTranslate(SceneTree *node, double tx, double ty, double tz)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_Translation3d(tx, ty, tz));
}

static double deg_to_rad(double degree)
{
    return degree * PI / 180.;
}

void applyRotateX(SceneTree *node, double dx)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_RotationX(deg_to_rad(dx)));
}

void applyRotateY(SceneTree *node, double dy)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_RotationY(deg_to_rad(dy)));
}

void applyRotateZ(SceneTree *node, double dz)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_RotationZ(deg_to_rad(dz)));
}

SceneTree createNode()
{
    SceneTree node = (Node *) malloc(sizeof(Node));
    if (node == NULL) { return NULL; }
    memcpy(node->mat, default_mat, 4 * sizeof(float));
    node->Md = g3x_Identity();
    return node;
}

void freeNode(SceneTree *node)
{
    if (*node == NULL) { return; }
    freeNode(&(*node)->next);
    freeNode(&(*node)->down);
    free(*node);
}

SceneTree addChildWithShape(SceneTree *father, Shape *shape)
{
    assert(father != NULL);
    return addChildWithShapeAndColor(father, shape, (*father)->col);
}

SceneTree addChildWithColor(SceneTree *father, G3Xcolor col)
{
    assert(father != NULL);
    return addChildWithShapeAndColor(father, NULL, col);
}

SceneTree addChildWithShapeAndColor(SceneTree *father, Shape *shape, G3Xcolor col)
{
    assert(father != NULL);

    SceneTree child;
    if (NULL == (*father)->down)
    {
        child = (*father)->down = (Node *) malloc(sizeof(Node));
        if (NULL == child) { return NULL; }
    }
    else
    {
        SceneTree tmp = (*father)->down;
        while (NULL != tmp->next) { tmp = tmp->next; }
        child = tmp->next = (Node *) malloc(sizeof(Node));
        if (NULL == child) { return NULL; }
    }

    if (shape != NULL) { child->instance = shape; }
    child->Md           = (*father)->Md;
    child->col          = col;
    child->scale_factor = (*father)->scale_factor;

    memcpy(child->mat, (*father)->mat, sizeof(float) * 4);

    return child;
}


static double max(double a, double b)
{
    return a > b ? a : b;
}

static double getDistVect3D(G3Xvector v1, G3Xvector v2)
{
    return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2) + pow((v2.z - v1.z), 2));
}

void draw_node(Node *node, G3Xvector pos, G3Xhmat mat)
{
    if (node == NULL) { return; }

    g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 0.);
    glPushMatrix();

//    glTranslatef(mat.m[12], mat.m[13], mat.m[14]);
    glMultMatrixd(node->Md.m);

    if (node->instance != NULL)
    {
        double dcam = getDistVect3D((G3Xvector) { node->Md.m[12] + mat.m[12],
                                                  node->Md.m[13] + mat.m[13],
                                                  node->Md.m[14] + mat.m[14] }, pos);

        double scale_balanced = (node->scale_factor.x * mat.m[0] +
                                 node->scale_factor.y * mat.m[5] +
                                 node->scale_factor.z * mat.m[10]) / 3.;

        G3Xvector real_scale = (G3Xvector) { node->scale_factor.x * mat.m[0],
                                             node->scale_factor.y * mat.m[5],
                                             node->scale_factor.z * mat.m[10] };

        double step = 1.; // step smallest value possible
        node->instance->draw_faces(node->instance,
                                   node->scale_factor,
                                   max(step, (step * dcam * 0.125) / scale_balanced));

    }
    glPopMatrix();

    draw_node(node->next, pos, mat);
    draw_node(node->down, pos, mat);
}