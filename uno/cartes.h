#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern char cartes[108][5];
extern int nbCartesPioche;
extern char couleurActive;


int piocheUneCarte(int borneMin, int borneMax);
void retirerCarte(int joueur, int index);
char* adresseCarte(int joueur, int index);
int indexValide(int joueur, int index);
void refermerLeVide(int joueur, int index);
void recupererCarte(int joueur, int indice);
void distribution(int joueur, int count);

int initialiserPioche();
void poserSurDefausse(char* carte);
char* carteDuDessus();
void libererPioche();

char couleurCarte(char* carte);
int estJoker(char* carte);
int longueurValeur(char* carte);
int memeValeur(char* a, char* b);
int verifierCartePosee(char* carteJoueur, char* cartePile, char couleurAttendue);
int nbCartesAPiocher(char* carteDansFausse);
char demanderCouleur();
void demarrerDefausse();

