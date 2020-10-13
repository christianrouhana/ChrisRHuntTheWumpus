// WumpusGame.cpp
// Christian Rouhana 2020

#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include "WumpusGame.h"

using namespace std;

string intro();
void instructions();

int main () 
{ 
	string playerName = intro();
	cout << "Beginning game..." << endl;

	GameWorld gameWorld;
	int score = 0;
	
	bool quit = false;
	while (true)
	{
		char userMove;
		cout << "Score: " << score << "\nEnter your next move: ";
		cin >> userMove;
		userMove = tolower(userMove);

		if (userMove == 'v')
		{
			score = score - 2;
			gameWorld.displayVisibleWorld();
		}
		else if (userMove == 'c')
		{
			score = score - 5;
			gameWorld.displayEntireWorld();
		}
		else if (userMove == 'r')
		{
			cout << "restarting game with same player..." << endl;
			GameWorld gameWorld;
			score = 0;
		}
		else if (userMove == 'n')
		{
			cout << "restarting game with new player..." << endl;
			playerName = intro();
			GameWorld gameWorld;
			score = 0;
		}
		else if (userMove == 'q')
		{
			quit = true;
			break;
		}
		else if (userMove == 'i' or userMove == 'k' or userMove == 'j' or userMove == 'l')
		{
			gameWorld.move(userMove);
			score = score + 5; 
		}
		else
			cout << "input not recognized!" << endl;
		
		if (gameWorld.haveIWon() or !gameWorld.amIAlive() or quit)
			break;
	}

	if (quit)
	{
		cout << "Quit selected." << endl;
	}
	else if (gameWorld.haveIWon())
	{
		score += 500;
		cout << "YOU WIN!" << endl;
	}
	else if (!gameWorld.amIAlive())
	{
		score -= 500;
		cout << "YOU LOSE" << endl;
	}
	
	cout << "FINAL SCORE: " << score << endl;
	cout << "Score saved to \"GameScore.txt\"" << endl;
	ofstream myfile;
	myfile.open ("GameScore.txt");
	myfile << "Player: " << playerName << "\nScore: " << score;
	myfile.close();
	return 0; 
}

string intro()
{
	cout << "Welcome to Christian's Hunt the Wumpus Version " << endl;

	string playerName;
	cout << "Please enter your name: ";
	cin >> playerName;
	cout << "Your name is " << playerName << "... get ready to play!" << endl;

	cout << "Generating game world..." << endl;

	cout << "Would you like instructions on how to play? [y/n] ";
	bool acceptedInput = false;
	char instruct;
	while (!acceptedInput)
	{
		cin >> instruct;
		instruct = tolower(instruct);
		if (instruct == 'y' or instruct == 'n')
		{
			acceptedInput = true;
		}
		else 
		{
			cout << "Sorry! I didn't recognize your input. Please enter only y or n [Yes or No respectively]" << endl;
			cout << "Would you like instructions on how to play? [y/n] ";
		}
	}

	if (instruct == 'y')
		instructions();

	return playerName;
}

void instructions()
{
	cout << "i or I will move the player UP \n";
	cout << "k or K will move the player DOWN \n";
	cout << "j or J will move the player LEFT \n";
	cout << "l or L will move the player RIGHT \n";
	cout << "v or V will display the world as well as any game elements adjacent to your location \n";
	cout << "c or C will activate a cheat code! You will see the entire world state \n";
	cout << "r or R will restart the game while keeping your player name \n";
	cout << "n or N will restart the game and allow for a new user to play \n";
	cout << "q or Q to quit \n";

	cout << "Your score starts at 0,every move that you stay alive you gain 5 points \n"; 
	cout << "Every time you use v or V, you get -2 points \n";
	cout <<	"Every time you use c or C, you get -5 points \n";
	cout << "You will lose if you die by being eaten by the Wumpus or falling into a pit. \n";
	cout << "You will win by getting the gold! \n";
	cout << "Winning scores you 500 points! \n";
	cout << "Losting gives you -500 points ): \n";
	cout << "That is all the instructions. Have fun!";
	cout << endl;
}