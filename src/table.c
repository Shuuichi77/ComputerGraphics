#include "../include/table.h"

int init_table_leg(SceneTree *father, SceneTree *next, Shape *cylinder, int leg_num)
{
    if (leg_num == 4) { return 1; }
    if (leg_num == 0)
    {
        if (!add_child(father)) { return 0; }
        (*father)->down->instance = cylinder;
        translate(&(*father)->down, desk_length * 0.05, desk_width * 0.1, LEG_Z);
        return init_table_leg(father, &(*father)->down, cylinder, leg_num + 1);
    }
    else
    {
        if (!add_next(next, father)) { return 0; }
        (*next)->next->instance = cylinder;
        if (leg_num == 1) { translate(&(*next)->next, desk_length * 0.95, desk_width * 0.1, LEG_Z); }
        else if (leg_num == 2) { translate(&(*next)->next, desk_length * 0.95, desk_width * 0.9, LEG_Z); }
        else if (leg_num == 3) { translate(&(*next)->next, desk_length * 0.05, desk_width * 0.9, LEG_Z); }
        return init_table_leg(father, &(*next)->next, cylinder, leg_num + 1);
    }
}


int init_table_legs(SceneTree *table, SceneTree *desk, Shape *cylinder)
{
    if (!add_next(desk, table)) { return 0; }

    (*desk)->next->col          = grey;
    (*desk)->next->scale_factor = (G3Xvector) { (desk_length + desk_width) * 0.02,
                                                (desk_length + desk_width) * 0.02,
                                                LEG_Z };

    return init_table_leg(&(*desk)->next, NULL, cylinder, 0);
}

int init_table_desk(SceneTree *table, Shape *cube)
{
    if (!add_child(table)) { return 0; }
    (*table)->down->instance     = cube;
    (*table)->down->col          = light_brown;
    (*table)->down->scale_factor = (G3Xvector) { DESK_X, DESK_Y, DESK_Z };
    translate(&(*table)->down, 0, 0, leg_height);

    return 1;
}

int init_table(SceneTree *table, Shape *cube, Shape *cylinder)
{
    if (((*table) = createNode()) == NULL) { return 0; }
    memcpy((*table)->mat, default_mat, 4 * sizeof(float));
    (*table)->Md = g3x_Identity();
    translate(table, -desk_length / 2., -desk_width / 2., 0.);

    return init_table_desk(table, cube) && init_table_legs(table, &(*table)->down, cylinder);
}



