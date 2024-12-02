#include "Cellule.h"

Cellule::Cellule() : vivante(false), voisinsVivants(0){}

bool Cellule::estVivante() {
	return vivante;
}

void Cellule::setVivante(bool etat) {
	vivante = etat;
}

void Cellule::incrementerVoisins() {
	voisinsVivants++;
}

void Cellule::reinitialiserVoisins() {
	voisinsVivants = 0;
}

int Cellule::getVoisinsVivants() {
	return voisinsVivants;
}

bool Cellule::calculerProchainEtat() {
	if (vivante) {
		return(voisinsVivants == 2 || voisinsVivants == 3);
	}
	else {
		return (voisinsVivants == 3);
	}
}