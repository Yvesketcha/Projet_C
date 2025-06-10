#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include "grille.h"
#include "mots.h"
#include "saisir.h"

void CouleurMotGrille(int couleurDuTexte, int couleurDeFond);//Appel de la fonction CouleurMotGrille pour mettre les couleurs sur la grille
void LireGrille(Grille *g, struct point *curseur, struct point *start, struct point *end, Listemots *listes, int *score, int temps_restant);//Appel de la fonction LireGrille pour afficher la grille avec le curseur
void enreigistrerscore(char *nomjoueur, int score);
#endif // AFFICHAGE_H_INCLUDED
