#pragma once
class Cellule
{
private:
	bool vivante;
	bool obstacle;
	int voisinsVivants;
public:
	Cellule();
	bool estVivante();
	void setVivante(bool etat);
	bool estObstacle();
	void setObstacle(bool etat);
	void incrementerVoisins();
	void reinitialiserVoisins();
	int getVoisinsVivants();
	bool calculerProchainEtat();
};
