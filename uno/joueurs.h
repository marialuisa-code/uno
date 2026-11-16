#pragma once
#include <stdio.h>

#define TAILLE_CARTE        5   
#define CAPACITE_INITIALE_CARTES   7  

extern char** mainsJoueurs;
extern int* nbCartes;
extern int* capaciteCartes;

int demanderNbJoueurs();
void initialiserJoueurs(int nbJoueurs);
int initialiserUnJoueur(int joueur);
int mainPleine(int joueur);
int agrandirMain(int joueur);
void ecrireCarte(int joueur, char* carte);
int allouerTableaux(int nbJoueurs);
void distribution(int joueur, int count);
void ajouterCarte(int joueur, char* carte);

void afficherCartes(int joueur);