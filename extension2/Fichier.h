#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;

class Fichier {
private:
    string nomFichier;

public:
    explicit Fichier(const string& nomFichier);

    void lireGrille(int& rows, int& cols, vector<vector<int>>& grille);

    string getNomFichier();
};

