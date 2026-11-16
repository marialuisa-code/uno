#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joueurs.h"

char** mainsJoueurs = NULL;
int* nbCartes = NULL;
int* capaciteCartes = NULL;

int allouerTableaux(int nbJoueurs) {
    mainsJoueurs = calloc(nbJoueurs, sizeof(char*));
    nbCartes = calloc(nbJoueurs, sizeof(int));
    capaciteCartes = calloc(nbJoueurs, sizeof(int));

    return mainsJoueurs != NULL
        && nbCartes != NULL
        && capaciteCartes != NULL;
}

int initialiserUnJoueur(int joueur) {
    capaciteCartes[joueur] = CAPACITE_INITIALE_CARTES;
    nbCartes[joueur] = 0;
    mainsJoueurs[joueur] = malloc(CAPACITE_INITIALE_CARTES * TAILLE_CARTE);

    return mainsJoueurs[joueur] != NULL;
}

void initialiserJoueurs(int nbJoueurs) {
    if (!allouerTableaux(nbJoueurs)) {
        printf("ERREUR : allocation des tableaux impossible\n");
        return;
    }

    for (int i = 0; i < nbJoueurs; i++) {
        if (!initialiserUnJoueur(i)) {
            printf("ERREUR : allocation du joueur %d impossible\n", i + 1);
            return;
        }
        printf("Joueur %d initialisé !\n", i + 1);
    }

    printf("Tous les joueurs sont initialisés !\n");
}

int demanderNbJoueurs() {
	int nbJoueurs;
	printf("Entrez le nombre de joueurs de la partie uno: ");
	scanf_s("%d", &nbJoueurs);
	printf("Il y a, %d Joueurs!", nbJoueurs);
	return nbJoueurs;
}

void ajouterCarte(int joueur, char* carte) {
    if (mainPleine(joueur) && !agrandirMain(joueur)) {
        printf("Erreur d'allocation mémoire !\n");
        return;
    }
    ecrireCarte(joueur, carte);
}

int mainPleine(int joueur) {
    return nbCartes[joueur] == capaciteCartes[joueur];
}

int agrandirMain(int joueur) {
    int nouvelleCapacite = capaciteCartes[joueur] * 2;
    char* temp = realloc(mainsJoueurs[joueur], nouvelleCapacite * TAILLE_CARTE);
    if (temp == NULL) {
        return 0;
    }
    mainsJoueurs[joueur] = temp;
    capaciteCartes[joueur] = nouvelleCapacite;
    return 1;
}

void ecrireCarte(int joueur, char* carte) {
    char* placeLibre = mainsJoueurs[joueur] + nbCartes[joueur] * TAILLE_CARTE;
    strcpy_s(placeLibre, TAILLE_CARTE, carte);
    nbCartes[joueur]++;
}

void afficherCartes(int joueur) {
    printf("\nCartes du joueur %d :\n", joueur + 1);
    for (int i = 0; i < nbCartes[joueur]; i++) {
        printf("Carte %d : %s\n",
            i + 1,
            mainsJoueurs[joueur] + (i * 5)
        );
    }
}