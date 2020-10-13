// GameWorld.cpp
// Christian Rouhana 2020


#include "GameWorld.h"

using namespace std;


GameWorld::GameWorld ( ) 
{	
	Generate( );
}

void GameWorld::Generate ( ) 
{
	while (pitLocations.empty()) //prevent pitLocations from becoming too large after many restarts
	{
		pitLocations.pop_front();
	}
	srand(time(NULL));
	/* any cell gameBoard[i][j] = {0 = EMPTY, 1 = USER, 2 = PIT, 3 = GOLD, 4 = WUMPUS} */
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 5; ++ y)
		{
			gameBoard[x][y] = 0;
		}
	}

	// create user location stored in Location(row, col)
	gameBoard[4][0] = 1;
	userLocation = Location(4, 0);

	int i = 0, j = 0;
	// generate pits
	int numPits = rand() % 5 + 5;
	for (int k = 0; k < numPits; k++) // worst case case O(numPits) but Does not always generate number of pits equal to numPits. needs improvement
	{
		i = rand() % 5;
		j = rand() % 5;

		if (userLocation != Location(i, j))
		{
			gameBoard[i][j] = 2;
			pitLocations.push_back(Location(i,j));
		}
	}

	// generate gold location. gold will never be co-located with init user location or pit
	while(Location(i,j) == userLocation or listContains(pitLocations, Location(i,j)))
	{
		i = rand() % 5;
		j = rand() % 5;
	}
	gameBoard[i][j] = 3;
	goldLocation = Location(i,j);

	// generate wumpus location. wumpus will never be co-located with init userlocation, pits, or gold
	while(Location(i,j) == goldLocation or Location(i,j) == userLocation or listContains(pitLocations, Location(i,j)))
	{
		i = rand() % 5; 
		j = rand() % 5;
	}
	gameBoard[i][j] = 4;
	wumpusLocation = Location(i,j);

	wumpusDead = false;
	victory = false;
	userDead = false;
	hasArrow = true;
	hasGold = false;
	justGotGold = false;
}

// if given a cheat command, the engine will display the entire world state
void GameWorld::displayEntireWorld ( )
{
	cout << "+";
	for (int i = 0; i < 5; i++)
		cout << "-----+";

	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "|";
		for (int j = 0; j < 5; j++)
		{
			if (gameBoard[i][j] == 1) 
				cout << "U";
			else 
				cout << " ";

			if (gameBoard[i][j] == 2) 
				cout << "P";
			else 
				cout << " ";

			if (gameBoard[i][j] == 3) 
				cout << "G";
			else 
				cout << " ";

			if (gameBoard[i][j] == 4) 
				cout << "W";
			else 
				cout << " ";

			if (gameBoard[i][j] == 5) 
				cout << "X";
			else 
				cout << " ";

			cout << "|";
		}
		cout << endl;
	}

	cout << "+";
	for (int i = 0; i < 5; i++)
		cout << "-----+";

	cout << endl;
}

// if given a noraml display command, this will display the world adjacent to the user [diagonal included]
void GameWorld::displayVisibleWorld ( )
{
	cout << "+";
	for (int i = 0; i < 5; i++)
		cout << "-----+";

	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "|";
		for (int j = 0; j < 5; j++)
		{

			if (userLocation.Adjacent(Location(i, j)) or Location(i,j) == userLocation)
			{
				if (gameBoard[i][j] == 1) 
					cout << "U";
				else 
					cout << " ";

				if (gameBoard[i][j] == 2) 
					cout << "P";
				else 
					cout << " ";

				if (gameBoard[i][j] == 3) 
					cout << "G";
				else 
					cout << " ";

				if (gameBoard[i][j] == 4) 
					cout << "W";
				else 
					cout << " ";

				if (gameBoard[i][j] == 5) 
					cout << "X";
				else 
					cout << " ";
			}
			else 
			{
				cout << "     ";
			}
		

			cout << "|";
		}
		cout << endl;
	}

	cout << "+";
	for (int i = 0; i < 5; i++)
		cout << "-----+";

	cout << endl;
}

// calls Location::move( char d ) method in userLocation, updates game board appropriately
void GameWorld::move( char d )
{
	justGotGold = false;
	Location old = userLocation;
	userLocation.move(tolower(d)); 
	gameBoard[old.row][ old.col] = 0;
	if (gameBoard[userLocation.row][ userLocation.col] != 2 and gameBoard[userLocation.row][ userLocation.col] != 4 and gameBoard[userLocation.row][ userLocation.col] != 3 )
	{
		gameBoard[userLocation.row][ userLocation.col] = 1;
	}
	else 
	{
		if (gameBoard[userLocation.row][ userLocation.col] == 3)
		{
			hasGold = true;
			justGotGold = true;
			cout << "You got the gold!\n";
			gameBoard[userLocation.row][ userLocation.col] = 1;
		}
		else if (gameBoard[userLocation.row][ userLocation.col] == 2)
		{
			userDead = true;
			cout << "You fell in a pit!\n";
		}
		else 
		{
			userDead = true;
			cout << "You were eaten by the Wumpus\n";
		}
	}
}

// quirky method to check if the user picked up the gold on their most RECENT turn
bool GameWorld::JustGotGold()
{
	return justGotGold;
}
// checks for win condition. The user will win if the user gets the gold and climbs at 1,1
bool GameWorld::haveIWon ( )
{ 
	return victory;
}

// checks for loss condition [player is slain]
bool GameWorld::amIAlive ( )
{
	return !userDead;
}

bool GameWorld::wumpusAlive ( )
{
	return !wumpusDead;
}

bool GameWorld::userHasGold ( )
{
	return hasGold;
}

bool GameWorld::userHasArrow ( )
{
	return hasArrow;
}

// user must be in the starting location and must have the gold to return true
bool GameWorld::climb ( ) 
{
	if (userLocation == Location(4, 0) and hasGold){
		victory = true;
		return true;
	}
	return false;
}

void GameWorld::shootArrow ( )
{
	char d;
	while (true)
	{
		cout << "Time to shoot! What direction are you shooting? [u:Up, d:Down, l:Left, r:Right, q:Changed your mind] ";
		cin >> d;
		int row = userLocation.row;
		int col = userLocation.col;
		if (d == 'u')
		{
			if (gameBoard[row - 1][ col] == 4)
			{
				wumpusDead = true;
				cout << "You killed the Wumpus!!!!! \n";
				gameBoard[row - 1][ col] = 0;
			}
			else
			{
				cout << "You missed.\n";
			}
			hasArrow = false;
			break;
		}
		else if (d == 'd')
		{
			if (gameBoard[row + 1][ col] == 4)
			{
				wumpusDead = true;
				cout << "You killed the Wumpus!!!!! \n";
				gameBoard[row + 1][ col] = 0;
			}
			else
			{
				cout << "You missed.\n";
			}
			hasArrow = false;
			break;
		}
		else if (d == 'l')
		{
			if (gameBoard[row][ col - 1] == 4)
			{
				wumpusDead = true;
				cout << "You killed the Wumpus!!!!! \n";
				gameBoard[row][ col - 1] = 0;
			}
			else
			{
				cout << "You missed.\n";
			}
			hasArrow = false;
			break;
		}
		else if (d == 'r')
		{
			if (gameBoard[row][ col + 1] == 4)
			{
				wumpusDead = true;
				cout << "You killed the Wumpus!!!!! \n";
				gameBoard[row][ col + 1] = 0;
			}
			else
			{
				cout << "You missed.\n";
			}
			hasArrow = false;
			break;
		}
		else if (d == 'q')
		{
			break;
		}
		else 
		{
			cout << "Sorry, I didn't understand your input. Please try again \n";
		}
	}
}

// tool for checking if a list<T> contains an specified object
bool GameWorld::listContains ( std::list<Location> __list, Location obj ) 
{
	return (std::find(__list.begin(), __list.end(), obj) != __list.end());
}

