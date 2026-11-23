#pragma once
#include <stdio.h>


int poseAutorisee(int joueur, int index);
void majCouleurActive(char* carte);
void poserSurPile(int joueur, char* carte);
int poserCarte(int joueur, int index);

void afficherTour(int joueur);
int demanderChoix(int joueur);
int veutJouerCartePiochee();
int piocherEtProposer(int joueur);
int jouerUneCarte(joueur);