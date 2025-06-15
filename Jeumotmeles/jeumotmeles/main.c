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
    int quitter = 0;
    int taillesize;
    int lignes = gridsize;//Initialisation avec la taille par defaut
    int colonnes =  gridsize;//Initailisation avec la taille par defaut
    char cheminFichier[256];
    printf("\n");
    printf("Veuillez entrez votre le nom du joueur:\n");
    scanf("%49s", nomjoueur);
        while(!quitter){
        printf("Bienvenue chers %s Veuillez effectuer votre choix\n", nomjoueur);
        printf("=========================================================Notre menu:=================================================================\n");
        printf("\nPress 1 pour choisir un theme\n");
        printf("\nPress 2 pour ajouter un theme\n");
        printf("\nPress 3 pour la taille de la grille\n");
        printf("\nPress 4 pour quitter le jeu\n");
        scanf("%d", &choix);

        switch(choix){
            system("cls");
            case 1:{
                system("cls");
                printf("\n*================================================*Veuillez effectuer votre choix*=====================================================*\n");
                int Themechoisi;
                char *Theme[] = {"Animaux", "Pays", "Sport", "Fruit"};//Definir un pointeur de tableau
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
                int quitter_jeu = CommencerJeu(Theme[Themechoisi - 1], gridsize, gridsize, nomjoueur);//Appel de la fonction commencerjeu pour la lancer la partie
                if(quitter_jeu){
                    printf("\nRetour au menu principal...\n");
                    Sleep(1500);
                }
                break;
            }
            case 2:{
                //printf("Bonjour\n");
                Listemots nouvelles_listes;
                ajouterTheme(NULL, &nouvelles_listes);
                break;
            }
            case 3:{
                changertaillegrille(NULL, &lignes, &colonnes);
                printf("La taille de la grille: %dx%d", lignes, colonnes);
                //Definir un theme apres avoir defini la taille de la grille
                system("cls");
                printf("\n*===================================================*Veuillez effectuer votre choix*================================================================*\n");
                int Themechoisi;
                char *Theme[] = {"Animaux", "Pays", "Sport", "Fruit"};//Definir un pointeur de tableau
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
                snprintf(cheminFichier, sizeof(cheminFichier), "%s%s", chemin_base, Theme[Themechoisi - 1]);
                int quitter_jeu =  CommencerJeu(Theme[Themechoisi - 1], lignes, colonnes, nomjoueur);//Appel de la fonction commencerjeu pour la lancer la partie
                if (quitter_jeu) {
                    printf("\nRetour au menu principal...\n");
                }
                break;
            }
                //printf("La taille que vous avez choisie: %dx%d", taillesize, taillesize);
            case 4:
                if (quitter) {
                    printf("Au revoir chers utilisateur !\n");
                    return 0;
                } else {
                    quitter = 1;
                    printf("Appuyez de nouveau sur 4 pour quitter totalement.\n");
                }
                break;
            default:
                printf("Vous n'avez effectuez aucun choix");
                break;
        }
        }

    return 0;
}
