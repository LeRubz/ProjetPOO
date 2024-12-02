#include "JeuDeLaVie.h"

JeuDeLaVie::JeuDeLaVie(int rows, int cols) : rows(rows), cols(cols) {
    grille.resize(rows, vector<Cellule>(cols));
}

void JeuDeLaVie::setCelluleVivante(int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        grille[row][col].setVivante(true);
    }
}

void JeuDeLaVie::afficherGrille() {
    for (auto& ligne : grille) {
        for (auto& cellule : ligne) {
            cout << (cellule.estVivante() ? 'O' : '.') << ' ';
        }
        cout << '\n';
    }
    cout << string(20, '-') << '\n';
}

void JeuDeLaVie::calculerProchaineGeneration() {
    for (auto& ligne : grille) {
        for (auto& cellule : ligne) {
            cellule.reinitialiserVoisins();
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grille[i][j].estVivante()) {
                for (int k = 0; k < 8; ++k) {
                    int ni = (i + dx[k] + rows) % rows;
                    int nj = (j + dy[k] + cols) % cols;
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        grille[ni][nj].incrementerVoisins();
                    }
                }
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            bool prochainEtat = grille[i][j].calculerProchainEtat();
            grille[i][j].setVivante(prochainEtat);
        }
    }
}

void JeuDeLaVie::executer(int generations) {
    for (int g = 0; g < generations; ++g) {
        cout << "Generation " << g << ":\n";
        afficherGrille();
        calculerProchaineGeneration();
    }
}

void JeuDeLaVie::chargerDepuisFichier(Fichier& fichier) {
    vector<vector<int>> grilleTemp;
    fichier.lireGrille(rows, cols, grilleTemp);

    grille.resize(rows, vector<Cellule>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grille[i][j].setVivante(grilleTemp[i][j] == 1);
        }
    }
}

void JeuDeLaVie::dessinerAvecSFML(int tailleCellule) {
    sf::RenderWindow window(sf::VideoMode(cols * tailleCellule, rows * tailleCellule), "Jeu de la Vie");

    // Boucle principale du jeu
    while (window.isOpen()) {
        sf::Event event;

        // Traiter tous les événements
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Si l'utilisateur appuie sur la touche espace, on passe à la génération suivante
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                calculerProchaineGeneration();  // Calculer la génération suivante
            }
        }

        // Affichage de la grille
        window.clear();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::RectangleShape cellule(sf::Vector2f(tailleCellule, tailleCellule));
                cellule.setPosition(j * tailleCellule, i * tailleCellule);

                if (grille[i][j].estVivante()) {
                    cellule.setFillColor(sf::Color::Magenta); // Cellule vivante en vert
                }
                else {
                    cellule.setFillColor(sf::Color::White); // Cellule morte en blanc
                }

                window.draw(cellule);
            }
        }

        window.display();  // Affiche la fenêtre avec les nouvelles cellules
    }
}
