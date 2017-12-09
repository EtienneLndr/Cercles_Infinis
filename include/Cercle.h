#ifndef CERCLE_H
#define CERCLE_H 1
#include "Forme.h"
#include <vector>


class Cercle : public Forme {
	
	public:
		void dessine(sf::RenderWindow *win);
		void animate();
		
		Cercle(int _x, int _y, int l, int h, int r, int v, int b, int _radius, int _dt);
		~Cercle();

		int getRadius();
		void setRadius(int r);
		
	protected:
		int radius;
		int dt;
		int difference = 0;
	
	};


inline int Cercle::getRadius() { return radius; }
inline void Cercle::setRadius(int r) { radius = r; }


#endif