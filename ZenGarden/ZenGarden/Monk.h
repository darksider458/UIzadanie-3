


#ifndef _MONK_H_
#define _MONK_H_

//============
//includes
//============



#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;

class Monk
{
public:
	enum Movement
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	int rakked_fields;
protected:
	Map garden;
	vector<int> starting_pozitions;		//genes
	
	int generation;
	Movement prefered;
	int y, x;
	Movement direction;
	
public:
	Monk();
	
	Monk(Map map,int generation);
	Monk(vector<int> genome, int generation ,Map map);  // cross over
	~Monk();
	void generategenes();
	bool operator<( Monk& other)  { return getfitness() > other.getfitness(); };
	void printgenes();
	int getfitness();
	int getY();
	void setY(int y);
	int getX();
	void setX(int x);
	vector<int> getstarts();
	bool isinside();
	bool isedge();
	void setdirection(int i);
	void setdirection(Movement move);
	Movement getdirection();
	vector<Movement> lookaround(vector< vector<int> > map);
	Movement getprefrered();
	Map getmap();
	void setmap(vector< vector<int> > map);
	void generatefitness();
};

#endif // !_MONK_H_