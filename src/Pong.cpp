#include "Pong.h"
#include "Constantes.h"


using namespace std;


Pong::Pong(string n, int w, int h) : _name(n), _width(w), _height(h) {
	// Création de la fenêtre de jeu
	_win = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);

	// Initialisation du pas de temps
	dt = 1;

	// Initilisation des variables permettant de définir le centre des cercles
	center_x = 1 + rand()%_width;
	center_y = 1 + rand()%_height;

	// Ajout du premier cercle
	addCercle(new Cercle(center_x,
		center_y,
		_width,
		_height,
		rand()%256,
		rand()%256,
		rand()%256,
		15,
		dt));
}


Pong::~Pong(void) {
  	// Destruction des objets graphiques
	cout << "Destruction des objets graphiques" << endl;
  	delete _win;
	for (unsigned int i=0; i<cercle.size(); i++) {
  		delete cercle[i];
	}
}


void Pong::animateCircles() {
	//cout << "Animation of every circle" << endl;

	if (state_of_random_value == random_value) {
		cout << "Création d'un nouveau cercle" << endl;
		addCercle(new Cercle(
			center_x,
			center_y,
			_width,
			_height,
			rand()%256,
			rand()%256,
			rand()%256,
			15,
			dt));
		
		state_of_random_value = 0;
		random_value = rand()%RANDOM_VALUE;
	} else {
		// Animation des cercles
		for (unsigned int i = 0; i < cercle.size(); i++) {
			cercle[i]->animate();
		}
		state_of_random_value++;
	}

	verifyIfCircleNotTooLong();
}


void Pong::drawAll(sf::RenderWindow * win) {
	// On dessine tous les objets graphiques en appelant leur fonction de dessin
	_win->clear(sf::Color(240, 240, 240));

	for (unsigned int i = 0; i < cercle.size(); i++) {
		cercle[i]->dessine(win);
	}
}


void Pong::verifyIfCircleNotTooLong() {
	for (unsigned int i = 0; i < cercle.size(); i++) {
		if ((cercle[i]->getRadius() > sqrt(pow((double)_width, 2) + pow((double)_height, 2))) && 
			(cercle[i]->getRadius() > sqrt(pow((double)_width, 2) + pow((double)_height, 2)))) {
			cout << "Supression du cercle " << i << endl;
			cercle.erase(cercle.begin() + i);
		}
	}
}


int Pong::execute(void) { 
	/**
	 * Cette fonction est l'élément clé de notre programme. Une boucle while permet
	 * de lancer indéfiniment notre programme jusqu'à ce que l'utilisateur décide de mettre
	 * fin à la partie en fermCercle la fenêtre de jeu. Dans cette boucle while on fait appel
	 * à différentes fonctions permettCercle de mettre en place notre jeu. 
	 */
	drawAll(_win);

	int timeMax = 0;
	
  	while (_win->isOpen()) {

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		
		// On déplace les fourmis
		if (!pause) {
			animateCircles();
			drawAll(_win);
		}
		
		_win->display();
		
    	sf::Event event;
    	if(_win->pollEvent(event)) {
      		switch (event.type) {
				// Fermeture de la fenêtre
      			case sf::Event::Closed:
             		_win->close();
					break;
				// Réacquisition du focus
				case sf::Event::GainedFocus:
					cout << "Focus regain" << endl;
					pause = false;
					break;
				// Perte du focus
				case sf::Event::LostFocus:
					cout << "Focus lost" << endl;
					pause = true;
					break;
             	// Si une touche du clavier est pressée:
        		case sf::Event::KeyPressed:
        			// Si c'est la touche 'echap' on met le jeu en pause
        			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        				// On met le jeu en pause --> plus aucun mouvement
        				if (!pause) pause = true;
        				else pause = false;
        			}
             		break;
             	// Si on clique avec la souris:
             	case sf::Event::MouseButtonPressed:
    				// Si c'est un clic gauche:
    				if (event.mouseButton.button == sf::Mouse::Right) {
        				/**
        				 * On teste si le clic est sur une forme à l'aide de la méthode 
        				 * cliqueSouris(int, int)
        				 */
    				} else if (event.mouseButton.button == sf::Mouse::Left && !mouseButtonPressed) {
						mouseButtonPressed = true;
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left && mouseButtonPressed) {
						mouseButtonPressed = false;
					}
        		default:
         			break;
      		}
		}

		if (mouseButtonPressed) {
			/**
			 * Récupération de la positon de la souris par rapport à la fenêtre
			 */
			sf::Vector2i globalPosition = sf::Mouse::getPosition(*_win);
			(void)globalPosition;
		}

		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		
		// Calcul de l'intervalle de temps
		auto duration = duration_cast<microseconds>( t2 - t1 ).count();
		
		if ((int)duration > timeMax) {
			timeMax = (int)duration;
			cout << "Maximum time -> " << timeMax << endl;
		}
		
    	/**
    	 * On met le programme en pause pendCercle une petite durée car sinon celui-ci est trop rapide
		 * et il plCerclee
    	 */
		usleep(15000);
	}

	return timeMax;
}