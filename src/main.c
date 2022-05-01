#include <g3x.h>
#include <time.h>

#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"

#include "../include/floor.h"
#include "../include/stool.h"
#include "../include/spinning_top.h"
#include "../include/stele.h"
#include "../include/table.h"

static int const NB_QUAD_STELE = 10; // 10 * 4 = 40 steles (20 per row)
static int       *random_radius;
static double    g_step        = 1.0;

static int   WWIDTH = 512, WHEIGHT = 512;
static Shape *cube;
static Shape *cylinder;
static Shape *sphere;
static Shape *torus;

static Node *floor_tiles;
static Node *table;
static Node *stool;

static Node *spinning_top;
static Node *stele;

static void init(void)
{
    srand(time(0));

    if (NULL == (random_radius = (int *) malloc(sizeof(int) * NB_QUAD_STELE * 2)))
    {
        fprintf(stderr, "Error in random_radius malloc\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NB_QUAD_STELE * 2; i++)
    {
        random_radius[i] = rand();
    }

    /* Call each init function only 1 time : we'll then use an instance of each shape */
    /* --------------------------------------------------------------------------- */
    if (NULL == (cube = initCube()))
    {
        fprintf(stderr, "Error in initCube() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == (cylinder = initCylinder()))
    {
        fprintf(stderr, "Error in initCylinder() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == (sphere = initSphere()))
    {
        fprintf(stderr, "Error in initSphere() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == (torus       = initTorus()))
    {
        fprintf(stderr, "Error in initTorus() malloc\n");
        exit(EXIT_FAILURE);
    }
    /* --------------------------------------------------------------------------- */
    if (NULL == (floor_tiles = initFloor(cube)))
    {
        fprintf(stderr, "Error in initFloor() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == (stool = initStool(cube, cylinder)))
    {
        fprintf(stderr, "Error in initStool() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == (table = initTable(cube, cylinder)))
    {
        fprintf(stderr, "Error in initTable() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == (spinning_top = initSpinningTop(cylinder, sphere, torus)))
    {
        fprintf(stderr, "Error in initSpinningTop() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (NULL == (stele = initStele(cube, cylinder, torus)))
    {
        fprintf(stderr, "Error in initStele() malloc\n");
        exit(EXIT_FAILURE);
    }
    /* --------------------------------------------------------------------------- */
}

static void printCameraInfo(void)
{
    G3Xcamera *cam = g3x_GetCamera();
    fprintf(stderr, "position (x:%lf,y:%lf,z:%lf)\n", cam->pos->x, cam->pos->y, cam->pos->z);
    fprintf(stderr, "cible    (x:%lf,y:%lf,z:%lf)\n", cam->tar->x, cam->tar->y, cam->tar->z);
    fprintf(stderr, "coord. spheriques (d:%lf,theta:%lf,phi:%lf)\n", cam->dist, cam->theta, cam->phi);
}

static void ctrl(void)
{
    g3x_SetKeyAction('c', printCameraInfo, "pos./dir. de la camera => terminal");
    g3x_CreateScrollv_d("dist", &(g3x_GetCamera()->dist), 1, 10, 1, "dist");
}

static void drawStoolOnTable(G3Xhmat mat)
{
    glPushMatrix();
    draw_node(table, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 1., 0., 0.);
    glTranslatef(desk_length * 0.05, -desk_width * 0.3, -2 * (leg_height + desk_height + floor_height) + desk_height);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(desk_length * 0.05,
                                               -desk_width * 0.3,
                                               -2 * (leg_height + desk_height + floor_height) + desk_height));
    draw_node(stool, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();
}

static void drawTablesStoolsScene(void)
{
    glPointSize(3);
    G3Xhmat mat = g3x_Identity();

    glPushMatrix();
    draw_node(floor_tiles, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.25, 0.25, 0.25);
    mat = g3x_Mat_x_Mat(mat, g3x_Homothetie3d(0.25, 0.25, 0.25));

    glPushMatrix();
    glRotatef(135, 0., 0., 1.);
    glTranslatef(0, 0.7 * floor_length / mat.m[5], 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(0, 0.7 * floor_length / mat.m[5], 0.));

    drawStoolOnTable(mat);
    glPopMatrix();

    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(0, -0.7 * floor_length / mat.m[5], 0.));

    glPushMatrix();
    glTranslatef(-floor_length * 0.5 / mat.m[0], floor_length * 0.5 / mat.m[5], 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-floor_length * 0.5 / mat.m[0], floor_length * 0.5 / mat.m[5], 0.));
    draw_node(stool, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();

    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(floor_length * 0.5 / mat.m[0], -floor_length * 0.5 / mat.m[5], 0.));

    glPushMatrix();
    glRotatef(130, 0., 0., 1.);
    glTranslatef(-floor_length * 0.7 / mat.m[0], 0, 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-floor_length * 0.7 / mat.m[0], 0, 0.));
    draw_node(table, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();

    glPopMatrix();
}

static void drawSpinningTopOnStele(int radius_num, G3Xhmat mat)
{
    int radius = random_radius[radius_num];

    glPushMatrix();
    draw_node(stele, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                 ((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                 pedestal_height + tower_height);

    glRotatef(((radius % 2) ? -radius : radius) % 45, 1., 0., 0.);
    glRotatef(((radius % 2) ? -radius : radius) % 45, 0., 1., 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                                               ((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                                               pedestal_height + tower_height));

    draw_node(spinning_top, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();
}

static void drawPairSpinningTopOnStele(int n, G3Xhmat mat)
{
    glPushMatrix();
    glTranslatef(-n * floor_length, -1.5 * floor_width, 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-n * floor_length, -1.5 * floor_width, 0.));

    drawSpinningTopOnStele(n, mat);
    glPopMatrix();

    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(n * floor_length, 1.5 * floor_width, 0.));

    glPushMatrix();
    glTranslatef(-n * floor_length, 1.5 * floor_width, 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-n * floor_length, 1.5 * floor_width, 0.));

    drawSpinningTopOnStele(n + 1, mat);
    glPopMatrix();
}

static void drawStelesScene()
{
    glPointSize(3);
    G3Xhmat mat = g3x_Identity();

    glPushMatrix();
//    double scene_tx = (NB_PAIR_STELE - 0.5) * floor_length; // To center camera between steles
    double scene_tx = 0;
    double scene_ty = 0;
    double scene_tz = -(pedestal_height + tower_height * 2 + stick_height) / 2;

    glTranslatef(scene_tx, scene_ty, scene_tz);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(scene_tx, scene_ty, scene_tz));

    for (int i = 0; i < NB_QUAD_STELE * 2; i++)
    {
        if (i < NB_QUAD_STELE)
        {
            glPushMatrix();
            glTranslatef((-i * floor_length * 2) - (0.5 * floor_length), 0., 0.);
            mat = g3x_Mat_x_Mat(mat, g3x_Translation3d((-i * floor_length * 2) - (0.5 * floor_length), 0., 0.));

            draw_node(floor_tiles, *(g3x_GetCamera()->pos), mat);
            glPopMatrix();

            mat = g3x_Mat_x_Mat(mat,
                                g3x_Translation3d(-((-i * floor_length * 2) - (0.5 * floor_length)), 0., 0.));
        }

        drawPairSpinningTopOnStele(i, mat);
    }

    glPopMatrix();
}

static void quit(void)
{
    fprintf(stdout, "Freeing shapes & nodes\n");
    freeShape(cube);
    freeShape(cylinder);
    freeShape(sphere);
    freeShape(torus);

    freeNode(&floor_tiles);
    freeNode(&table);
    freeNode(&stool);
    freeNode(&spinning_top);
    freeNode(&stele);
    fprintf(stdout, "Done. Good bye !\n");
}

static void usage()
{
    printf("Usage :\n"
           "./main steles (or ./main)\n"
           "./main tables\n");
}

int main(int argc, char **argv)
{
    if (argc > 2 ||
        (argc == 2 && strcmp(argv[1], "tables") && strcmp(argv[1], "steles")))
    {
        usage();
        return 0;
    }

    g3x_InitWindow(*argv, WWIDTH, WHEIGHT);
    g3x_SetInitFunction(init);
    g3x_SetCtrlFunction(ctrl);

    switch (argc)
    {
        case 1:g3x_SetDrawFunction(drawStelesScene);
            break;

        case 2: g3x_SetDrawFunction(!strcmp(argv[1], "steles") ? drawStelesScene : drawTablesStoolsScene);
            break;
    }

    g3x_SetExitFunction(quit);

    return g3x_MainStart();
}
