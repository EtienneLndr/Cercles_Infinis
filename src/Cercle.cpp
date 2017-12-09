#include "Cercle.h"


Cercle::Cercle(int _x, int _y, int l, int h, int r, int v, int b, int _radius, int _dt): Forme(_x, _y, l, h, Couleur(r, v, b)), radius(_radius), dt(_dt) {
}


Cercle::~Cercle() {
}


void Cercle::dessine(sf::RenderWindow *win) {
	int red, green, blue;
  	couleur.getRVB(red, green, blue);
  	sf::CircleShape shape(radius);
  	shape.setFillColor(sf::Color(red, green, blue));
  	shape.setPosition(x - difference, y - difference);
	win->draw(shape);
}

void Cercle::animate() {
	radius += dt;
	difference += dt;
}