#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern char cartes[108][5];
extern int nbCartesPioche;

int piocheUneCarte(int borneMin, int borneMax);
void retirerCarte(int joueur, int index);
void recupererCarte(int joueur, int indice);
void distribution(int joueur, int count);
