#ifndef PONG_H
#define PONG_H 1
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "Cercle.h"

using namespace std;
using namespace std::chrono;

class Case;

class Pong {
	
	public: 
		int execute();
		
		Pong(string n = "Window", int w = 400, int h = 400);
		~Pong();
		
		Cercle* getCercle(int i);
		void addCercle(Cercle * a);
		
	private:
		string _name;
    	int _width, _height;
    	sf::RenderWindow *_win;
		vector<Cercle*> cercle;
		
		int limite;
		int dt 					= 1;
		int random_value = 0;
		int state_of_random_value = 0;
		int center_x;
		int center_y;
		bool pause 				= false;
		bool mouseButtonPressed = false;
		
		void animateCircles();
		void drawAll(sf::RenderWindow * win);
		void verifyIfCircleNotTooLong();
	
	};
		
		
inline Cercle* Pong::getCercle(int i) { return cercle[i]; }
inline void Pong::addCercle(Cercle * a) { cercle.push_back(a); }


#endif