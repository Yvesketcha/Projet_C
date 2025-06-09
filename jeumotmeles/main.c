#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "grille.h"
#include "mots.h"
#include "jeu.h"
#include "saisir.h"

#define max_theme 100
#define chemin_base "C:\\Cours\\ProgrammationC\\Jeumotmeles\\jeumotmeles\\Theme\\" //pour definir le chemin ou on va recuperer nos fichiers

int main()
{

    char nomjoueur[50];
    srand(time(NULL));
    int choix;
    int taillesize;
    char cheminFichier[256];
    printf("\n");
    printf("Veuillez entrez votre le nom du joueur:\n");
    scanf("%49s", nomjoueur);
    printf("Bienvenue chers %s Veuillez effectuer votre choix\n", nomjoueur);
    printf("=========================================================Notre menu:================================================================\n");
    printf("\nPress 1 pour choisir un theme\n");
    printf("\nPress 2 pour ajouter un theme\n");
    printf("\nPress 3 pour la taille de la grille\n");
    printf("\nPress 4 pour quitter le jeu\n");
    scanf("%d", &choix);
    if(choix == 3){
        printf("Veuillez entrez la taille de la grille:\n");
        scanf("%d", &taillesize);
    }
    else{
        taillesize = gridsize;//gridsize est la taille par defaut
    }
    switch(choix){
        case 1:{
            int Themechoisi;
            char *Theme[] = {"Animaux", "Pays", "Afrique", "Fruit"};//Definir un pointeur de tableau
            int nbTheme = sizeof(Theme) / sizeof(Theme[0]);
            printf("Veuillez choisir un theme: \n");
            for(int i = 0; i < nbTheme; i++){
                printf("%d.%s\n", i + 1, Theme[i]);
            }
            scanf("%d", &Themechoisi);
            if(Themechoisi < 1 || Themechoisi > nbTheme){
                printf("choix invalide\n");
                return 1;
            }
            //snprintf(cheminFichier, sizeof(cheminFichier), "%s%s", chemin_base, Theme[Themechoisi - 1]);
            CommencerJeu(Theme[Themechoisi - 1], gridsize, gridsize);//Appel de la fonction commencerjeu pour la lancer la partie
            break;
        }
        case 2:{
            //printf("Bonjour\n");
            Listemots nouvelles_listes;
            ajouterTheme(NULL, &nouvelles_listes);
            break;
        }
        case 3:
            printf("La taille que vous avez choisie: %dx%d", taillesize, taillesize);
            break;
        case 4:
            printf("Aurevoir chers utilisateur\n");
            return 0;
        default:
            printf("Vous n'avez effectuez aucun choix");
            break;
    }
    return 0;
}
