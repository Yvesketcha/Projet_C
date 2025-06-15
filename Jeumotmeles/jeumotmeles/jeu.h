#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "grille.h"
#include "mots.h"
/*#include "grille.h"
#include "mots.h"*/

int CommencerJeu(const char *Theme, int lignes, int colonnes, const char *nomjoueur);
void nettoyerselection(Grille *g);
void marqueselection(Grille *g, struct point start, struct point end);
char *extractionmot(Grille *g, struct point start,struct point end);
void marque_valide(Grille *g, struct point start, struct point end);
void marquemottrouve(Listemots *listes, char *word);
void my_strrev(char *str);
enum direction determinedirectionpoint(struct point start, struct point end);

#endif // JEU_H_INCLUDED
