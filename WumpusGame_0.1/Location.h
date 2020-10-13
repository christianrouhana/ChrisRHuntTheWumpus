// Location.h
// Christian Rouhana 2020

#ifndef LOCATION_H
#define LOCATION_H

#include <cstdlib>
#include <ctype.h>
#include <iostream>

class Location
{
public:
	Location ();
	Location (int row, int col);
	Location (const Location& location);
	bool operator==(const Location& location) const;
	bool Adjacent( Location location );
	void move(char d);

	
	int row;
	int col;
};

#endif 