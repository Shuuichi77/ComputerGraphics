#include "../include/floor.h"

double const FLOOR_X = 1. / 3.;
double const FLOOR_Y = FLOOR_X;
double const FLOOR_Z = 0.001 / 3.;

double const floor_length = FLOOR_X * CUBE_W;
double const floor_width  = FLOOR_Y * CUBE_W;
double const floor_height = FLOOR_Z * CUBE_W;

static int init_tiles(SceneTree *blackTileFather, SceneTree *whiteTileFather, Shape *cube)
{
    SceneTree blackTile1 = addChildWithShape(blackTileFather, cube);
    if (blackTile1 == NULL) { return 0; }
    applyTranslate(&blackTile1, 0, floor_width, -floor_height);

    SceneTree whiteTile1 = addChildWithShape(whiteTileFather, cube);
    if (whiteTile1 == NULL) { return 0; }
    applyTranslate(&whiteTile1, floor_length, floor_width, -floor_height);

    SceneTree blackTile2 = addChildWithShape(blackTileFather, cube);
    if (blackTile2 == NULL) { return 0; }
    applyTranslate(&blackTile2, floor_length, 0, -floor_height);

    SceneTree whiteTile2 = addChildWithShape(whiteTileFather, cube);
    if (whiteTile2 == NULL) { return 0; }
    applyTranslate(&whiteTile2, 0, 0, -floor_height);

    return 1;
}

SceneTree initFloor(Shape *cube)
{
    SceneTree floor = createNode();
    if (floor == NULL) { return NULL; }
    floor->scale_factor = (G3Xvector) { FLOOR_X, FLOOR_Y, FLOOR_Z };
    applyTranslate(&floor, -floor_length, -floor_width, 0);

    SceneTree blackTileFather = addChildWithColor(&floor, dark_grey);
    SceneTree whiteTileFather = addChildWithColor(&floor, light_grey);

    if (!init_tiles(&blackTileFather, &whiteTileFather, cube))
    {
        freeNode(&floor);
        return NULL;
    }

    return floor;
}



