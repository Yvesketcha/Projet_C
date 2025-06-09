#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#define gridsize 15
#define decalage 70

typedef struct
{
    char lettre;
    int lettreselectionne; //1 si la case est selectionne temporairement(jaune)
    int lettretrouve; //1 si la lettre fait partie d'in mot trouve
} Case;

typedef struct
{
    Case grille[gridsize][gridsize];
    int lignes;
    int colonnes;
} Grille;

struct point
{
    int x;
    int y;
};

//Enum direction
//Enumerateur pour la direction dans la grille, dans laquelle le mot est insere.

enum direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

void Grillevide(Grille *g, int lignes, int colonnes);
void Insertionmotgrille(char *word, Grille *g, int i);
void remplissagegrille(Grille *g);
char LettreAleatoire();
struct point shift_point(struct point start, enum direction d);

#endif // GRILLE_H_INCLUDED
