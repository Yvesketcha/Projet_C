#ifndef MOTS_H_INCLUDED
#define MOTS_H_INCLUDED

#define max_words 5
#define max_words_len 10

typedef struct{
    mot char[max_words_len];
    int trouve;// 1 trouve, 0 pas encore trouve
}Mot;

typedef struct{
    Mot liste[max_words];
    int nbmots;
}Listemots;

chargerMotsDepuisFichier(const char *Animaux, ListeMots *liste);

#endif // MOTS_H_INCLUDED
