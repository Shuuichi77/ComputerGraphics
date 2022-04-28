#include "../include/stele.h"

int init_pedestal(SceneTree *stele, Shape *cube)
{
    if (!add_child(stele)) { return 0; }
    (*stele)->down->instance     = cube;
    (*stele)->down->col          = light_grey;
    (*stele)->down->scale_factor = (G3Xvector) { PEDESTAL_X, PEDESTAL_Y, PEDESTAL_Z };
    translate(&(*stele)->down, -pedestal_length / 2., -pedestal_width / 2., 0);
    return 1;
}

int init_tower(SceneTree *stele, SceneTree *next, Shape *cylinder)
{
    if (!add_next(next, stele)) { return 0; }
    (*next)->next->instance     = cylinder;
    (*next)->next->col          = light_grey;
    (*next)->next->scale_factor = (G3Xvector) { TOWER_X, TOWER_Y, TOWER_Z };
    translate(&(*next)->next, 0, 0, pedestal_height + tower_height / 2.);

    return 1;
}

int init_tower_ring(SceneTree *stele, SceneTree *next, Shape *torus)
{
    if (!add_next(next, stele)) { return 0; }
    (*next)->next->instance     = torus;
    (*next)->next->col          = light_grey;
    (*next)->next->scale_factor = (G3Xvector) { TOWER_RING_X, TOWER_RING_Y, TOWER_RING_Z };
    translate(&(*next)->next, 0, 0, pedestal_height + tower_ring_height / 2.);

    return 1;
}

int init_stele(SceneTree *stele, Shape *cube, Shape *cylinder, Shape *torus)
{
    if (((*stele) = (Node *) malloc(sizeof(Node))) == NULL) { return 0; }
    memcpy((*stele)->mat, default_mat, 4 * sizeof(float));
    (*stele)->Md = g3x_Identity();

    return init_pedestal(stele, cube) &&
           init_tower(stele, &(*stele)->down, cylinder) &&
           init_tower_ring(stele, &(*stele)->down->next, torus);
}



