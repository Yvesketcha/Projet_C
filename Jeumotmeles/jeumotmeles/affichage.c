#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "affichage.h"
#include "grille.h"
#include "mots.h"
#include "saisir.h"
#define decal 20
#define decala 5
#define chemin_base "C:\\Cours\\ProgrammationC\\Jeumotmeles\\jeumotmeles\\Theme\\" //pour definir le chemin ou on va recuperer nos fichiers

void CouleurMotGrille(int couleurDuTexte, int couleurDeFond) //fonction d'affichage de couleur
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
    /*WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;*/
}

// Afficher la grille dans la console
void LireGrille(Grille *g, struct point *curseur, struct point *start, struct point *end, Listemots *listes, int *score, int temps_restant)
{
    system("cls");

    printf("Temps restant: %d:%02d\n", temps_restant / 60, temps_restant%60);
    printf("Votre score actuel: %d points\n\n", *score);

    printf("*----------------------------------*\n");
    printf("| %2d mots à rechercher dans la grille |\n", listes->nbmots);
    printf("*----------------------------------*\n\n");

    int max_lignes = g->lignes > listes->nbmots ? g->lignes : listes->nbmots;

    // Affichage des lignes en parallèle
    for (int i = 0; i < max_lignes; i++)
    {
        // Partie gauche : mot à rechercher
        if (i < listes->nbmots && !listes->liste[i].trouve)
        {
            printf("- %-20s", listes->liste[i].mot); // mots non trouvés
        }
        else
        {
            printf("                      "); // espace vide pour alignement
        }

        printf("    "); // séparation entre mots et grille

        // Partie droite : grille
        if (i < g->lignes)
        {
            for (int j = 0; j < g->colonnes; j++)
            {
                if (i == curseur->x && j == curseur->y){
                    CouleurMotGrille(12, 0);
                }
                else if (g->grille[i][j].lettretrouve){
                    CouleurMotGrille(10, 0);
                }
                else if (g->grille[i][j].lettreselectionne){
                    CouleurMotGrille(14, 0);
                }
                else if ((i + j) % 2 == 0){
                    CouleurMotGrille(0, 8);
                }
                else{
                    CouleurMotGrille(0, 5);
                }

                printf("%c ", g->grille[i][j].lettre);
                CouleurMotGrille(15, 0);
            }
        }

        printf("\n");
    }

    printf("\n\n");
    printf("*----------------------------------*\n");
    printf("| %2d Mots trouves                  |\n", listes->nbmots);
    printf("*----------------------------------*\n");

    for (int i = 0; i < listes->nbmots; i++)
    {
        if (listes->liste[i].trouve)
        {
            printf("- %s\n", listes->liste[i].mot);
        }
    }

    printf("\n");
}
/*void LireGrille(Grille *g, struct point *curseur, struct point *start, struct point *end, Listemots *listes, int *score, int temps_restant)
{
    system("cls");
    for(int i = 0; i < g->lignes; i++)
    {
        for(int k = 0; k < decalage; k++) printf(" ");

        for(int j = 0; j < g->colonnes; j++)
        {
            if(i == curseur->x && j == curseur->y){
                CouleurMotGrille(12,0);//curseur rouge vif
            }
            else if(g->grille[i][j].lettretrouve){
                CouleurMotGrille(10,0);//vert pour la lettre trouvee
            }
            else if(g->grille[i][j].lettreselectionne){
                CouleurMotGrille(14,0);//jaune pour la lettre selectionnee
            }
            else if((i + j)%2 == 0){
                CouleurMotGrille(0,8);//Fond gris
            }
            else{
                CouleurMotGrille(0,5);//Fond violet clair
            }
            printf("%c ", g->grille[i][j].lettre);
            CouleurMotGrille(15,0);//Reinitialise la couleur
        }

        printf("\n");
    }
    printf("\n");

    printf("Temps restant: %d:%02d\n", temps_restant / 60, temps_restant%60);
    printf("Votre score actuel: %d points\n", *score);
    int mots_restants = 0;
    for (int i = 0; i < listes->nbmots; i++) {
        if (!listes->liste[i].trouve) mots_restants++;
    }

    printf("*------------------------------------------------*\n");
    printf("|"); for(int l = 0; l < decala; l++) printf(" "); printf("%d mots à rechercher dans la grille\n", mots_restants); printf("|");
    printf("*------------------------------------------------*\n");
    for (int i = 0; i < listes->nbmots; i++) {
        if (!listes->liste[i].trouve) {
            printf("- %-20s\n", listes->liste[i].mot);
        }
        else{
            printf("    ");
        }
        printf("  ");
    }
    printf("\n");
    int mots_trouves = listes->nbmots - mots_restants;
    printf("\n");

    printf("*------------------------------------------------*\n");
    printf("|"); for(int l = 0; l < decal; l++) printf(" "); printf("%d Mots trouves\n", mots_trouves);
    printf("*------------------------------------------------*\n");
    for (int i = 0; i < listes->nbmots; i++) {
        if (listes->liste[i].trouve) {
            printf("- %s\n", listes->liste[i].mot);
        }
    }
    printf("\n");
}*/

void enreigistrerscore(char *nomjoueur, int score){//Fonction permettant d'enreigistrer les scores des joueurs
    FILE *fscore = fopen("score.txt", "a");

    if(fscore == NULL){
        printf("Erreur lors de l'ouverture du fichier score.txt");
        return;
    }

    fprintf(fscore, "%s a obtenu : %d points\n", nomjoueur, score);
    fclose(fscore);
}



















/* HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE);
 WORD wOldColorAttrs;
 CONSOLE_SCREEN_BUFFER_INFO csbiInfo;



 GetConsoleScreenBufferInfo(h, &csbiInfo);
 wOldColorAttrs = csbiInfo.wAttributes;

 //Definie la nouvelle information de couleur

 SetConsoleTextAttribute ( h, color[i][j] );


 //Retrouve la couleur originale
 SetConsoleTextAttribute ( h, wOldColorAttrs);

 int color[colorsize][colorsize];*/


