#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grille.h"
#include "mots.h"

int main()
{

    char nom[50];
    int choix;
    printf("\n");
    printf("Veuillez entrez votre le nom du joueur:\n");
    scanf("%s", nom);
    printf("Bienvenue chers %s Veuillez effectuer votre choix\n", nom);
    printf("Notre menu:\n");
    printf("\nPress 1 pour les animaux");
    printf("\nPress 2 pour les pays");
    scanf("%d", &choix);
    return 0;
}
