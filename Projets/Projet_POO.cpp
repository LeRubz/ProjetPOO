#include "JeuDeLaVie.h"
#include "Fichier.h"
#include <iostream>

using namespace std;

int main() {
    string nomFichier;
    string nomDossier;
    cout << "Donnez le nom du fichier d'entrée :" << endl;
    cin >> nomFichier;
    try {
        Fichier fichier(nomFichier);
        JeuDeLaVie jeu(0, 0, nomFichier);
        jeu.chargerDepuisFichier(fichier);

        jeu.dessinerAvecSFML(5);
    }
    catch (const exception& e) {
        cerr << "Erreur : " << e.what() << '\n';
    }

    return 0;
}
