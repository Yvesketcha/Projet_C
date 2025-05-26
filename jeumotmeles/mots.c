#include <stdio.h>
#include <stdlib.h>
#include "mots.h"

int chargerMotsDepuisFichier(const char *Animaux, ListeMots *liste) {
    FILE *f = fopen(Animaux, "r");
    if (!f) {
        perror("Erreur ouverture fichier");
        return 0;
    }

    liste->nbmots = 0;
    while (fgets(liste->liste[liste->nbmots].mot, max_words_len, f) != NULL) {
        // Supprimer le saut de ligne
        liste->liste[liste->nbmots].mot[strcspn(liste->liste[liste->nbmots].mot, "\n")] = '\0';
        liste->liste[liste->nbmots].trouve = 0;
        liste->nbmots++;
    }

    fclose(f);
    return 1;
}
