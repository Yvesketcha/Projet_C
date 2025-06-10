#ifndef SAISIR_H_INCLUDED
#define SAISIR_H_INCLUDED
#include "grille.h"

typedef enum{
    TOUCHE_AUCUNE = 0,
    TOUCHE_UP = 8,
    TOUCHE_DOWN = 2,
    TOUCHE_LEFT = 4,
    TOUCHE_RIGHT = 6,
    TOUCHE_UP_LEFT = 7,
    TOUCHE_UP_RIGHT = 9,
    TOUCHE_DOWN_LEFT = 1,
    TOUCHE_DOWN_RIGHT = 3,
    TOUCHE_SPACE = 32,
    TOUCHE_EXIT = 'q'
}touche;

touche liretouche();//Recupere une touche entree par l'utilisateur
void deplacementcurseur(struct point *curseur, touche direction, int ligmax, int colmax, int *gameover);//deplace le curseur selon la direction
void gotoligcolcurseur(int lig, int col);//fonction permettant de positionner le curseur sur un point(x,y)
int wherex();//pour recuperer la position horizontale du curseur
int wherey();//pour recuperer la position verticale du curseur

#endif // SAISIR_H_INCLUDED
