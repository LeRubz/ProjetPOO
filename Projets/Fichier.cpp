#include "Fichier.h"

Fichier::Fichier(const string& nomFichier) : nomFichier(nomFichier) {}

void Fichier::lireGrille(int& rows, int& cols, vector<vector<int>>& grille) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier : " + nomFichier);
    }

    fichier >> rows >> cols;

    grille.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fichier >> grille[i][j];
        }
    }

    fichier.close();
}

string Fichier::getNomFichier() {
    return nomFichier;
}
