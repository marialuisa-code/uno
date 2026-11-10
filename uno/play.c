#include "play.h"
#include "cartes.h";
#include "joueurs.h"

int jouerLaCartePiochee() {

	int nb_cartePiochee = piocheUneCarte(0, 108);
	printf("La carte piochée", nb_cartePiochee);
	int veutJouerSaCarte;
	printf("Voulez-vous jouer la carte piochée? (1 pour oui et 0 pour non): ");
	scanf_s("%d", &veutJouerSaCarte);
	if (veutJouerSaCarte == 1) {
		printf("Le joueur a decidé de jouer !");
		
	}
	else {
		printf("Le joueur a decidé de passer son tour !");
	}
	return veutJouerSaCarte;
}

int jouerUneCarte(joueur) {
	int joueUneCarteDansPaquet = 0;
	afficherCartes(joueur);
	printf("Joueur %d, Voulez-vous jouer une des cartes dans votre paquet? (1 pour oui et 0 pour non): \n", joueur);

	scanf_s("%d", &joueUneCarteDansPaquet);
	if (joueUneCarteDansPaquet == 1) {
		printf("Le joueur a decidé de jouer une carte de son paquet!");
	}

	if (joueUneCarteDansPaquet == 1) {
		int indexCarte;
		printf("Choisir la carte à jouer (1, 2, 3 etc...):");
		scanf_s("%d", &indexCarte);
		printf("Le joueur joue la carte n* %d de son paquet\n", indexCarte);

	}
	else {
		jouerLaCartePiochee();
	}
	return joueUneCarteDansPaquet;
}