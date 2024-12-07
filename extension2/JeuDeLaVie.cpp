#include "JeuDeLaVie.h"

JeuDeLaVie::JeuDeLaVie(int rows, int cols, string nomFichier, bool obstaclesVivants)
    : rows(rows), cols(cols), FichierEntree(nomFichier), generation(0), obstaclesVivants(obstaclesVivants) {
    grille.resize(rows, vector<Cellule>(cols));
}

int JeuDeLaVie::getGeneration() {
    return generation;
}

void JeuDeLaVie::setCelluleVivante(int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        grille[row][col].setVivante(true);
    }
}

//!!!!!!!!!!!!!!!!!!!!
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
    bool grilleChangee = false;

    // Réinitialiser compteur vivants voisins
    for (auto& ligne : grille) {
        for (auto& cellule : ligne) {
            cellule.reinitialiserVoisins();
        }
    }
    // Calcul des voisins vivants
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grille[i][j].estVivante()) {
                for (int k = 0; k < 8; ++k) {
                    int ni = (i + dx[k] + rows) % rows; //Modulo pour gérer la bordure de grille
                    int nj = (j + dy[k] + cols) % cols;
                    grille[ni][nj].incrementerVoisins();
                }
            }
        }
    }
    // Calcul futur état de chaque cellule en fcontion de ses voisins
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            bool prochainEtat = grille[i][j].calculerProchainEtat();
            if (grille[i][j].estVivante() != prochainEtat) { // Vérifie si l'état de la grille à bien changé
                grilleChangee = true;
            }
            grille[i][j].setVivante(prochainEtat);
        }
    }
    // Arrêt simulation si l'état de la grille n'a pas changé 
    if (!grilleChangee) {
        cout << "Plus d'?volution : la simulation s'arr?te ? la g?n?ration " << generation << ".\n";
        exit(0);
    }
    enregistrerGeneration();
    generation++;
}

// !!!!!!!!!Affiche la grille et le nombre de la génération actuelle dans la console 
void JeuDeLaVie::executer(int generations) {
    for (int g = 0; g < generations; ++g) {
        cout << "Generation " << g << ":\n";
        afficherGrille();
        calculerProchaineGeneration();
    }
}
// Charger la grille depuis un fichier, la redimensionner et définir comme morte ou vivante les cellules
void JeuDeLaVie::chargerDepuisFichier(Fichier& fichier) {
    vector<vector<int>> grilleTemp;
    fichier.lireGrille(rows, cols, grilleTemp);

    grille.resize(rows, vector<Cellule>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grilleTemp[i][j] == 1) {
                grille[i][j].setVivante(true); // Cellule vibvante
            }
            else if (grilleTemp[i][j] == 2) {
                grille[i][j].setObstacle(true);
                grille[i][j].setVivante(obstaclesVivants);// Cellule obstacle
            }
            else {
                grille[i][j].setVivante(false); // Cellule morte
            }
        }
    }
}

void JeuDeLaVie::dessinerAvecSFML(int tailleCellule) {
    sf::RenderWindow window(sf::VideoMode(cols * tailleCellule, rows * tailleCellule), "Jeu de la Vie");

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        cerr << "Erreur : Impossible de charger la police DejaVu Sans." << endl;
        return;
    }


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                calculerProchaineGeneration();
            }
        }

        text.setString("Generation: " + to_string(generation));

        window.clear();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::RectangleShape cellule(sf::Vector2f(tailleCellule, tailleCellule));
                cellule.setPosition(j * tailleCellule, i * tailleCellule);

                if (grille[i][j].estObstacle()) {
                    cellule.setFillColor(sf::Color::Blue); 
                }
                else if (grille[i][j].estVivante()) {
                    cellule.setFillColor(sf::Color::Magenta); 
                }
                else {
                    cellule.setFillColor(sf::Color::White);
                }

                window.draw(cellule);
            }
        }

        window.draw(text);

        window.display();
    }
}

void JeuDeLaVie::enregistrerGeneration() {
    size_t pos = FichierEntree.find_last_of('.');
    string nomSansExtension = FichierEntree.substr(0, pos);
    string dossierSortie = nomSansExtension + "_out";

    if (mkdir(dossierSortie.c_str(), 0777) != 0 && errno != EEXIST) {
        cerr << "Erreur : Impossible de cr?er le dossier " << dossierSortie << endl;
        return;
    }

    string cheminFichier = dossierSortie + "/Generation_" + to_string(generation) + ".txt";

    ofstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible de cr?er le fichier " << cheminFichier << endl;
        return;
    }

    fichier << rows << " " << cols << "\n";

    for (auto& ligne : grille) {
        for (auto& cellule : ligne) {
            fichier << (cellule.estVivante() ? "1" : "0") << " ";
        }
        fichier << "\n";
    }

    fichier.close();
    cout << "G?n?ration " << generation << " sauvegard?e dans " << cheminFichier << "\n";
}