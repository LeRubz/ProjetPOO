#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cellule.h"
#include "Fichier.h"
using namespace std;

class JeuDeLaVie
{
private:
	int rows, cols;
	vector<vector<Cellule>> grille;

	const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

public:
	JeuDeLaVie(int rows, int cols);
	void setCelluleVivante(int row, int col);
	void afficherGrille();
	void calculerProchaineGeneration();
	void executer(int generations);
	void chargerDepuisFichier(Fichier& fichier);
	void dessinerAvecSFML(int tailleCellule);
};

