#ifndef MOTS_H_INCLUDED
#define MOTS_H_INCLUDED

#define max_words 11
#define max_words_len 15
#include "grille.h"

typedef struct{
    char mot[max_words_len];
    int trouve;// 1 trouve, 0 pas encore trouve
}Mot;

typedef struct{
    Mot liste[max_words];
    int nbmots;
}Listemots;

int chargerMotsFichier(const char *Theme, Listemots *listes);
int Verificationinsertionmot(char* word, Grille *g, struct point start, enum direction d);
void ajouterTheme(const char *Theme, Listemots *listes);

#endif // MOTS_H_INCLUDED
