#include<iostream>
#include"Generation.h"
#include<math.h>
#include<ctime>
using namespace std;


int main()
{
	double mutation_chance;
	srand(time(NULL));
	int mode;
	int selection;
	int population_size;
	int generation, generation_limit=20;
	double mutation=0.1;
	int widht, height, stones;
	while (true)
	{
		cout << "select mode " << endl << "1:default " << endl << "2:custom " << endl << "3 :exit" << endl;
		cin >> mode;
		cout << "you choose [" << mode << "] " << endl;
		if (mode == 1)
		{

			population_size = 150;
			cout << "select selection " << "1:tournament " << "2:truncation " << endl;
			cin >> selection;
			cout << "selection [" << selection << "] " << endl;
			double treshold;
			cout << "if 2 selected enter treshold" << endl;
			cin >> treshold;
			generation = 1;
			Map map = Map();
			cout << "your map" << endl;
			map.printmap();
			cout << endl;
			map.generatestartingpoints();
			Generation humanity = Generation();
			humanity.fillGeneration(population_size, generation, map);
			int max = map.max();
			vector<Monk> first = humanity.gethumanity();
			vector<Monk> matingpool;
			vector<Monk> next_generation;
			cout << "maximun number of rakked fields possible" << max << endl;
			for (int i = 0; i < first.size(); i++)
			{
				humanity.hrabanie(map, &first[i]);
			}
			for (int i = 0; i < first.size(); i++)
			{
				first[i].generatefitness();
			}
			if (humanity.getbestfitness(first) == max)
			{
				sort(first.begin(), first.end());
				first[0].getmap().printmap();
				break;
			}
			while (generation <= generation_limit)
			{
				generation++;

				cout << "max : " << humanity.getbestfitness(first) << " avg: " << humanity.avgfitness(first) << endl;
				if (selection == 1)
				{
					matingpool = humanity.selection1(first);
					next_generation = humanity.crossover(matingpool, matingpool.size(), map, mutation);
					humanity.addgeneration(population_size, generation, map, next_generation);
				}
				else if (selection == 2)
				{

					matingpool = humanity.selection2(treshold, first);
					next_generation = humanity.crossover(matingpool, matingpool.size(), map, mutation);
					humanity.addgeneration(population_size, generation, map, next_generation);

				}
				first = humanity.gethumanity();
				for (int i = 0; i < first.size(); i++)
				{
					humanity.hrabanie(map, &first[i]);
				}
				for (int i = 0; i < first.size(); i++)
				{
					first[i].generatefitness();
				}
				if (humanity.getbestfitness(first) == max)
				{
					sort(first.begin(), first.end());
					first[0].getmap().printmap();
					break;
				}

				cout << generation << "finsihed" << endl;
				  
			}
			sort(first.begin(), first.end());
			first[0].getmap().printmap();

		}
		else if (mode == 2)
		{

			cout << "select selection " << "1:tournament " << "2:truncation " << endl;
			cin >> selection;
			cout << "selection [" << selection << "] " << endl;
			double treshold;
			cout << "if 2 selected enter treshold" << endl;
			cin >> treshold;
			generation = 1;
			cout << "enter population size " << endl;
			cin >> population_size;
			cout << "enter width and height and number of stones " << endl;
			cin >> widht >> height >> stones;
			cout << "enter mutation chance" << endl;
			cin >> mutation;
			cout << "Enter generation limit" << endl;
			cin >> generation_limit;
			Map map = Map(widht, height, stones);
			map.loadmap();
			map.generatestartingpoints();
			int max = map.max();
			Generation humanity = Generation();
			humanity.fillGeneration(population_size, generation, map);

			vector<Monk> first = humanity.gethumanity();
			vector<Monk> matingpool;
			vector<Monk> next_generation;
			for (int i = 0; i < first.size(); i++)
			{
				humanity.hrabanie(map, &first[i]);
			}
			cout << "firstgeneration finished " << endl;
			cout << "maximun number of rakked fields possible" << max << endl;
			for (int i = 0; i < first.size(); i++)
			{
				first[i].generatefitness();
			}
			if (humanity.getbestfitness(first) == max)
			{
				sort(first.begin(), first.end());
				first[0].getmap().printmap();
				break;
			}
			while (generation <= generation_limit)
			{
				generation++;


				cout << "max : " << humanity.getbestfitness(first) << " avg: " << humanity.avgfitness(first) << endl;
				if (selection == 1)
				{
					matingpool = humanity.selection1(first);
					next_generation = humanity.crossover(matingpool, matingpool.size(), map, mutation);
					humanity.addgeneration(population_size, generation, map, next_generation);
				}
				else if (selection == 2)
				{

					matingpool = humanity.selection2(treshold, first);
					next_generation = humanity.crossover(matingpool, matingpool.size(), map, mutation);
					humanity.addgeneration(population_size, generation, map, next_generation);

				}
				if (humanity.getbestfitness(first) == max)
				{
					sort(first.begin(), first.end());
					first[0].getmap().printmap();
					break;
				}
				first = humanity.gethumanity();
				for (int i = 0; i < first.size(); i++)
				{
					humanity.hrabanie(map, &first[i]);
				}
				for (int i = 0; i < first.size(); i++)
				{
					first[i].generatefitness();
				}

				cout << generation << "finsihed" << endl;

			}
			sort(first.begin(), first.end());
			first[0].getmap().printmap();
		}
		if (mode == 3)
		{
			return 0;
		}

	}//while end 
}