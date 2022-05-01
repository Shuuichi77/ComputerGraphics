#include "../include/table.h"

double const DESK_X = 0.75;
double const DESK_Y = 0.5;
double const DESK_Z = 0.1;
double const LEG_Z  = 0.5;

double const desk_length = DESK_X * CUBE_W;
double const desk_width  = DESK_Y * CUBE_W;
double const desk_height = DESK_Z * CUBE_W;

double const leg_height = LEG_Z * CYLINDER_H;

static int initTableLeg(SceneTree *legs, Shape *cylinder, int leg_num)
{
    if (leg_num == 4) { return 1; }

    SceneTree leg = addChildWithShape(legs, cylinder);
    if (leg == NULL) { return 0; }

    switch (leg_num)
    {
        case 0:applyTranslate(&leg, desk_length * 0.05, desk_width * 0.1, LEG_Z);
            break;
        case 1:applyTranslate(&leg, desk_length * 0.95, desk_width * 0.1, LEG_Z);
            break;
        case 2:applyTranslate(&leg, desk_length * 0.95, desk_width * 0.9, LEG_Z);
            break;
        case 3:applyTranslate(&leg, desk_length * 0.05, desk_width * 0.9, LEG_Z);
            break;
    }

    return initTableLeg(legs, cylinder, leg_num + 1);
}


static int initTableLegs(SceneTree *table, Shape *cylinder)
{
    SceneTree tableLegs = addChildWithColor(table, grey);

    if (tableLegs == NULL) { return 0; }
    tableLegs->scale_factor = (G3Xvector) { (desk_length + desk_width) * 0.02,
                                            (desk_length + desk_width) * 0.02,
                                            LEG_Z };

    return initTableLeg(&tableLegs, cylinder, 0);
}

static int initTableDesk(SceneTree *table, Shape *cube)
{
    SceneTree tableDesk = addChildWithShapeAndColor(table, cube, light_brown);

    if (tableDesk == NULL) { return 0; }
    tableDesk->scale_factor = (G3Xvector) { DESK_X, DESK_Y, DESK_Z };
    applyTranslate(&tableDesk, 0, 0, leg_height);

    return 1;
}

SceneTree initTable(Shape *cube, Shape *cylinder)
{
    SceneTree table = createNode();
    if (table == NULL) { return NULL; }
    applyTranslate(&table, -desk_length / 2., -desk_width / 2., 0.);

    if (!initTableDesk(&table, cube) || !initTableLegs(&table, cylinder))
    {
        freeNode(&table);
        return NULL;
    }

    return table;
}



