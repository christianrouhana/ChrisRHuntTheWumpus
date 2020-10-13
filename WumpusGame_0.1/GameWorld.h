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


#include "Location.h"
#include "senses.h" 

class GameWorld
{
	private:
		int gameBoard[5][5];
		
		Location userLocation;
		std::list<Location> pitLocations;
		Location wumpusLocation;
		Location goldLocation;
		bool wumpusDead;
		bool victory;
		bool userDead;
		//bool hasArrow; 
		//bool hasGold; 
		//senses playerSenses;

	public:
    	GameWorld();
	
    	void displayEntireWorld();
		void displayVisibleWorld();
		void move( char d );
		bool haveIWon();
		bool amIAlive();
		bool listContains(std::list<Location> __list, Location obj);
		//void shootArrow();
		//void checkSenses();
		// void printArrayDEBUG();
};
 
#endif