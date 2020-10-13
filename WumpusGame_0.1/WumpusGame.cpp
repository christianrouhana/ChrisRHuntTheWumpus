// WumpusGame.cpp
// Christian Rouhana 2020

#include "WumpusGame.h"

using namespace std;

double gameVersion = 0.1;
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
			score = score - 10;
			gameWorld.displayVisibleWorld();
		}
		else if (userMove == 'c')
		{
			score = score - 50;
			gameWorld.displayEntireWorld();
		}
		else if (userMove == 'r')
		{
			cout << "Restarting game with same player, generating world..." << endl;
			gameWorld.Generate();
			score = 0;
		}
		else if (userMove == 'n')
		{
			cout << "Restarting game with new player, generating world..." << endl;
			playerName = intro();
			gameWorld.Generate();
			score = 0;
		}
		else if (userMove == 'q')
		{
			quit = true;
			break;
		}
		else if (userMove == 's')
		{
			if (gameWorld.userHasArrow())
			{
				gameWorld.shootArrow();
				if (!gameWorld.wumpusAlive())
				{
					score += 500;
				}
			}
			else
			{
				cout << "You don't have an arrow anymore" << endl;
			}
		}
		else if (userMove == 'x')
		{
			if (gameWorld.climb())
			{
				cout << "You escaped!";
				break;
			}
			else 
			{
				cout << "You can't climb. Either you need to get to the starting point, fetch the gold, or both!";
			}
		}
		else if (userMove == 'i' or userMove == 'k' or userMove == 'j' or userMove == 'l')
		{
			gameWorld.move(userMove);
			if (gameWorld.JustGotGold())
				score += 200;
			if (gameWorld.amIAlive())
				score += 20;
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
	cout << "Welcome to Christian's Hunt the Wumpus Version " << gameVersion << endl;

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
	cout << "s or S will shoot an arrow \n";
	cout << "x or X will climb if you are back at the starting position and have the gold \n";
	cout << "v or V will display the world as well as any game elements adjacent to your location \n";
	cout << "c or C will activate a cheat code! You will see the entire world state \n";
	cout << "r or R will restart the game while keeping your player name \n";
	cout << "n or N will restart the game and allow for a new user to play \n";
	cout << "q or Q to quit \n";

	cout << "Your score starts at 0,every turn that you stay alive you gain 20 points \n"; 
	cout << "Every time you use v or V, you get -10 points \n";
	cout <<	"Every time you use c or C, you get -50 points \n";
	cout << "Killing the wumpus grants you 500 points! \n";
	cout << "Getting the gold gives you 200 points! \n";
	cout << "You will lose if you die by being eaten by the Wumpus or falling into a pit. \n";
	cout << "You will win by getting the gold, getting back to your starting point, and climbing!! \n";
	cout << "Winning scores you 500 points! \n";
	cout << "Losting gives you -500 points ): \n";
	cout << "That is all the instructions. Have fun!";
	cout << endl;
}