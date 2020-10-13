// Location.cpp
// Christian Rouhana 2020

// Location.cc

#include "Location.h"

using namespace std;

Location::Location ()
{
	row = 0;
	col = 0;
}

Location::Location (int row, int col)
{
	this -> row = row;
	this -> col = col;
}
	
Location::Location (const Location& location)
{
	row = location.row;
	col = location.col;
}

Location& Location::operator= (const Location& location)
{
	if (this == &location)
	{
		return *this;
	}
	col = location.col;
	row = location.row;
	return *this;
}

bool Location::operator== (const Location& location) const
{
	return (this -> row == location.row && this -> col == location.col);
}

bool Location::operator!= (const Location& location) const
{
	return (this -> row != location.row or this -> col != location.col);
}

bool Location::Adjacent ( Location location ) 
{
	return ((this -> row == location.row and this -> col == location.col) or (this -> row + 1 == location.row and this -> col == location.col)
		or (this -> row == location.row and this -> col + 1 == location.col) or (this -> row + 1 == location.row and this -> col + 1 == location.col)
		or (this -> row - 1 == location.row and this -> col == location.col) or (this -> row == location.row and this -> col - 1 == location.col)
		or (this -> row - 1 == location.row and this -> col - 1 == location.col));
}

void Location::move(char d)
{ 
	if (d == 'i' and this -> row != 0)
		row--;
	if (d == 'k' and this -> row != 4)
		row++;
	if (d == 'j' and this -> col != 0)
		col--;
	if (d == 'l' and this -> col != 4)
		col++;
	
	// cout << "NEW LOCATION: " << row << ", " << col << endl;
}

