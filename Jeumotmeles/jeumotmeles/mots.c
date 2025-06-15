#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mots.h"
#include "grille.h"
#define chemin_base "C:\\Cours\\ProgrammationC\\Jeumotmeles\\jeumotmeles\\Theme\\" //pour definir le chemin ou on va recuperer nos fichiers

int chargerMotsFichier(const char *Theme, Listemots *listes){
    char cheminFichier[100];
    snprintf(cheminFichier, sizeof(cheminFichier), "Theme/%s.txt", Theme);//construit le chemin vers le fichier
    FILE *file = fopen(cheminFichier, "r");
    if(!file){
        printf("Erreur ouverture fichier: %s\n", cheminFichier);
        return 0;
    }

    listes->nbmots = 0;
    while(listes->nbmots < max_words && fgets(listes->liste[listes->nbmots].mot, max_words_len, file) != NULL){
        //Supprimer le saut de ligne
        listes->liste[listes->nbmots].mot[strcspn(listes->liste[listes->nbmots].mot, "\n")]  = '\0';
        listes->liste[listes->nbmots].trouve = 0;
        listes->nbmots++;
    }
    fclose(file);
    return 1;
}

void ajouterTheme(const char *Theme, Listemots *listes){
    char nomTheme[50];
    int nbmots;
    char mot[50];
    char chemin[200];

    printf("Entrez le nom du nouveau theme: ");
    scanf("%49s", nomTheme);
    snprintf(chemin, sizeof(chemin), "%s%s.txt", chemin_base, nomTheme);

    FILE *file = fopen(chemin, "w");
    if(!file){
        printf("Erreur lors de la creation du nouveau fichier\n");
        return 1;
    }

    printf("Combien de mots voulez vous ajouter (le maximum c'est: %d)", max_words);
    scanf("%d", &nbmots);

    if(nbmots > max_words) listes->nbmots = max_words;

    listes->nbmots = nbmots;
    printf("Entrez les %d mots du theme '%s': ", nbmots, nomTheme);
    for(int i = 0; i < listes->nbmots; i++){
        printf("Mot %d: ", i + 1);
        scanf("%49s", &mot);
        strcpy(listes->liste[i].mot, mot);//copie dans la structure
        listes->liste[i].trouve = 0;
        fprintf(file, "%s\n", mot);//ecrire dans le fichier
    }
    fclose(file);
    printf("Theme '%s' ajoute avec success! \n", nomTheme);
}

int Verificationinsertionmot(char *word, Grille *g, struct point start, enum direction d) //Fonction permettant de verifier si un mot peut etre insere dans la grille dans cette position ou pas
{
    int i = 0;
    struct point new_point = start;
    while(i < (int)strlen(word))//parcourt le tableau de caractere du mot
    {
        if(new_point.x < 0 || new_point.x >= g->lignes || new_point.y < 0 || new_point.y >= g->colonnes){
            return 0;
        }

        //Tenter de deplacer le point vers le nouveau point
        char lettregrille = g->grille[new_point.x][new_point.y].lettre;
        if(lettregrille == ' ' || lettregrille == word[i])
        {
            new_point = shift_point(new_point, d);
            i++;
        }
        else{
            return 0;//Si le mot ne peut pas etre insere renvoie faux
        }
    }
      return 1;//Peut etre insere donc retourne vraie
}
