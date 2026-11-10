#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joueurs.h"

char** mainsJoueurs = NULL;
int* nbCartes = NULL;
int* capaciteCartes = NULL;

int demanderNbJoueurs() {
	int nbJoueurs;
	printf("Entrez le nombre de joueurs de la partie uno: ");
	scanf_s("%d", &nbJoueurs);
	printf("Il y a, %d Joueurs!", nbJoueurs);
	return nbJoueurs;
}

void initialiserJoueurs(int nbJoueurs) {
    mainsJoueurs = calloc(nbJoueurs, sizeof(char*));
    nbCartes = calloc(nbJoueurs, sizeof(int));
    capaciteCartes = calloc(nbJoueurs, sizeof(int));

    if (mainsJoueurs == NULL ||
        nbCartes == NULL ||
        capaciteCartes == NULL) {
        printf("ERREUR ALLOCATION PRINCIPALE\n");
        return;
    }

    for (int i = 0; i < nbJoueurs; i++) {
        fflush(stdout);

        capaciteCartes[i] = 7;

        mainsJoueurs[i] = malloc(35);

        if (mainsJoueurs[i] == NULL) {
            printf("ERREUR allocation joueur %d\n", i + 1);
            return;
        }

        nbCartes[i] = 0;

        printf("Joueur %d initialise !\n", i + 1);
    }

    printf("TOUS LES JOUEURS SONT INITIALISES !\n");
}

void ajouterCarte(int joueur, const char* carte) {

    if (nbCartes[joueur] == capaciteCartes[joueur]) {

        int nouvelleCapacite = capaciteCartes[joueur] * 2;
        char* temp = realloc(
            mainsJoueurs[joueur],
            nouvelleCapacite * sizeof(char[5])
        );
        if (temp == NULL) {
            printf("Erreur d'allocation mémoire !\n");
            return;
        }

        mainsJoueurs[joueur] = temp;
        capaciteCartes[joueur] = nouvelleCapacite;
    }

    strcpy_s(
        mainsJoueurs[joueur] + nbCartes[joueur] * 5,
        5,
        carte
    );

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