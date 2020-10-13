// senses.h
#ifndef SENSES_H
#define SENSES_H

#include <vector>

using namespace std;

class senses {
	private:
		bool Stench;
		bool Breeze;
		bool Glitter;
		bool Bump;
	
	public:
		senses ();
		senses ();
		senses (bool stench, bool breeze, bool glitter, bool bump);
		senses (const senses& senses);
		senses& operator= (const senses& senses);
		void SetSenses (bool stench, bool breeze, bool glitter, bool bump);
		void Print();
};

#endif