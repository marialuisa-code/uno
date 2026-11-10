#include <stdio.h>
#include "cartes.h"
#include "joueurs.h"
#include "play.h"

int main()
{
	//me sert pour l'aléatoire
	srand(time(NULL));


    // Initialiser l'aléatoire
    srand((unsigned)time(NULL));

    int nbJoueurs;
    int choix;
    int tours; 
    int uno;
    uno = 0;
    tours = 0;

    char** mainsJoueurs = NULL;
    int* nbCartes = NULL;

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

        for (int i = 0; i < nbJoueurs; i++) {
            distribution(i, 7);
        }

        for (int i = 0; i < nbJoueurs; i++) {
            printf("\nCartes du joueur %d :\n", i + 1);
            afficherCartes(i);
        }

        while (uno == 0 ) {
            for (int i= 0; i <= nbJoueurs; i++) {
                printf("\nLe joueur %d joue:\n", i );
                jouerUneCarte(i);
            }
            tours++;
        }
        //libererJoueurs(nbJoueurs);

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

