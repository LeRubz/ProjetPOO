#pragma once
class Cellule
{
private:
	bool vivante;
	int voisinsVivants;
public:
	Cellule();
	bool estVivante();
	void setVivante(bool etat);

	void incrementerVoisins();
	void reinitialiserVoisins();
	int getVoisinsVivants();
	bool calculerProchainEtat();
};

