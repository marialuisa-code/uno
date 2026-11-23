#include "play.h"
#include "cartes.h";
#include "joueurs.h"

int poseAutorisee(int joueur, int index) {
	if (!indexValide(joueur, index)) {
		printf("Index invalide !\n");
		return 0;
	}
	if (!verifierCartePosee(adresseCarte(joueur, index), carteDuDessus(), couleurActive)) {
		printf("Cette carte ne peut pas être posée !\n");
		return 0;
	}
	return 1;
}

void majCouleurActive(char* carte) {
	if (estJoker(carte)) {
		couleurActive = demanderCouleur();
	}
	else {
		couleurActive = couleurCarte(carte);
	}
}

void poserSurPile(int joueur, char* carte) {
	printf("Le joueur %d pose : %s\n", joueur + 1, carte);
	poserSurDefausse(carte);
}

int poserCarte(int joueur, int index) {
	if (!poseAutorisee(joueur, index)) {
		return 0;
	}

	char* carte = adresseCarte(joueur, index);

	poserSurPile(joueur, carte);
	majCouleurActive(carte);
	retirerCarte(joueur, index);   
	return 1;
}

void afficherTour(int joueur) {
	printf("\nCarte du dessus : %s (couleur active : %c)\n", carteDuDessus(), couleurActive);
	afficherCartes(joueur);
}

int demanderChoix(int joueur) {
	int choix;
	printf("Carte à jouer (1 à %d) ou 0 pour piocher : ", nbCartes[joueur]);
	scanf_s("%d", &choix);
	return choix;
}

int veutJouerCartePiochee() {
	int veutJouer;
	printf("Voulez-vous la jouer ? (1 pour oui, 0 pour non) : ");
	scanf_s("%d", &veutJouer);
	return veutJouer == 1;
}

int piocherEtProposer(int joueur) {
	int avant = nbCartes[joueur];
	distribution(joueur, 1);
	if (nbCartes[joueur] == avant) {
		return 0;   
	}

	int dernier = nbCartes[joueur] - 1;
	char* carte = adresseCarte(joueur, dernier);
	printf("\nVous avez pioché : %s\n", carte);

	if (!verifierCartePosee(carte, carteDuDessus(), couleurActive)) {
		printf("Elle n'est pas jouable, vous passez votre tour.\n");
		return 0;
	}
	if (veutJouerCartePiochee()) {
		return poserCarte(joueur, dernier);
	}
	return 0;
}

int jouerUneCarte(int joueur) {
	afficherTour(joueur);
	while (1) {
		int choix = demanderChoix(joueur);

		if (choix == 0) {
			return piocherEtProposer(joueur);
		}
		if (poserCarte(joueur, choix - 1)) {
			return 1;
		}
	}
}