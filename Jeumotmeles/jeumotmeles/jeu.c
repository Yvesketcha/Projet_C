#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "jeu.h"
#include "grille.h"
#include "mots.h"
#include "affichage.h"
#include "saisir.h"


void nettoyerselection(Grille *g)
{
    for(int i = 0; i < g->lignes; i++)
    {
        for(int j = 0; j < g->colonnes; j++)
        {
            g->grille[i][j].lettreselectionne = 0;//Reinitialise la selection temporaire a jaune
        }
    }
}

void marqueselection(Grille *g, struct point start, struct point end)//Fonction permettat de selectionner un mot
{
    //Calcul des differences de positions  entre les deux points
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    int len = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);//Determine la longueur du mot a selectionne
    //Determination des direction de deplacement en x et en y
    int x_inc = (dx == 0) ? 0 : dx / abs(dx);
    int y_inc = (dy == 0) ? 0 : dy / abs(dy);

    int x = start.x;
    int y = start.y;
    //Parcours des lettres de start a end
    for(int i = 0; i <= len; i++)
{
    //verifie que la position du mot est dans les limites de la grille
    if(x >= 0 && x < g->lignes && y >= 0 && y < g->colonnes)
        {
            g->grille[x][y].lettreselectionne = 1;//marque comme selectionne (jaune)
        }
        x += x_inc;//Avance dans la direction de x
        y += y_inc;//Avance dans la direction de y
    }
}

char *extractionmot(Grille *g, struct point start,struct point end)
{
    static char word[50];//Tableau statique de taille 50 pour retourner les mots
    int idx = 0;
    //Calcul des differences de positions  entre les deux points
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int len = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);//Determine la longueur du mot a selectionne
    int x_inc = (dx == 0) ? 0 : dx /abs(dx); //Determination des direction de deplacement en x
    int y_inc = (dy == 0) ? 0 : dy/abs(dy); //Determination des direction de deplacement en y

    int x = start.x;
    int y = start.y;
    //Parcours des lettres de start a end
    for(int i = 0; i <= len; i++)
    {
        //verifie que la position du mot est dans les limites de la grille
        if(x >= 0 && x < g->lignes && y >= 0 && y < g->colonnes)
        {
            word[idx++] = g->grille[x][y].lettre;
        }
        x += x_inc;
        y += y_inc;
    }
    word[idx] = '\0';//fin de chaine
    return word;//retourne le mot
}

void marque_valide(Grille *g, struct point start, struct point end)//Fonction permettant de marquer qu'un mot de la grille a ete valide puis colorie
{
    //Calcul des differences de positions entre les deux points
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int len = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);//Determine la longueur du mot a selectionne
    int x_inc = (dx == 0) ? 0 : dx / abs(dx);//Determination des direction de deplacement en x
    int y_inc = (dy == 0) ? 0 : dy / abs(dy);//Determination des direction de deplacement en y

    int x = start.x;
    int y = start.y;
    for(int i = 0; i <= len; i++)
{
    //verifie que la position du mot est dans les limites de la grille
    if(x >= 0 && x < g->lignes && y >= 0 && y < g->colonnes)
        {
            g->grille[x][y].lettretrouve = 1;
            g->grille[x][y].lettreselectionne = 0;
        }
        x += x_inc;//Deplacement en x
        y += y_inc;//Deplacement en y
    }
}

void marquemottrouve(Listemots *listes, char *word){//cette fonction permet de marquer un mot comme etant trouve et de mettre a jour la liste des mots
    for(int i = 0; i < listes->nbmots; i++){
        if(!listes->liste[i].trouve && strcmp(listes->liste[i].mot, word) == 0){//ici cette etape verifie si le mot est different de celui qui est trouve
            listes->liste[i].trouve = 1;
        break;
        }
    }
}

int CommencerJeu(const char *Theme, int lignes, int colonnes, const char *nomjoueur)
{
    Grille g;//Declaration de la grille principale de jeu
    Listemots listes;//Listes de mots a rechercher dans la grille
    int gameover = 0;
    struct point curseur = {0,0};//initialise le curseur a (0,0)
    struct point start = {-1,-1};//point de depart de la selection
    struct point end = {-1,-1};//point de fin de la selection
    int selection = 0;
    int score = 0; //score initial

    //masquer le curseur de texte
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hconsole, &cursorInfo);//permet de recuperer les informations actuelles du curseur de la console
    cursorInfo.bVisible = FALSE;//permet de rendre invisible le curseur de texte de la console
    SetConsoleCursorInfo(hconsole, &cursorInfo);//applique les changements rendant le curseur de texte invisible

    //initialisation des dimensions
    int ligmax = lignes;
    int colmax = colonnes;
    char cheminFichier[100];

    if(!chargerMotsFichier(Theme, &listes)) //Appel de la fonction ecriture dans la grilles depuis le fichier mots.c
    {
        printf("Erreur lors du chargement du fichier de mot: %s\n", cheminFichier);
        printf("Nombre de mots chargés : %d\n", listes.nbmots);
        return;
    }

    Grillevide(&g, lignes, colonnes);//Appel de la fonction Initialisation de la grille vide depuis le fichier grille.c
    g.lignes = lignes;
    g.colonnes = colonnes;

    for(int i = 0; i < listes.nbmots; i++)
    {
        Insertionmotgrille(listes.liste[i].mot, &g, i);//Appel de la fonction pour inserer les mots dans la grille a partir du fichier grille.c
    }

    remplissagegrille(&g);//Appel de la fonction pour le remplissage de la grille avec les lettres aleatoires depuis le fichier grille.c
    system("cls");//pour effacer l'ecran

    clock_t temps_debut = clock();
    int temps_limite = 240;//4 minutes
    int temps_restant = temps_limite;

    LireGrille(&g, &curseur, &start, &end, &listes, &score, temps_restant);//Appel de la fonction pour l'affichage de la grille
    gotoligcolcurseur(curseur.x, curseur.y + decalage);//positionner le curseur

    while(!gameover)
    {
        touche direction = liretouche();//Lire la touche
        clock_t temps_actuel = clock();
        int temps_ecoule = (int)((temps_actuel - temps_debut)/ CLOCKS_PER_SEC);
        int temps_restant = temps_limite - temps_ecoule;
        if(temps_restant <= 0){
            gameover = 1;
            system("cls");
            printf("\nLe temps restant est ecoule: GAMEOVER!!\n");
            Sleep(3000);//pour afficher le message
            break;
        }

        if(direction == TOUCHE_EXIT)
        {
             printf("\nVous avez quitté la partie. Retour au menu principal...\n");
             Sleep(1500);
             return 1; // Signale au main() de retourner au menu
        }
        else if(direction == TOUCHE_SPACE)
        {
            if(!selection)
            {
                //Debut de la selection
                start = curseur;
                selection = 1;
                if(start.x >= 0 && start.x < g.lignes && start.y >= 0 && start.y < g.colonnes){
                    g.grille[start.x][start.y].lettreselectionne = 1;//premiere lettre selectionne en jaune
                }
            }
            else
            {
                end = curseur;
                selection = 0;
                if(start.x == end.x && start.y == end.y)
                {
                    //deuxieme pression sur la lettre retour a la couleur d'origine
                    nettoyerselection(&g);
                }
                else
                {
                    nettoyerselection(&g);
                    marqueselection(&g, start, end);
                    char *selection_word = extractionmot(&g, start, end);
                    int trouve = 0;//Le mot n'est pas encore trouve
                   enum direction d = determinedirectionpoint(start, end);//Nouvelle fonction pour determiner la direction
                    for(int i = 0; i < listes.nbmots; i++){
                    if (strcmp(selection_word, listes.liste[i].mot) == 0) {
                        trouve = 1;//pour montrer que le mot est trouve
                        marquemottrouve(&listes, listes.liste[i].mot);
                        break;
                    }
                    // Vérifie aussi la version inversée
                        char reversed[50];
                        strcpy(reversed, listes.liste[i].mot);
                        my_strrev(reversed);
                        if (strcmp(selection_word, reversed) == 0) {
                            trouve = 1;
                            marquemottrouve(&listes, listes.liste[i].mot);
                            break;
                        }
                       /*if(!listes.liste[i].trouve){
                            char mot[50];
                            strcpy(mot, listes.liste[i].mot);
                           if(Verificationinsertionmot(mot, &g, start, d)){
                                trouve = 1;
                                marquemottrouve(&listes, mot);
                                break;
                            }
                            my_strrev(mot);
                            if(Verificationinsertionmot(mot, &g, start, d)){
                                trouve = 1;
                                marquemottrouve(&listes, listes.liste[i].mot);
                                break;
                            }
                       }*/
                    }
                    if(trouve){
                        score += 10;//En cas de bonne reponse ajout de 10 points
                        marque_valide(&g, start, end);
                        //Beep(1000, 100);
                        for(int i = 0; i < 3; i++){
                            Beep(1400, 200);
                        }
                    }
                    else{
                        score -= 5;//Penalite de 5 points en cas de mauvaise reponse
                        nettoyerselection(&g);
                        for(int i = 0; i < 2; i++){
                            Beep(1000, 150);
                            //Sleep(50);
                        }
                    }
                }
                start.x = -1;
                start.y = -1;
                end.x = -1;
                end.y = -1;
            }
            system("cls");
            LireGrille(&g, &curseur,&start, &end, &listes, &score, temps_restant);
            gotoligcolcurseur(curseur.x, curseur.y + decalage);
            //printf("Apres selection position curseur: (x=%d, y=%d)\n", wherex(), wherey());
        }
        else if(direction != TOUCHE_AUCUNE)
        {
            deplacementcurseur(&curseur, direction, ligmax, colmax, &gameover);//fonction pour le deplacement du curseur
            if(selection)
            {
                nettoyerselection(&g);
                marqueselection(&g, start, curseur);//surligner jusqu'au curseur
            }
            system("cls");
            LireGrille(&g, &curseur, &start, &end, &listes, &score, temps_restant);//fonction pour afficher la grille avec le curseur
            gotoligcolcurseur(curseur.x, curseur.y + decalage);//Mettre a jour la position du curseur
            //printf("Apres deplacement position curseur: (x=%d, y=%d)\n", wherex(), wherey());
        }
    }
    enreigistrerscore(nomjoueur, score);
    printf("\n%s, votre score final est : %d points\n", nomjoueur, score);
    Sleep(2000);
    return 0; // Fin normale du jeu (temps écoulé ou tous les mots trouvés)
}

enum direction determinedirectionpoint(struct point start, struct point end){
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    if(dx == -1 && dy == 0) return UP;
    if(dx == 1 && dy == 0) return DOWN;
    if(dx == 0 && dy == -1) return LEFT;
    if(dx == 0 && dy == 1) return RIGHT;
    if(dx == -1 && dy == -1) return UP_LEFT;
    if(dx == -1 && dy == 1) return UP_RIGHT;
    if(dx == 1 && dy == -1) return DOWN_LEFT;
    if(dx == 1 && dy == 1) return DOWN_RIGHT;
    //Par defaut si la direction n'est pas claire (par exemple, pas de mouvement direct, retourner right)
    return RIGHT;
};

void my_strrev(char *str) {//fonction permettant de selectionne les mots dans les deux sens etant donne que le joueur peut selectionne les mots dans les deux sens de gauche a droite ou de droite a gauche
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}
