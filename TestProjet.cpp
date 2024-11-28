#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Cellule {
private:
    bool vivante; // État de la cellule
    int voisinsVivants; // Nombre de voisins vivants

public:
    // Constructeur
    Cellule() : vivante(false), voisinsVivants(0) {}

    // Méthodes pour accéder et modifier l'état
    bool estVivante() const { return vivante; }
    void setVivante(bool etat) { vivante = etat; }

    // Méthodes pour gérer les voisins vivants
    void incrementerVoisins() { ++voisinsVivants; }
    void reinitialiserVoisins() { voisinsVivants = 0; }
    int getVoisinsVivants() const { return voisinsVivants; }

    // Calcul de l'état futur
    bool calculerProchainEtat() const {
        if (vivante) {
            return (voisinsVivants == 2 || voisinsVivants == 3);
        }
        else {
            return (voisinsVivants == 3);
        }
    }
};

class JeuDeLaVie {
private:
    int rows, cols;
    vector<vector<Cellule>> grille;

    const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

public:
    JeuDeLaVie(int rows, int cols) : rows(rows), cols(cols) {
        grille.resize(rows, vector<Cellule>(cols));
    }

    // Définit une cellule vivante
    void setCelluleVivante(int row, int col) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            grille[row][col].setVivante(true);
        }
    }

    // Affiche la grille
    void afficherGrille() const {
        for (const auto& ligne : grille) {
            for (const auto& cellule : ligne) {
                cout << (cellule.estVivante() ? 'O' : '.') << ' ';
            }
            cout << '\n';
        }
        cout << string(20, '-') << '\n';
    }

    // Calcul de la prochaine génération
    void calculerProchaineGeneration() {
        // Réinitialise les voisins vivants
        for (auto& ligne : grille) {
            for (auto& cellule : ligne) {
                cellule.reinitialiserVoisins();
            }
        }

        // Notification des voisins
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grille[i][j].estVivante()) {
                    for (int k = 0; k < 8; ++k) {
                        int ni = i + dx[k], nj = j + dy[k];
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            grille[ni][nj].incrementerVoisins();
                        }
                    }
                }
            }
        }

        // Calcul des nouveaux états
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                bool prochainEtat = grille[i][j].calculerProchainEtat();
                grille[i][j].setVivante(prochainEtat);
            }
        }
    }

    // Exécution du jeu pour plusieurs générations
    void executer(int generations) {
        for (int g = 0; g < generations; ++g) {
            cout << "Generation " << g << ":\n";
            afficherGrille();
            calculerProchaineGeneration();
        }
    }
};

class Fichier {
private:
    string nomFichier;
public:
    Fichier() : nomFichier("Entree.txt") {}
    Fichier(string nom) : nomFichier(nom) {}
    string lecture() {
        ifstream monFlux(nomFichier);
        string mot;
        if (monFlux) {
            getline(monFlux, mot);
        }
        else {
            cout << "ERREUR: Impossible de lire le contenu du fichier." << endl;
        }
        return mot;
    }
    
     
};


int main() {
    Fichier fichier("Entree.txt");



    JeuDeLaVie jeu(10, 10);

    // Configuration initiale (Glider)
    jeu.setCelluleVivante(4, 3);
    jeu.setCelluleVivante(4, 4);
    jeu.setCelluleVivante(4, 5);
    jeu.setCelluleVivante(5, 5);
    jeu.setCelluleVivante(6, 4);



    // Exécution pour  générations
    jeu.executer(30);

    return 0;
}
