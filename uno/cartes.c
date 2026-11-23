#include "cartes.h";
#include "joueurs.h";

int nbCartesPioche = 108;
char (*pioche)[TAILLE_CARTE] = NULL;    
char (*defausse)[TAILLE_CARTE] = NULL;  
int nbCartesDefausse = 0;
char couleurActive = ' ';   

/*
* Tableau dynamique du tableau statique Cartes
*/
int initialiserPioche() {
    pioche = malloc(108 * TAILLE_CARTE);
    defausse = malloc(108 * TAILLE_CARTE);
    if (pioche == NULL || defausse == NULL) {
        printf("ERREUR : allocation de la pioche impossible\n");
        return 0;
    }
    for (int i = 0; i < 108; i++) {
        strcpy_s(pioche[i], TAILLE_CARTE, cartes[i]);
    }
    nbCartesPioche = 108;
    nbCartesDefausse = 0;
    return 1;
}

int piocheUneCarte(int borneMin, int borneMax) {
    int rd_num = rand() % (borneMax - borneMin + 1) ;
    printf("%d ", rd_num);
    return rd_num;
}

/*
* donner au joueur la carte qui se trouve à 'indice' ( random ) dans la pioche, et la retirer de la pioche
* [carte1, carte2, carte3, carte4,carte5]
* joueur choisit de piocher mais derrière on fait un random car l'ordre de la pioche compte pas et car on se base sur le tableau rangé de cartes
* joueur pioche index 1 par ex
* [carte1, VIDE , carte3, carte4,carte5]
* dans le tableau pioche on remplace le trou par la derniere carte 
* [carte1, carte5, carte3, carte4, RIEN]
* ducoup on enleve 1 du nb total de la pioche
*/
void recupererCarte(int joueur, int indice) {
    ajouterCarte(joueur, pioche[indice]);
    strcpy_s(pioche[indice], TAILLE_CARTE, pioche[nbCartesPioche - 1]);
    nbCartesPioche--;
}

char* adresseCarte(int joueur, int index) {
    return mainsJoueurs[joueur] + index * TAILLE_CARTE;
}

int indexValide(int joueur, int index) {
    return index >= 0 && index < nbCartes[joueur];
}

void retirerCarte(int joueur, int index) {
    if (!indexValide(joueur, index)) {
        printf("Index invalide !\n");
        return;
    }
    refermerLeVide(joueur, index);
    nbCartes[joueur]--;
}

/*
* Quand on pose une carte a patir de notre deck, il y a un vide , donc on décale toutes les cartes a partir de cet index pour fermer le trou
* la dst c'est l adresse i de la carte du joueur , et la carte qu on veut y mettre c'est la carte prochaine ( ca decale un par un )
* [carte1, cartePOsée , carte3, carte4,carte5]
* [carte1, carte3 , vide , carte4,carte5]
* [carte1, carte3 , carte4 , vide ,carte5]
* [carte1, carte3 , carte4 , carte5 , vide]
*/
void refermerLeVide(int joueur, int index) {
    for (int i = index; i < nbCartes[joueur] - 1; i++) {
        strcpy_s(adresseCarte(joueur, i), TAILLE_CARTE, adresseCarte(joueur, i + 1));
    }
}

/*
* La fonction sert à quand on distribue mais aussi quand on pioche car on peut choisir le 'count' des cartes qu'on veut donner
*/
void distribution(int joueur, int count) {
    for (int i = 0; i < count; i++) {
        if (nbCartesPioche <= 0) {
            printf("Le paquet est vide !\n");
            return;
        }
        int indice = piocheUneCarte(0, nbCartesPioche - 1);
        recupererCarte(joueur, indice);
    }
}

/*
* % nbCartesPioche recadre le nombre dans l'intervalle, unsigned char pour specifier que si jamais le char depasse 127
* on prednd pas la partie negative
* tant que le premier caractère d'une carte n'est pas un chiffre on ne pose pas la carte, le jeu doit commencer par une carte normale
*/
void demarrerDefausse() {
    int indice = rand() % nbCartesPioche;
    while (!isdigit((unsigned char)pioche[indice][0])) {
        indice = rand() % nbCartesPioche;
    }

    poserSurDefausse(pioche[indice]);
    couleurActive = couleurCarte(pioche[indice]);
    strcpy_s(pioche[indice], TAILLE_CARTE, pioche[nbCartesPioche - 1]);
    nbCartesPioche--;
}

void poserSurDefausse(char* carte) {
    strcpy_s(defausse[nbCartesDefausse], TAILLE_CARTE, carte);
    nbCartesDefausse++;
}

char* carteDuDessus() {
    if (nbCartesDefausse == 0) return NULL;
    return defausse[nbCartesDefausse - 1];
}

void libererPioche() {
    free(pioche);
    free(defausse);
}



/*
* "7 V" mais en mémoire: [7, ,V,/0]
*/
char couleurCarte(char* carte) {
    return carte[strlen(carte) - 1];
}

int estJoker(char* carte) {
    return couleurCarte(carte) == 'N';
}

/*
* Regarde uniquement la longueur avant l'espace de la carte ( pour savoir si le nb est egal a l autre nb )
*/
int longueurValeur(char* carte) {
    int i = 0;
    while (carte[i] != ' ' && carte[i] != '\0') {
        i++;
    }
    return i;
}

/*
* Verifie que la chaine a et la chaine b sont identiques avec strncmp qui compare chaine a , chaine b et nb de char a comparer 
*/
int memeValeur(char* a, char* b) {
    int longueurA = longueurValeur(a);
    int longueurB = longueurValeur(b);
    if (longueurA != longueurB) {
        return 0;
    }

    return strncmp(a, b, longueurA) == 0;
}

int verifierCartePosee(char* carteJoueur, char* cartePile, char couleurAttendue) {
    int cartesAPiocher = nbCartesAPiocher(cartePile);
    printf("Tu dois prendre %d cartes!", cartesAPiocher);

    if (estJoker(carteJoueur)) return 1;
    if (couleurCarte(carteJoueur) == couleurAttendue) return 1;
    if (memeValeur(carteJoueur, cartePile)) return 1;
    return 0;
}

/*
* verifie si la valeur avant l'espace c'est un +2 ou +4 , ça nous permet de savoir combien le joueur d'après doit poser de cartes
*/
int nbCartesAPiocher(char* carteDansFausse) {
    int nbAPiocher = 0;
    if (carteDansFausse[0] == '+' && carteDansFausse[1] == '2') {
        nbAPiocher = 2;
    }
    if (carteDansFausse[0] == '+' && carteDansFausse[1] == '4') {
        nbAPiocher = 4;
    }

    return nbAPiocher;
}

/*
* avec le scanf on met 1 car c'est la taille du tampon ( correspond a la taille d'un char ) il faut lui donner la taille  sinon buffer overflow
* Elle convertit la lettre en majuscule
*/
char demanderCouleur() {
    char c;
    printf("Quelle couleur choisissez-vous ? (R, V, B, J) : ");
    scanf_s(" %c", &c, 1);
    c = toupper(c);

    while (c != 'R' && c != 'V' && c != 'B' && c != 'J') {
        printf("Couleur invalide. Choisissez R, V, B ou J : ");
        scanf_s(" %c", &c, 1);
        c = toupper(c);
    }
    return c;
}


char cartes[108][5] = {
    // Cartes rouges
    "0 R", "1 R", "1 R", "2 R", "2 R",
    "3 R", "3 R", "4 R", "4 R", "5 R",
    "5 R", "6 R", "6 R", "7 R", "7 R",
    "8 R", "8 R", "9 R", "9 R",

    //  vertes
    "0 V", "1 V", "1 V", "2 V", "2 V",
    "3 V", "3 V", "4 V", "4 V", "5 V",
    "5 V", "6 V", "6 V", "7 V", "7 V",
    "8 V", "8 V", "9 V", "9 V",

    //  jaunes
    "0 J", "1 J", "1 J", "2 J", "2 J",
    "3 J", "3 J", "4 J", "4 J", "5 J",
    "5 J", "6 J", "6 J", "7 J", "7 J",
    "8 J", "8 J", "9 J", "9 J",

    //  bleues
    "0 B", "1 B", "1 B", "2 B", "2 B",
    "3 B", "3 B", "4 B", "4 B", "5 B",
    "5 B", "6 B", "6 B", "7 B", "7 B",
    "8 B", "8 B", "9 B", "9 B",

    // Cartes +2
    "+2 R", "+2 R", "+2 V", "+2 V",
    "+2 J", "+2 J", "+2 B", "+2 B",

    // Cartes Inversion
    "RV R", "RV R", "RV V", "RV V",
    "RV J", "RV J", "RV B", "RV B",

    // Cartes Passer son tour
    "PS R", "PS R", "PS V", "PS V",
    "PS J", "PS J", "PS B", "PS B",

    // Jokers
    "JJ N", "JJ N", "JJ N", "JJ N",

    // Super Jokers +4
    "+4 N", "+4 N", "+4 N", "+4 N"
};