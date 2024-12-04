#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include "Cellule.h"
#include "Fichier.h"
using namespace std;

class JeuDeLaVie
{
private:
	int rows, cols;
	vector<vector<Cellule>> grille;
	int generation;

	const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	string FichierEntree;
	string DossierSortie;

public:
	JeuDeLaVie(int rows, int cols, string nomFichier);
	int getGeneration();
	void setCelluleVivante(int row, int col);
	void afficherGrille();
	void calculerProchaineGeneration();
	void executer(int generations);
	void chargerDepuisFichier(Fichier& fichier);
	void dessinerAvecSFML(int tailleCellule);
	void enregistrerGeneration();
};

