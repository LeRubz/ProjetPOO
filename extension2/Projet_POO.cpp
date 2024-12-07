#include "JeuDeLaVie.h"
#include "Fichier.h"
#include <iostream>

using namespace std;

int main() {
    string nomFichier;
    bool obstaclesVivants; 
    cout << "Donnez le nom du fichier d'entrée :" << endl;
    cin >> nomFichier;

    cout << "Les cellules obstacles doivent-elles être vivantes ? (1 pour Oui, 0 pour Non) : " << endl;
    cin >> obstaclesVivants; 

    try {
        Fichier fichier(nomFichier);
        JeuDeLaVie jeu(0, 0, nomFichier, obstaclesVivants);
        jeu.chargerDepuisFichier(fichier);

        jeu.dessinerAvecSFML(5);
    }
    catch (const exception& e) {
        cerr << "Erreur : " << e.what() << '\n';
    }

    return 0;
}
