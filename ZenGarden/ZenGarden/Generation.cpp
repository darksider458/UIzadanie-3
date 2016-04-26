#include "Generation.h"



Generation::Generation()
{
}


Generation::~Generation()
{
}

void Generation::fillGeneration(int size, int generation, Map map)
{
	this->population_size = size;
	this->generation = generation;
	this->population.resize(size);
	for (int i = 0; i < size; i++)
	{
		this->population[i] = Monk(map, generation);
	}
}

vector<Monk> Generation::gethumanity()
{
	return this->population;
}

vector<Monk> Generation::selection1(vector<Monk> population) //tournament
{
	vector<Monk> matingpool;
	int current_pool_filling = 0;
	matingpool.resize(this->population_size / 2);
	vector<int> used;
	Monk first_contenstance = Monk();
	Monk second_contenstance = Monk();
	int first;
	int second;
	used.resize(this->population_size);
	while (current_pool_filling < this->population_size/2)
	{
		first = ((rand() % this->population_size));
		second = ((rand() % this->population_size));
		while ((first == second) )
		{
			second = ((rand() % this->population_size));
		}
		first_contenstance = population[first];
		second_contenstance = population[second];
		if (first_contenstance.getfitness() >= second_contenstance.getfitness())
		{
			matingpool[current_pool_filling]=(first_contenstance);
			current_pool_filling++;
		}
		else
		{
			matingpool[current_pool_filling] = (second_contenstance);
			current_pool_filling++;
		}
	}
	return matingpool;

}

vector<Monk> Generation::selection2(double T, vector<Monk> population)
{
	vector<Monk> matingpool;
	vector<Monk> full = population;
	double numbers = ((double)this->population_size )* T;
	std::sort(full.begin(), full.end());
	matingpool.resize((int)numbers);
	
	for (int i = 0; i < (int)numbers; i++)
	{
		matingpool[i]=full[i];
	}
	return matingpool;
}

void Generation::hrabanie(Map map, Monk *gardener)
{
	Map povodna = map;
	vector< vector<int> > garden=map.getmap();
	vector<Monk::Movement> free;
	Monk monk = *gardener;
	Monk::Movement current_direction;
	bool set = false;
	bool game_over = false;;
	vector<int> starts = monk.getstarts();
	for (int i = 0; i < starts.size(); i++)
	{

		monk.setdirection(starts[i]);
		current_direction = monk.getdirection();
		if (current_direction == Monk::DOWN)
			{
				monk.setY(0);
				monk.setX(starts[i]);
			}
		else if (current_direction == Monk::LEFT)
			{
				monk.setY(starts[i] % povodna.getheight());
				monk.setX(0);
			}
		else if (current_direction == Monk::UP)
			{
				monk.setY(povodna.getheight()-1);
				monk.setX(starts[i] % povodna.getwidth());
			}
		else if (current_direction == Monk::RIGHT)
			{
				monk.setY(starts[i] % povodna.getheight());
				monk.setX(povodna.getwidth() - 1);
			}

		if (garden[monk.getY()][monk.getX()] == 0)
		{
			while (monk.isinside() && !game_over)
				{
					
						free.clear();
						while (current_direction == Monk::DOWN)
						{
							if (!monk.isinside())
							{
								break;
							}

							if (garden[monk.getY()][monk.getX()] != 0)
							{
								monk.setY(monk.getY() - 1);
								free = monk.lookaround(garden);
								if (free.empty())
								{
									
									game_over = true;
								
								}
								else
								{
									for each (Monk::Movement var in free)
									{
										if (var == monk.getprefrered())
										{
											set = true;
											monk.setdirection(var);
											current_direction = monk.getdirection();
											if (monk.getprefrered() == Monk::RIGHT)
											{
												monk.setX(monk.getX() - 1);
											}
											else if (monk.getprefrered() == Monk::LEFT)
											{
												monk.setX(monk.getX() + 1);
											}

										}
									}

									if (!set)
									{
										monk.setdirection(free[0]);
										current_direction = monk.getdirection();
										if (monk.getdirection() == Monk::RIGHT)
										{
											monk.setX(monk.getX() - 1);
										}
										else if (monk.getdirection() == Monk::LEFT)
										{
											monk.setX(monk.getX() + 1);
										}
										break;
									}
									else
									{
										set = false;
										break;
									}
								}
							}
							else
							{
								garden[monk.getY()][monk.getX()] = i + 1;
								monk.setY(monk.getY() + 1);
							}
						}//while down end

						free.clear();
						while (current_direction == Monk::UP)
						{
							if (!monk.isinside())
							{
								break;
							}

							if (garden[monk.getY()][monk.getX()] != 0)
							{
								monk.setY(monk.getY() + 1);
								free = monk.lookaround(garden);
								if (free.empty())
								{
									
									game_over = true;
								
								}
								else
								{
									for each (Monk::Movement var in free)
									{
										if (var == monk.getprefrered())
										{
											set = true;
											monk.setdirection(var);
											current_direction = monk.getdirection();
											if (monk.getprefrered() == Monk::RIGHT)
											{
												monk.setX(monk.getX() - 1);
											}
											else if (monk.getprefrered() == Monk::LEFT)
											{
												monk.setX(monk.getX() + 1);
											}
										}
									}

									if (!set)
									{
										monk.setdirection(free[0]);
										current_direction = monk.getdirection();
										if (monk.getdirection() == Monk::RIGHT)
										{
											monk.setX(monk.getX() - 1);
										}
										else if (monk.getdirection() == Monk::LEFT)
										{
											monk.setX(monk.getX() + 1);
										}

										break;
									}
									else
									{
										set = false;
										break;
									}
								}
							}
							else
							{
								garden[monk.getY()][monk.getX()] = i + 1;
								monk.setY(monk.getY() - 1);
							}
						}// while up end

						free.clear();
						while (current_direction == Monk::LEFT)
						{
							if (!monk.isinside())
							{
								break;
							}

							if (garden[monk.getY()][monk.getX()] != 0)
							{
								monk.setX(monk.getX() - 1);
								free = monk.lookaround(garden);
								if (free.empty())
								{
									
									game_over = true;
								
								}
								else
								{
									for each (Monk::Movement var in free)
									{
										if (var == monk.getprefrered())
										{
											set = true;
											monk.setdirection(var);
											current_direction = monk.getdirection();
											if (monk.getprefrered() == Monk::DOWN)
											{
												monk.setY(monk.getY() + 1);
											}
											else if (monk.getprefrered() == Monk::UP)
											{
												monk.setY(monk.getY() - 1);
											}
										}
									}

									if (!set)
									{
										monk.setdirection(free[0]);
										current_direction = monk.getdirection();
										if (monk.getdirection() == Monk::DOWN)
										{
											monk.setY(monk.getY() + 1);
										}
										else if (monk.getdirection() == Monk::UP)
										{
											monk.setY(monk.getY() - 1);
										}
										break;
									}
									else
									{
										set = false;
										break;
									}
								}
							}
							else
							{
								garden[monk.getY()][monk.getX()] = i + 1;
								monk.setX(monk.getX() + 1);
							}
						}// while left end
						free.clear();
						while (current_direction == Monk::RIGHT)
						{
							if (!monk.isinside())
							{
								break;
							} 

							if (garden[monk.getY()][monk.getX()] != 0)
							{
								monk.setX(monk.getX() + 1);
								free = monk.lookaround(garden);
								if (free.empty())
								{
									game_over = true;
								
								}
								else
								{
									for each (Monk::Movement var in free)
									{
										if (var == monk.getprefrered())
										{
											set = true;
											monk.setdirection(var);
											current_direction = monk.getdirection();
											if (monk.getprefrered() == Monk::DOWN)
											{
												monk.setY(monk.getY() + 1);
											}
											else if (monk.getprefrered() == Monk::UP)
											{
												monk.setY(monk.getY() - 1);
											}
										}
									}

									if (!set)
									{
										monk.setdirection(free[0]);
										current_direction = monk.getdirection();
										if (monk.getdirection() == Monk::DOWN)
										{
											monk.setY(monk.getY() + 1);
										}
										else if (monk.getdirection() == Monk::UP)
										{
											monk.setY(monk.getY() - 1);
										}
										break;
									}
									else
									{
										set = false;
										break;
									}
								}
							}
							else
							{
								garden[monk.getY()][monk.getX()] = i + 1;
								monk.setX(monk.getX() - 1);
							}
						}// while right end
						free.clear();
					
				}// while end
			}// check if can be entered
			free.clear();

	}//for end
	gardener->setmap(garden);
}

vector<Monk> Generation::crossover(vector<Monk> matingpool, int size,Map map)
{
	Monk father;
	Monk mother;
	int first, second;
	vector<int>genes;
	vector<Monk> new_generation;
	new_generation.resize(2*size);
	genes.resize(map.getheight() + map.getwidth() + map.getstonecount());
	int numbers = 0;
	int childrecount = 0;
	while (numbers<(2*size))
	{
		childrecount = 0;
		first = (rand() % size);
		second = (rand() % size);
		while (first == second)
		{
			second = (rand() % size);
		}

		father = matingpool[first];
		mother = matingpool[second];


			for (int i = 0; i < father.getstarts().size(); i++)
			{
				if (i % 2 == 0)
				{
					genes[i] = father.getstarts()[i];
				}
				else
				{
					genes[i] = mother.getstarts()[i];
				}
				
				
			}
			genes[(map.getheight() + map.getwidth() + map.getstonecount())-1] = (rand() % 2);
			new_generation[numbers] = Monk(genes, this->generation + 1, map);
			numbers++;
			childrecount++;
			
		
	}
	return new_generation;
}
void Generation::addgeneration(int size, int generation, Map map,vector<Monk> humanity)
{
	this->population_size = size;
	this->generation = generation;
	this->population = humanity;
}

int Generation::getbestfitness(vector<Monk> pop)
{
	int max = 0;
	for (int i = 0; i < pop.size(); i++)
	{
		if (max < pop[i].getfitness())
		{
			max = pop[i].getfitness();
		}
	}
	return max;
}
int Generation::avgfitness(vector<Monk> pop)
{
	int sum = 0;
	int avg = 0;
	for (int i = 0; i < pop.size(); i++)
	{
		sum += pop[i].getfitness();
	}
	avg = sum / pop.size();
	return avg;
}
vector<Monk> Generation::crossover(vector<Monk> matingpool, int size, Map map,double mutation)
{
	Monk father;
	Monk mother;
	int first, second;
	vector<int>genes;
	vector<Monk> new_generation;
	bool wilmutate = false;
	new_generation.resize(2 * size);
	genes.resize(map.getheight() + map.getwidth() + map.getstonecount());
	int numbers = 0;
	int childrecount = 0;
	
	while (numbers<(2 * size))
	{
		if (((double)rand() / (RAND_MAX + 1)) < mutation)
		{
			wilmutate = true;
		}
		childrecount = 0;
		first = (rand() % size);
		second = (rand() % size);
		while (first == second)
		{
			second = (rand() % size);
		}

		father = matingpool[first];
		mother = matingpool[second];


		for (int i = 0; i < father.getstarts().size(); i++)
		{
			if (i % 2 == 0)
			{
				genes[i] = father.getstarts()[i];
			}
			else
			{
				genes[i] = mother.getstarts()[i];
			}


		}
		if (wilmutate)
		{
			int i = (rand() % genes.size());
			genes[(map.getheight() + map.getwidth() + map.getstonecount()) - 1] = (rand() % 2);
			genes[i] = (rand() % (map.getheight() + map.getwidth() + map.getstonecount()));
			new_generation[numbers] = Monk(genes, this->generation + 1, map);
			numbers++;
			childrecount++;
		}
		else
		{
			genes[(map.getheight() + map.getwidth() + map.getstonecount()) - 1] = (rand() % 2);
			new_generation[numbers] = Monk(genes, this->generation + 1, map);
			numbers++;
			childrecount++;
		}
		wilmutate = false;

	}
	return new_generation;
}