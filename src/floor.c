#include "../include/floor.h"

int init_tiles(SceneTree *father, Shape *cube)
{
    if (!addChildWithShapeAndColor(father, cube, dark_grey)) { return 0; }
    translate(&(*father)->down, 0, floor_width, -floor_height);

    if (!addNextWithShapeAndColor(&(*father)->down, father, cube, light_grey)) { return 0; }
    translate(&(*father)->down->next, floor_length, floor_width, -floor_height);

    if (!addNextWithShapeAndColor(&(*father)->down->next, father, cube, dark_grey)) { return 0; }
    translate(&(*father)->down->next->next, floor_length, 0, -floor_height);

    if (!addNextWithShapeAndColor(&(*father)->down->next->next, father, cube, light_grey)) { return 0; }
    translate(&(*father)->down->next->next->next, 0, 0, -floor_height);

    return 1;
}

int init_floor(SceneTree *floor, Shape *cube)
{
    if (((*floor) = (Node *) malloc(sizeof(Node))) == NULL) { return 0; }
    memcpy((*floor)->mat, default_mat, 4 * sizeof(float));
    (*floor)->scale_factor = (G3Xvector) { FLOOR_X, FLOOR_Y, FLOOR_Z };
    (*floor)->Md           = g3x_Identity();

    return init_tiles(floor, cube);
}



