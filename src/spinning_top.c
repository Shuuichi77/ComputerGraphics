#include "../include/spinning_top.h"

int init_stick(SceneTree *spinning_top, Shape *cylinder)
{
    if (!add_child(spinning_top)) { return 0; }
    (*spinning_top)->down->instance     = cylinder;
    (*spinning_top)->down->col          = light_grey;
    (*spinning_top)->down->scale_factor = (G3Xvector) { STICK_X, STICK_Y, STICK_Z };
    translate(&(*spinning_top)->down, 0, 0, STICK_Z);
    return 1;
}

int init_globe(SceneTree *spinning_top, SceneTree *next, Shape *sphere)
{
    if (!add_next(next, spinning_top)) { return 0; }
    (*next)->next->instance     = sphere;
    (*next)->next->col          = light_grey;
    (*next)->next->scale_factor = (G3Xvector) { GLOBE_X, GLOBE_Y, GLOBE_Z };
    translate(&(*next)->next, 0, 0, bottom_stick_height);

    return 1;
}

int init_ring(SceneTree *spinning_top, SceneTree *next, Shape *torus)
{
    if (!add_next(next, spinning_top)) { return 0; }
    (*next)->next->instance     = torus;
    (*next)->next->col          = light_grey;
    (*next)->next->scale_factor = (G3Xvector) { TORUS_X, TORUS_Y, TORUS_Z };
    translate(&(*next)->next, 0, 0, bottom_stick_height);

    return 1;
}

int init_spinning_top(SceneTree *spinning_top, Shape *cylinder, Shape *sphere, Shape *torus)
{
    if (((*spinning_top) = (Node *) malloc(sizeof(Node))) == NULL) { return 0; }
    memcpy((*spinning_top)->mat, default_mat, 4 * sizeof(float));
    (*spinning_top)->Md = g3x_Identity();

    return init_stick(spinning_top, cylinder) &&
           init_globe(spinning_top, &(*spinning_top)->down, sphere) &&
           init_ring(spinning_top, &(*spinning_top)->down->next, torus);
}



