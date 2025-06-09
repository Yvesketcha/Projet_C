#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "grille.h"
#include "affichage.h"


//Fonction permettant de generer des lettres de manieres aleatoires
char LettreAleatoire()
{
    return 'A' + rand()%26;
}

// Iniatiliser la grille vide
void Grillevide(Grille *g, int lignes, int colonnes)
{
    int i;
    int j;
    g->lignes = lignes;
    g->colonnes = colonnes;
    for(i = 0; i < lignes; i++)
    {
        for(j = 0; j < colonnes; j++)
        {
            g->grille[i][j].lettre = ' ';
            g->grille[i][j].lettreselectionne = 0;
            g->grille[i][j].lettretrouve = 0;
        }
    }
}

char input[10];//Les mots qui sont inseres dans la grille
int input_point[10][3]; //Les coordonnees x, y et la direction des mots inseres dans la grille
int mark[10]= {0}; // utilise pour marquer les mots identifies par l'utilisateur afin qu'une reponse en double ne soit pas acceptees

int flag = 0; //flag

struct point shift_point(struct point start, enum direction d) //Start est la position du point a decaler dans la grille, est la direction dans laquelle le point se deplace
{
    int i = start.x;
    int j = start.y;
    struct point new_point = start; //La position finale du point decale depends de la direction d
    switch(d)
    {
    //Huits directions dans laquelle le point peut se deplacer et permet aussi de gerer les debordements
    case UP:
        new_point.x = i-1;//Deplacement vers le haut
        new_point.y = j;
        break;
    case DOWN:
        new_point.x = i+1;//Deplacement vers le bas
        new_point.y = j;
        break;
    case LEFT:
        new_point.x = i;
        new_point.y = j-1;//Deplacement vers la gauche
        break;
    case RIGHT:
        new_point.x = i;
        new_point.y = j+1;//Deplacement vers la droite
        break;
    case UP_LEFT:
        new_point.x = i-1;//Deplacement de la ligne vers le haut
        new_point.y = j-1;//Deplacement de la colonne vers la gauche
        break;
    case UP_RIGHT:
        new_point.x = i-1;//Deplacement de la ligne vers le haut
        new_point.y = j+1;//Deplacement de la colonne vers la droite
        break;
    case DOWN_LEFT:
        new_point.x = i+1;//Deplacement de la ligne vers le bas
        new_point.y = j-1;//Deplacement de la colonne vers la gauche
        break;
    case DOWN_RIGHT:
        new_point.x = i+1;//Deplacement de la ligne vers le bas
        new_point.y = j+1;//Deplacement de la colonne vers le droite
        break;
    default:
        new_point.x = i;//Position de la ligne par defaut
        new_point.y = j;//Position de la colonne par defaut
        break;
    }
    //Gerer les erreurs hors limites
    /*if(new_point.x < -1 || new_point.x > gridsize || new_point.y < -1 || new_point.y > gridsize)
    {
        flag = 1;//Gestion des exceptions debordement
    }*/
    return new_point;//Retourne le nouveau point

};

//char nullchar = 'Z';

enum direction arr[10]=
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    LEFT,
    RIGHT
};
int p = 0;//utilisé comme index pour parcourir le tableau ci-dessus arr

void Insertionmotgrille(char *word, Grille *g, int i) //Fonction pour inserer un mot dans la grille
{
    //i signifie que le ieme mot est en cours d'insertion
    struct point place;//point ou le mot va etre insere dans la grille
    enum direction d;//direction dans laquelle le mot va s'orienter
    do
    {
        place.x = rand() % g->lignes;//definie une ligne de maniere aleatoire
        place.y = rand() % g->colonnes;//definie une colonne de maniere aleatoire
        d = (arr[(p++) %10]);// Obtenir une direction selon la regle specifie
    }
    while(!Verificationinsertionmot(word, g, place, d));

    int j = 0;//Boucle variable

    struct point new_point = place;//Copie de la valeur de la structure place dans la valeur de la structure new_point
    while(j < (int)strlen(word))
    {
        g->grille[new_point.x][new_point.y].lettre = (char)toupper(word[j]);//Insertion dans la grille
        new_point = shift_point(new_point, d);//Deplacement accorde a la direction
        j++;
    }
    input_point[i][0] = place.x;//utilise pour modifier la grille ulterieurement lorsque l'utilisateur entre un mot correct
    input_point[i][1] = place.y;
    input_point[i][2] = d;
}

void remplissagegrille(Grille *g) //Fonction pour le remplissage de la grille
{
    srand(time(NULL));
    for(int i = 0; i < g->lignes; i++)
    {
        for(int j = 0; j < g->colonnes; j++)
        {
            if(g->grille[i][j].lettre == ' ')
            {
                g->grille[i][j].lettre = LettreAleatoire();
            }
        }
    }
}

void changertaillegrille(Grille *g, int lignes, int colonnes){
    printf("Veuillez entrez la taille de la grille par exemple: (10x10)");
    printf("Entrez la taille des lignes")
}
