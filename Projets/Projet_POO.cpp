#include "JeuDeLaVie.h"
#include "Fichier.h"
#include <iostream>

using namespace std;

int main() {
    try {
        Fichier fichier("grille.txt");
        JeuDeLaVie jeu(0, 0);
        jeu.chargerDepuisFichier(fichier);

        jeu.dessinerAvecSFML(5);
    }
    catch (const exception& e) {
        cerr << "Erreur : " << e.what() << '\n';
    }

    return 0;
}
