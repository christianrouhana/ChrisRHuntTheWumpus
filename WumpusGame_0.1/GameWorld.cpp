// GameWorld.cpp
// Christian Rouhana 2020


#include "GameWorld.h"

using namespace std;


GameWorld::GameWorld ( ) 
{	
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

	// wumpusDead = false;
	victory = false;
	userDead = false;
}

// if given a cheat command, the engine will display the entire world state
void GameWorld::displayEntireWorld ( )
{
	cout << "+";
	for (int i = 0; i < 5; i++)
		cout << "---+";

	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "|";
		for (int j = 0; j < 5; j++)
		{
			if (gameBoard[i, j] == 1) 
				cout << "U";
			else 
				cout << " ";

			if (gameBoard[i, j] == 2) 
				cout << "P";
			else 
				cout << " ";

			if (gameBoard[i, j] == 3) 
				cout << "G";
			else 
				cout << " ";

			if (gameBoard[i, j] == 4) 
				cout << "W";
			else 
				cout << " ";

			if (gameBoard[i, j] == 5) 
				cout << "X";
			else 
				cout << " ";

			cout << "|";
		}
		cout << endl;
	}

	cout << "+";
	for (int i = 0; i < 5; i++)
		cout << "---+";

	cout << endl;
}

// if given a noraml display command, this will display the world adjacent to the user [diagonal included]
void GameWorld::displayVisibleWorld ( )
{
	cout << "+";
	for (int i = 0; i < 5; i++)
		cout << "---+";

	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "|";
		for (int j = 0; j < 5; j++)
		{

			if (userLocation.adjacent(Location(i, j)) or Location(i,j) == userLocation)
			{
				if (gameBoard[i, j] == 1) 
					cout << "U";
				else 
					cout << " ";

				if (gameBoard[i, j] == 2) 
					cout << "P";
				else 
					cout << " ";

				if (gameBoard[i, j] == 3) 
					cout << "G";
				else 
					cout << " ";

				if (gameBoard[i, j] == 4) 
					cout << "W";
				else 
					cout << " ";

				if (gameBoard[i, j] == 5) 
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
		cout << "---+";

	cout << endl;
}

// invokes move ( char d ) method in userLocation, updates game board appropriately
void GameWorld::move( char d )
{
	Location old = userLocation;
	userLocation.move(tolower(d)); 
	gameBoard[old.row, old.col] = 0;
	if (gameBoard[userLocation.row, userLocation.col] != 2 and gameBoard[userLocation.row, userLocation.col] != 4 and gameBoard[userLocation.row, userLocation.col] != 3 )
	{
		gameBoard[userLocation.row, userLocation.col] = 1;
	}
	else // condition to end the game
	{
		if (gameBoard[userLocation.row, userLocation.col] == 3)
		{
			victory = true;
			cout << "You got the gold!\n";
		}
		else if (gameBoard[userLocation.row, userLocation.col] == 2)
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

// checks for win condition. The user will win if the user gets the gold and climbs at 1,1
bool GameWorld::haveIWon ( )
{ 
	return victory;
}

// checks for loss condition [player is slain]
bool GameWorld::amIAlive ( )
{
	return userDead;
}

// tool for checking if a list<T> contains an specified object
bool GameWorld::listContains ( std::list<Location> __list, Location obj ) 
{
	return (std::find(__list.begin(), __list.end(), obj) != __list.end());
}
