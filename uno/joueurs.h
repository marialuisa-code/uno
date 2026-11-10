#pragma once
#include <stdio.h>

extern char** mainsJoueurs;
extern int* nbCartes;
extern int* capaciteCartes;

int demanderNbJoueurs();
void initialiserJoueurs(int nbJoueurs);
void distribution(int joueur, int count);
void ajouterCarte(int joueur, const char* carte);

void afficherCartes(int joueur);