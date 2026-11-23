#include <stdio.h>
#include "cartes.h"
#include "joueurs.h"
#include "play.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));
    srand((unsigned)time(NULL));

    int nbJoueurs;
    int choix;
    int tours; 
    int uno;
    uno = 0;
    tours = 0;

    printf("================================\n");
    printf("          JEU UNO\n");
    printf("================================\n");

    printf("1. Nouvelle partie\n");
    printf("2. Quitter\n");
    printf("Votre choix : ");
    scanf_s("%d", &choix);

    switch (choix) {

    case 1:

        nbJoueurs = demanderNbJoueurs();
        initialiserJoueurs(nbJoueurs);
        if (!initialiserPioche()) {
            return 1;   
        }

        for (int i = 0; i < nbJoueurs; i++) {
            distribution(i, 7);
        }

        for (int i = 0; i < nbJoueurs; i++) {
            printf("\nCartes du joueur %d :\n", i + 1);
            afficherCartes(i);
        }

        demarrerDefausse();
        printf("\nPremière carte de la défausse : %s\n", carteDuDessus());

        while (uno == 0 ) {
            for (int i= 0; i < nbJoueurs; i++) {
                printf("\nLe joueur %d joue:\n", i + 1);
                jouerUneCarte(i);
                if (nbCartes[i] == 0) {
                    printf("Le joueur %d a gagné !\n", i + 1);
                    uno = 1;
                }
            }
            tours++;
        }
        break;

    case 2:
        printf("Au revoir !\n");
        break;

    default:
        printf("Choix invalide.\n");
        break;
    }

    return 0;
}

