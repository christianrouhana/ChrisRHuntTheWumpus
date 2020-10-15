//GameWorld.h
// Christian Rouhana 2020

#ifndef GAMEWORLD_H
#define GAMEWORLD_H
 
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <ctype.h>
#include <list>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <SFML/Audio.hpp>

#include "Location.h" 
#include "Color.hpp"

class GameWorld
{
	private:
		int gameBoard[10][10];
		
		Location userLocation;
		std::list<Location> pitLocations;
		Location wumpusLocation;
		Location goldLocation;
		bool wumpusDead;
		bool victory;
		bool userDead;
		bool hasArrow; 
		bool hasGold; 
		bool justGotGold;

		sf::SoundBuffer bufferWumpus;
		sf::Sound wumpusSound;

		sf::SoundBuffer bufferGold;
		sf::Sound goldSound;

		sf::SoundBuffer arrowBuffer;
		sf::Sound arrowSound;

		sf::SoundBuffer pitBuffer;
		sf::Sound pitSound;
		//sf::SoundBuffer bufferPit;
		//sf::SoundBuffer bufferBats;

	public:
    	GameWorld();
		void Generate( );

    	void displayEntireWorld();
		void displayVisibleWorld();
		void move( char d );
		bool JustGotGold();
		bool haveIWon();
		bool amIAlive();
		bool wumpusAlive ( );
		bool userHasGold ( );
		bool userHasArrow ( );
		bool climb ( );
		bool listContains(std::list<Location> __list, Location obj);
		void shootArrow();
};
 
#endif