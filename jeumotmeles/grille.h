#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#define gridsize 10
#define colorsize 10
typedef struct
{
    char lettre;
    int lettretrouve //1 si la lettre fait partie d'in mot trouve
} Case;

typedef struct
{
    Case grille[gridsize][gridsize];
    int color[colorsize][colorsize];
    int lignes;
    int colonnes;
} Grille;

typedef struct
{
    int x;
    int y;
} point;

void Grillevide(Grille *g, int lignes, int colonnes);
void LireGrille(Grille *g);
void Insertionmotgrille(char *word, int i);
void remplissagegrille(Grille *g);

#endif // GRILLE_H_INCLUDED
