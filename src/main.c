#include <g3x.h>
#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"

#include "../include/floor.h"
#include "../include/table.h"


static int   WWIDTH = 512, WHEIGHT = 512;
static Shape *cube;
static Shape *cylinder;
static Shape *sphere;
static Shape *torus;
static Node  *table;
static Node  *floor_tiles;

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
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

    if (!init_table(&table, cube, cylinder))
    {
        fprintf(stderr, "Error in init_table() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_floor(&floor_tiles, cube))
    {
        fprintf(stderr, "Error in init_floor() malloc\n");
        exit(EXIT_FAILURE);
    }

    /* ----------------------------------------------- */
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
    g3x_CreateScrollv_d("step", &step, 1, 10, 1, "Pas de rendu");
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
    glPointSize(3);

    glPushMatrix();
    glTranslatef(-floor_length, -floor_length, 0.);
    draw_node(floor_tiles);
    glPopMatrix();

    glPushMatrix();
    glRotatef(135, 0., 0., 1.);    /* une rotation autour de l'axe 'x' */
    glTranslatef(0, floor_length * 0.7, 0.);
    draw_node(table);
    glPopMatrix();

    glPushMatrix();
    glRotatef(130, 0., 0., 1.);    /* une rotation autour de l'axe 'x' */
    glTranslatef(floor_length * 0.7, 0, 0.);
    draw_node(table);
    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(-desk_x * 1.1, -desk_y * 1.1, 0.);
//    draw_node(table);
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(-desk_x * 1.1, 0, 0.);
//    draw_node(table);
//    glPopMatrix();
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

//    g3x_SetCameraSpheric(0., 0.25 * PI, 15., (G3Xpoint) { 0., 0., 0. });
    g3x_SetInitFunction(init); /* fonction d'initialisation */
    g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
    g3x_SetDrawFunction(draw); /* fonction de dessin        */
    g3x_SetAnimFunction(anim); /* fonction d'animation      */
    g3x_SetExitFunction(quit); /* fonction de sortie        */

    /* lancement de la boucle principale */
    return g3x_MainStart();
    /* RIEN APRES CA */
}
