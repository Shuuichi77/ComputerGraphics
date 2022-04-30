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

static G3Xpoint TARGET;

static int    NB_PAIR_STELE = 8;
static int    *random_radius;
static double g_step        = 1.0;

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

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
    srand(time(0));

    if (NULL == (random_radius = (int *) malloc(sizeof(int) * NB_PAIR_STELE * 4)))
    {
        fprintf(stderr, "Error in random_radius malloc\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NB_PAIR_STELE * 4; i++)
    {
        random_radius[i] = rand();
    }

    /* Call each init function only 1 time : we'll then use an instance of each shape */
    /* ----------------------------------------------- */
    if (!init_cube(&cube))
    {
        fprintf(stderr, "Error in init_cube() malloc\n");
        exit(EXIT_FAILURE);
    }
    if (!init_cylinder(&cylinder))
    {
        fprintf(stderr, "Error in init_cylinder() malloc\n");
        exit(EXIT_FAILURE);
    }
    if (!init_sphere(&sphere))
    {
        fprintf(stderr, "Error in init_sphere() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_torus(&torus))
    {
        fprintf(stderr, "Error in init_torus() malloc\n");
        exit(EXIT_FAILURE);
    }
    /* ----------------------------------------------- */

    if (!init_floor(&floor_tiles, cube))
    {
        fprintf(stderr, "Error in init_floor() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_stool(&stool, cube, cylinder))
    {
        fprintf(stderr, "Error in init_stool() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_table(&table, cube, cylinder))
    {
        fprintf(stderr, "Error in init_table() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_spinning_top(&spinning_top, cylinder, sphere, torus))
    {
        fprintf(stderr, "Error in init_spinning_top() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_stele(&stele, cube, cylinder, torus))
    {
        fprintf(stderr, "Error in init_stele() malloc\n");
        exit(EXIT_FAILURE);
    }
    /* ----------------------------------------------- */
}


static void camera_info(void)
{
    G3Xcamera *cam = g3x_GetCamera();
    fprintf(stderr, "position (x:%lf,y:%lf,z:%lf)\n", cam->pos->x, cam->pos->y, cam->pos->z);
    fprintf(stderr, "cible    (x:%lf,y:%lf,z:%lf)\n", cam->tar->x, cam->tar->y, cam->tar->z);
    fprintf(stderr, "coord. spheriques (d:%lf,theta:%lf,phi:%lf)\n", cam->dist, cam->theta, cam->phi);
}

static void ctrl(void)
{
    g3x_CreateScrollv_d("g_step", &g_step, 1, 10, 1, "Pas de rendu");
    g3x_SetKeyAction('c', camera_info, "pos./dir. de la camera => terminal");

    g3x_CreateScrollv_d("x", &(g3x_GetCamera())->tar->x, -10, 20, 1, "x");
    g3x_CreateScrollv_d("y", &(g3x_GetCamera())->tar->y, -10, 20, 1, "y");
    g3x_CreateScrollv_d("z", &(g3x_GetCamera())->tar->z, -10, 20, 1, "z");
    g3x_CreateScrollv_d("dist", &(g3x_GetCamera()->dist), 1, 20, 1, "dist");

    g3x_CreateScrollh_d("Target.z", &(TARGET).z, -10, 20, 1, "z");
    g3x_CreateScrollh_d("Target.y", &(TARGET).y, -10, 20, 1, "y");
    g3x_CreateScrollh_d("Target.x", &(TARGET).x, -10, 20, 1, "x");
}

static void draw_stool_on_desk(void)
{
    glPushMatrix();
    draw_node(table, *(g3x_GetCamera()->pos), g3x_Identity());
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 1., 0., 0.);
    glTranslatef(desk_length * 0.05, -desk_width * 0.3, -2 * (leg_height + desk_height + floor_height) + desk_height);
    draw_node(stool, *(g3x_GetCamera()->pos), g3x_Identity());
    glPopMatrix();
}

static void draw_desks_and_stools(void)
{
    glPushMatrix();
    glTranslatef(-floor_length, -floor_length, 0.);
    draw_node(floor_tiles, *(g3x_GetCamera()->pos), g3x_Identity());
    glPopMatrix();

    glPushMatrix();
    glRotatef(135, 0., 0., 1.);
    glTranslatef(0, floor_length * 0.7, 0.);
    draw_stool_on_desk();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-floor_length * 0.5, floor_length * 0.5, 0.);
    draw_node(stool, *(g3x_GetCamera()->pos), g3x_Identity());
    glPopMatrix();

    glPushMatrix();
    glRotatef(130, 0., 0., 1.);
    glTranslatef(-floor_length * 0.7, 0, 0.);
    draw_node(table, *(g3x_GetCamera()->pos), g3x_Identity());
    glPopMatrix();
}

static void draw_spinning_top_on_stele(int radius_num, G3Xhmat mat)
{
    int radius = random_radius[radius_num];

    glPushMatrix();
    draw_node(stele, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                 ((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                 pedestal_height + tower_height);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                                               ((((radius % 2) ? -radius : radius) % 50) / 100.) * tower_radius,
                                               pedestal_height + tower_height));
    glRotatef(((radius % 2) ? -radius : radius) % 45, 1., 0., 0.);
    glRotatef(((radius % 2) ? -radius : radius) % 45, 0., 1., 0.);
    draw_node(spinning_top, *(g3x_GetCamera()->pos), mat);
    glPopMatrix();

    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(0., 0., -(pedestal_height + tower_height)));
}

static void draw_pair_spinning_top_on_stele(int n, G3Xhmat mat)
{
    glPushMatrix();
    glTranslatef(-n * floor_length, -1.5 * floor_width, 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(floor_length + pedestal_length / 2., floor_length * n, 0.));
    draw_spinning_top_on_stele(n, mat);
    glPopMatrix();

    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-(floor_length + pedestal_length / 2.), -(floor_length * n), 0.));

    glPushMatrix();
    glTranslatef(-n * floor_length, 1.5 * floor_width, 0.);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-floor_length - pedestal_length / 2., floor_length * n, 0.));
    draw_spinning_top_on_stele(n + 1, mat);
    glPopMatrix();

    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-(-floor_length - pedestal_length / 2.), -(floor_length * n), 0.));
}

static void draw_steles_scene()
{
    G3Xhmat mat = g3x_Identity();

    glPushMatrix();
//    glScaled(0.5, 0.5, 0.5);
//    mat = g3x_Mat_x_Mat(mat, g3x_Homothetie3d(0.5, 0.5, 0.5));

//    double scene_tx = (NB_PAIR_STELE - 0.5) * floor_length;
    double scene_tx = 0;
    double scene_ty = 0;
//    double scene_tz = -(PEDESTAL_Z + TOWER_Z + STICK_Z);
    double scene_tz = -(PEDESTAL_Z + TOWER_Z * 2 + STICK_Z);
    glTranslatef(scene_tx, scene_ty, scene_tz);
    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(scene_tx, scene_ty, scene_tz));

    for (int i = 0; i < NB_PAIR_STELE * 2; i++)
    {
        if (i < NB_PAIR_STELE)
        {
            glPushMatrix();
            glTranslatef((-i * floor_length * 2) + (-1.5 * floor_length), -floor_width, 0.);
            mat = g3x_Mat_x_Mat(mat,
                                g3x_Translation3d((-i * floor_length * 2) + (-1.5 * floor_length), -floor_width, 0.));
            draw_node(floor_tiles, *(g3x_GetCamera()->pos), mat);
            glPopMatrix();

            mat = g3x_Mat_x_Mat(mat,
                                g3x_Translation3d(-((-i * floor_length * 2) + (-1.5 * floor_length)), floor_width, 0.));
        }

        draw_pair_spinning_top_on_stele(i, mat);
    }
    glPopMatrix();

}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
//    printf("------------------------------ DEBUT ------------------------------\n");
    g3x_SetCameraTar(TARGET); // TODO : enlever

    // -------------------------------------------------------------------------

//    glPointSize(3);
//    draw_desks_and_stools();
//    return;

    // -------------------------------------------------------------------------

    glPointSize(3);
    draw_steles_scene();
//    camera_info();
    return;

    // -------------------------------------------------------------------------
//    G3Xhmat mat = g3x_Identity();
//    glPushMatrix();
//    glScaled(0.5, 0.5, 0.5);
//    mat = g3x_Mat_x_Mat(mat, g3x_Homothetie3d(0.5, 0.5, 0.5));
//
//    glTranslatef(0., 0., -7.);
//    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(0., 0., -7.));
//
//    glPushMatrix();
//    printf("------ 1st stele ------\n");
//    draw_spinning_top_on_stele(0, mat);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-20., 0., 0.);
//    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-20., 0., 0.));
//    printf("------ 2nd stele ------\n");
//    draw_spinning_top_on_stele(1, mat);
//    glPopMatrix();
//
//    glPopMatrix();
//    return;

    // -------------------------------------------------------------------------

//    glPointSize(3);
//    g3x_Material(G3Xr, .2, .6, .9, 1, 1);
//
//    cylinder->draw_faces(cylinder, (G3Xvector) { 1, 1, 1 }, g_step);
//    glTranslatef(2., 0, 0.);
//    cube->draw_faces(cube, (G3Xvector) { 1, 1, 1 }, g_step);
//    glTranslatef(0., 4, 0.);
//    sphere->draw_faces(sphere, (G3Xvector) { 1, 1, 1 }, g_step);
//    glTranslatef(-3., 0., 0.);
//    stele_torus->draw_faces(stele_torus, (G3Xvector) { 1, 1, 1 }, g_step);
//    glTranslatef(-2., -3., 0.);
//    spinning_top_torus->draw_faces(spinning_top_torus, (G3Xvector) { 1, 1, 1 }, g_step);
//    return;

    // -------------------------------------------------------------------------

//    draw_spinning_top_on_stele(0, g3x_Identity());
//    draw_spinning_top_on_stele(1, g3x_Identity());
////    double  n   = 0.;
//    int     n   = 0;
//    G3Xhmat mat = g3x_Identity();
//    glPushMatrix();
//    glTranslatef(floor_length + pedestal_length / 2., floor_length * n, 0.);
////    glTranslatef(2., 0., 0.);
////    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(floor_length + pedestal_length / 2., floor_length * n, 0.));
//    draw_spinning_top_on_stele(n, mat);
//    glPopMatrix();
//
////    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-(floor_length + pedestal_length / 2.), -(floor_length * n), 0.));
//
//    glPushMatrix();
////    glTranslatef(-floor_length - pedestal_length / 2., floor_length * n, 0.);
////    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-floor_length - pedestal_length / 2., floor_length * n, 0.));
//    draw_spinning_top_on_stele(n + 1, mat);
//    glPopMatrix();
//
//    mat = g3x_Mat_x_Mat(mat, g3x_Translation3d(-(-floor_length - pedestal_length / 2.), -(floor_length * n), 0.));
//
//    draw_pair_spinning_top_on_stele(0, g3x_Identity());


    printf("------------------------------- FIN -------------------------------\n");
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void)
{
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS ou presque                    */
/***************************************************************************/
int main(int argc, char **argv)
{
    /* creation de la fenetre - titre et tailles (pixels) */
    g3x_InitWindow(*argv, WWIDTH, WHEIGHT);
//    g3x_SetCameraSpheric(0., 0.25 * PI, 20., (G3Xpoint) { 0., 0., 0. });
    g3x_SetInitFunction(init); /*² fonction d'initialisation */
    g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
    g3x_SetDrawFunction(draw); /* fonction de dessin        */
    g3x_SetAnimFunction(anim); /* fonction d'animation      */
    g3x_SetExitFunction(quit); /* fonction de sortie        */

    /* lancement de la boucle principale */
    return g3x_MainStart();
    /* RIEN APRES CA */
}
