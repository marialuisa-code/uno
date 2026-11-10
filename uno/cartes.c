#include "cartes.h";
#include "joueurs.h";

int nbCartesPioche = 108;

int piocheUneCarte(int borneMin, int borneMax) {
    int rd_num = rand() % (borneMax - borneMin + 1) + borneMin;
    printf("%d ", rd_num);
    return rd_num;
}

void recupererCarte(int joueur, int indice) {
    ajouterCarte(joueur, cartes[indice]);
    strcpy_s(cartes[indice], 5, cartes[nbCartesPioche - 1]);
    nbCartesPioche--;
}

int* retirerCarte(int* tableau, int* size, int index) {
    if (index < 0 || index >= *size) {
        printf("Invalid index.\n");
        return tableau;
    }

    // Shift elements left
    for (int i = index; i < *size - 1; i++) {
        tableau[i] = tableau[i + 1];
    }

    (*size)--;

    // Resize memory
    int* newArr = realloc(tableau, (*size) * sizeof(int));
    if (!newArr && *size > 0) {
        printf("Memory reallocation failed.\n");
        return tableau; // Keep old array if realloc fails
    }

    return newArr;
}


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

char cartes[108][5] = {
    // Cartes rouges
    "0 R", "1 R", "1 R", "2 R", "2 R",
    "3 R", "3 R", "4 R", "4 R", "5 R",
    "5 R", "6 R", "6 R", "7 R", "7 R",
    "8 R", "8 R", "9 R", "9 R",

    // Cartes vertes
    "0 V", "1 V", "1 V", "2 V", "2 V",
    "3 V", "3 V", "4 V", "4 V", "5 V",
    "5 V", "6 V", "6 V", "7 V", "7 V",
    "8 V", "8 V", "9 V", "9 V",

    // Cartes jaunes
    "0 J", "1 J", "1 J", "2 J", "2 J",
    "3 J", "3 J", "4 J", "4 J", "5 J",
    "5 J", "6 J", "6 J", "7 J", "7 J",
    "8 J", "8 J", "9 J", "9 J",

    // Cartes bleues
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