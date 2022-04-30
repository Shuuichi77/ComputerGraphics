#ifndef __SHAPE_H__
#define __SHAPE_H__

// Rouge    : x
// Vert     : y
// Bleu     : z

#include <g3x.h>

#define NBM 100                   // Nombre de méridiens (lignes verticales)
#define NBP 100                   // Nombre de parallèles (lignes horizontales)
#define NBC 50                    // Nombre de cercles sur les bases (pour le cylindre)

typedef struct _shape_
{
    int       n1, n2, n3;   /* Valeurs d’échantillonnage max - la plupart du temps 2 suffisent */
    G3Xpoint  *vrtx;        /* Tableau des vertex - spécifique d’une forme */
    G3Xvector *norm;        /* Tableau des normales - spécifique d’une forme */
    /* Méthode d’affichage - spécifique d’une forme */
    void (*draw_points)(struct _shape_ *, G3Xvector scale_factor); /* Mode GL_POINTS */
    void (*draw_faces )(struct _shape_ *, G3Xvector scale_factor, double step); /* Mode GL_TRIANGLES ou GL_QUADS */
} Shape, *ShapePtr;

/**
 * Renvoie le minimum entre a et b.
 */
int min(int a, int b);

/**
 * Dessine un side et une normale aux coordonnées fournies.<br/>
 * La normale sert notamment à calculer les réflexions de lumières.
 */
void NormalVertex3dv(Shape shape, unsigned int index);

#endif