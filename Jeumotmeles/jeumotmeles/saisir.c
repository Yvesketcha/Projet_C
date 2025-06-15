#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "grille.h"
#include "saisir.h"

//Fonction permettant de positionner le curseur sur un point de coordonne(x,y)
void gotoligcolcurseur(int lig, int col)
{
    COORD mycoord;//permet de definir une position dans la console
    mycoord.X = col * 2 + decalage;//affectation de la colonne a x
    mycoord.Y = lig;//affectation de la ligne a y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);//cette fonction depalce le curseur dans la console windows a la position(col, lig)
}
//Ces deux fonctions wherex() et wherey() permettent de recuperer la position du curseur
//Fonction permettant de connaitre la position horizontal(colonne) du curseur en ecriture
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.X;
}
//Fonction pour connaitre la position verticale(ligne) du curseur en ecriture
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
    return info.dwCursorPosition.Y;
}

touche liretouche() //Fonction la gestion des touches de directions du curseur
{
    int touch = _getch();//permet de retourner le caractere saisi au clavier(sans besoin de valider)
    switch(touch)
    {
    case '2':
        return TOUCHE_DOWN;
    case '8':
        return TOUCHE_UP;
    case '4':
        return TOUCHE_LEFT;
    case '6':
        return TOUCHE_RIGHT;
    case '7':
        return TOUCHE_UP_LEFT;
    case '9':
        return TOUCHE_UP_RIGHT;
    case '1':
        return TOUCHE_DOWN_LEFT;
    case '3':
        return TOUCHE_DOWN_RIGHT;
    case ' ':
        return TOUCHE_SPACE;
    case 'q':
    case 'Q':
        return TOUCHE_EXIT;
    default:
        return TOUCHE_AUCUNE;
    }
}
void deplacementcurseur(struct point *curseur, touche direction, int ligmax, int colmax, int *gameover)
{
    switch(direction)
    {
    case TOUCHE_UP:
        if(curseur->x > 0)
        {
            curseur->x--;
        }
        break;
    case TOUCHE_DOWN:
        if(curseur->x < ligmax - 1)
        {
            curseur->x++;
        }
        break;
    case TOUCHE_LEFT:
        if(curseur->y > 0)
        {
            curseur->y--;
        }
        break;
    case TOUCHE_RIGHT:
        if(curseur->y < colmax - 1)
        {
            curseur->y++;
        }
        break;
    case TOUCHE_UP_LEFT:
        if (curseur->x > 0 && curseur->y > 0)
        {
            curseur->x--;
            curseur->y--;
        }
        break;
    case TOUCHE_UP_RIGHT:
        if (curseur->x > 0 && curseur->y < colmax - 1)
        {
            curseur->x--;
            curseur->y++;
        }
        break;
    case TOUCHE_DOWN_LEFT:
        if (curseur->x < ligmax - 1 && curseur->y > 0)
        {
            curseur->x++;
            curseur->y--;
        }
        break;
    case TOUCHE_DOWN_RIGHT:
        if (curseur->x < ligmax - 1 && curseur->y < colmax - 1)
        {
            curseur->x++;
            curseur->y++;
        }
        break;
    case TOUCHE_EXIT:
        *gameover = 1;
        break;
    }
}
