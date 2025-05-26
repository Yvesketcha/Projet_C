#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grille.h"

void LettreAleatoire()
{
    return 'A' + rand()%26;
}

// Iniatiliser la grille vide
void Grillevide(Grille *g, int lignes, int colonnes)
{
    g->lignes = lignes;
    g->colonnes = colonnes;
    for(i = 0; i < lignes; i++)
    {
        for(j = 0; j < colonnes; j++)
        {
            g->grille[i][j].lettre == '';
            g->grille[i][j].lettretrouve = 0;
        }
    }
}

// Afficher la grille dans la console
void LireGrille(Grille *g)
{
    for(i = 0; i < g->lignes; i++)
    {
        for(j = 0; j < g->colonnes; j++)
        {
            HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE);
            WORD wOldColorAttrs;
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;



            GetConsoleScreenBufferInfo(h, &csbiInfo);
            wOldColorAttrs = csbiInfo.wAttributes;

            //Definie la nouvelle information de couleur

            SetConsoleTextAttribute ( h, color[i][j] );


            //Retrouve la couleur originale

            printf("%c", g->grille[i][j].lettre);
            SetConsoleTextAttribute ( h, wOldColorAttrs);
        }
        printf("\n");
    }
}

//Enum direction
//Enumerateur pour la direction dans la grille, dans laquelle le mot est insere.
enum direction
{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

char input[10];//Les mots qui sont inseres dans la grille
int input_point[10][3]; //Les coordonnees x, y et la direction des mots inseres dans la grille
int mark[10]= {0} // utilise pour marquer les mots identifies par l'utilisateur afin qu'un reponse en double ne soit pas acceptees

int flag //flag

struct point shift_point(struct point start, enum direction d) //Start est la position du point a decaler dans la grille, est la direction dans laquelle le point se deplace
{
    int i = start.x;
    int j = start.y;
    struct point new_point; //La position finale du point decale depends de la direction d
    switch(d)
    {
    //Huits directions dans laquelle le curseur peut se deplacer
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
    if(new_point.x < -1 || new_point.x > gridsize || new_point.y < -1 || new_point.y > gridsize)
    {
        flag = 1;//Gestion des exceptions
    }
    return new_point;//Retourne le nouveau point

};

char nullchar = 'Z';

int Verificationinsertionmot(char* word, Grille *g, struct point start, enum direction d) //Fonction permettant de verifier si un mot peut etre insere dans la grille dans cette position ou pas
{
    int i = 0;
    struct point new_point = start;
    while(i < (int)strlen(word))//parcourt le tableau de caractere du mot
    {
        //Tenter de deplacer le point vers le nouveau point
        if(g->grille[new_point.x][new_point.y] == nullchar || g->grille[new_point.x][new_point.y] == word[i])
        {
            new_point = shift_point(new_point, d);
            i++;
        }
        else{
            return 0;//Si le mot ne peut pas etre insere renvoie faux
        }
        if(flag == 1){
            return 0;//Cet indicateur dans a fonction de decalage de point en raison d'une exception de limites du tableau
        }
        return 1;//Peut etre insere donc retourne vraie
    }
}
int arr[10]={1,2,3,4,5,6,1,2,3,4}//ce tableau assure une division de 40, 40, 20 pour cent des mots dans les directions horizontale, verticale et diagonale
int p = 0;//utilisé comme index pour parcourir le tableau ci-dessus arr

void Insertionmotgrille(char *word, Grille *g, int i) //Fonction pour inserer un mot dans la grille
{
    //i signifie que le ieme mot est en cours d'insertion
    struct point place;//point ou le mot va etre insere dans la grille
    enum direction d;
    do
    {
        place.x = rand() % gridsize;//definie une ligne de maniere aleatoire
        place.y = rand() % gridsize;//definie une colonne de maniere aleatoire
        d = (arr[(p++)%10]);// Obtenir une direction selon la regle specifie
    }
    while(!Verificationinsertionmot());

    int j = 0;//Boucle variable

    struct point new_point = place;//Copie de la valeur de la structure place dans la valeur de la structure new_point
    while(j < (int)strlen(word))
    {
        g->grille[new_point.x][new_point.y] == (char)toupper(word[j]);//Insertion dans la grille
        new_point = shift_point(new_point, d);//Deplacement accorde a la direction
        j++;
    }
    input_point[i][0] = place.x//utilise pour modifier la grille ulterieurement lorsque l'utilisateur entre un mot correct
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
            if(g->grille[i][j] == '')
            {
                g->grille[i][j] = LettreAleatoire();
            }
        }
    }
}
