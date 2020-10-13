// senses.cpp
// Christian Rouhana 2020

// senses.cc

using namespace std;
#include <iostream>

#include "senses.h"

senses::senses ()
{
	Stench = false;
	Breeze = false;
	Glitter = false;
}

senses::senses (bool stench, bool breeze, bool glitter)
{
	Stench = stench;
	Breeze = breeze;
	Glitter = glitter;
}

senses::senses (const senses& senses)
{
	Stench = senses.Stench;
	Breeze = senses.Breeze;
	Glitter = glitter;
}

senses& senses::operator= (const senses& senses)
{
	if (this == &senses)
	{
		return *this;
	}
	Stench = senses.Stench;
	Breeze = senses.Breeze;
	Glitter = senses.Glitter;
	return *this;
}

void senses::SetSense (bool stench, bool breeze,  bool glitter);
{
	Stench = stench;
	Breeze = breeze;
	Glitter = glitter;
}

void sense::Print()
{
	if (Stench)
		cout << "You smell something dreadful nearby..." << endl;
	else
		cout << "Smells like wet cave." << endl;
	
	if (Breeze)
		cout << "You feel a breeze from nearby..." << endl;
	else
		cout << "The air is still." << endl;

	if (Glitter)
		cout << "You see something shimmering nearby..." << endl;
}