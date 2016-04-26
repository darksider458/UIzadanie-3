


#include "Monk.h"
#include<math.h>


Monk::Monk()
{

}
Monk::Monk(Map map, int generation)
{
	this->garden = map;
	this->generation = generation;
	generategenes();
	this->rakked_fields = 0;
	if (this->starting_pozitions[starting_pozitions.size() - 1] == 1)
	{
		prefered = this->RIGHT;
	}
	else if (this->starting_pozitions[starting_pozitions.size() - 1] == 2)
	{
		prefered = this->LEFT;
	}
	
}

Monk::Monk(vector<int> genenome,int generation,Map map)
{
	this->starting_pozitions = genenome;
	this->generation = generation;
	this->garden = map;
	this->rakked_fields = 0;
	if (this->starting_pozitions[starting_pozitions.size() - 1] == 1)
	{
		prefered = this->RIGHT;
	}
	else if (this->starting_pozitions[starting_pozitions.size() - 1] == 2)
	{
		prefered = this->LEFT;
	}
}

Monk::~Monk()
{
}

void Monk::generategenes()
{
	this->garden.calculatestones();
	this->garden.generatestartingpoints();
	vector<int> map = this->garden.getstarts();
	int genesize = this->garden.getwidth() + this->garden.getheight() + this->garden.getstonecount();
	this->starting_pozitions.resize(genesize);
	int selectedgene;
	for (int i = 0; i < genesize-1; i++)
	{
		selectedgene = (rand() % genesize);
		this->starting_pozitions[i] = map[selectedgene];
		//this->starting_pozitions[i] = 0;
	}
	starting_pozitions[genesize - 1] = ((rand() % 2) + 1);//prefered direction
	//starting_pozitions[genesize - 1] = 2;
}

void Monk::printgenes()
{
	for (int i = 0; i < this->starting_pozitions.size();i++)
	{
		cout << "["<<starting_pozitions[i]<<"] ";
	}
}
int Monk::getfitness()
{
	return this->rakked_fields;
}

int Monk::getY()
{
	return this->y;
}

int Monk::getX()
{
	return this->x;
}
vector<int> Monk::getstarts()
{
	return this->starting_pozitions;
}
void Monk::setY(int y)
{
	this->y = y;
}
void Monk::setX(int x)
{
	this->x = x;
}
bool Monk::isinside()
{
	if ((this->x >= this->garden.getwidth()) || (this->y >= this->garden.getheight()) || (this->x < 0) || (this->y < 0))
	{
		return false;
	}
	return true;
}
void Monk::setdirection(int i)
{
	if (i >= 0 && i < this->garden.getwidth())
	{
		this->direction = DOWN;
	}
	else if (i >= this->garden.getwidth() && (i < this->garden.getwidth() + this->garden.getheight()))
	{
		this->direction = LEFT;
	}
	else if (i >=(this->garden.getwidth() + this->garden.getheight()) && (i < 2*this->garden.getwidth() + this->garden.getheight()))
	{
		this->direction = UP;
	}
	else if (i >= (2*this->garden.getwidth()+this->garden.getheight()) && (i < 2*this->garden.getwidth() + 2*this->garden.getheight()))
	{
		this->direction = RIGHT;
	}
}
void Monk::setdirection(Monk::Movement move)
{
	this->direction = move;
}
Monk::Movement Monk::getdirection()
{
	return this->direction;
}

Monk::Movement Monk::getprefrered()
{
	return this->prefered;
}

vector<Monk::Movement> Monk::lookaround(vector< vector<int> > map)
{
	vector<Monk::Movement> available;
	
	int i = 0;
	if (this->direction == this->DOWN || this->direction==this->UP)
	{
		if (this->isinside())
		{
			
			if (x != 0)
			{
				if (map[this->y][this->x - 1] == 0)
				{
					available.resize(i + 1);
					available[i]=(Monk::RIGHT);
					i++;
				}
			}
			if (x != this->garden.getwidth()-1)
			{
				if (map[this->y][this->x + 1] == 0)
				{
					available.resize(i+1);
					available[i]=(Monk::LEFT);
					i++;
				}
			}
		}
	}
	else if (this->direction == this->RIGHT || this->direction==this->LEFT)
	{
		if (this->isinside())
		{
		
			if (y != 0)
			{
				if (map[this->y - 1][this->x] == 0)
				{
					available.resize(i + 1);
					available[i] = (Monk::UP);
					i++;
				}
			}
			if (y != this->garden.getheight()-1)
			{
				if (map[this->y + 1][this->x] == 0)
				{
					available.resize(i + 1);
					available[i] = (Monk::DOWN);
					i++;
				}
			}
		}
	}

	return available;
}
bool Monk::isedge()
{
	if (this->x == 0 || this - y == 0)
	{
		return true;
	}
	return false;
}
Map Monk::getmap()
{
	return this->garden;
}

void Monk::setmap(vector< vector<int> > map)
{
	this->garden.setmap(map);
}
void Monk::generatefitness()
{
	for (int i = 0; i < this->garden.getheight(); i++)
	{
		for (int k = 0; k < this->garden.getwidth(); k++)
		{
			if (garden.getmap()[i][k]>0)
			{
				rakked_fields++;
			}
		}
	}
}