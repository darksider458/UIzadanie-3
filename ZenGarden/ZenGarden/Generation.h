


#ifndef _GENERATION_H_
#define _GENERATION_H_


#include<vector>
#include<math.h>
#include"Monk.h"
#include"Map.h"
#include<stdlib.h>
#include<algorithm>
using namespace std;
class Generation
{
protected:
	vector<Monk> population;
	int generation;
	int population_size;

public:
	Generation();
	~Generation();
	void fillGeneration(int size, int generation,Map map);
	vector<Monk> gethumanity();
	vector<Monk> selection1(vector<Monk> population); //tournament
	vector<Monk> selection2(double T, vector<Monk> population); // truncation
	vector<Monk> crossover(vector<Monk> matingpool,int size,Map map);
	void hrabanie(Map map, Monk *gardener);
	void addgeneration(int size, int generation, Map map, vector<Monk> humanity);
	int getbestfitness(vector<Monk> pop);
	int avgfitness(vector<Monk> pop);
	vector<Monk> crossover(vector<Monk> matingpool, int size, Map map,double mutation);
};

#endif
