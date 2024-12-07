#include "Cellule.h"

Cellule::Cellule() : vivante(false), obstacle(false), voisinsVivants(0){}

bool Cellule::estVivante() {
	return vivante;
}

void Cellule::setVivante(bool etat) {
	vivante = etat;
}
bool Cellule::estObstacle() {
	return obstacle;
}

void Cellule::setObstacle(bool etat) {
	obstacle = etat;
	if (obstacle) {
		vivante = false;
	}
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

