
#include <iostream>
#include "menu.h"


void runnerValues::setFile(int levelNumber) {
	switch (levelNumber) {
	case 1:
		this->file = "./levels/level1.txt";
		break;
	case 2:
		this->file = "./levels/level2i.txt";
		break;
	case 3:
		this->file =  "./levels/level3.txt";
		break;
	case 4:
		this->file = "./levels/level4.txt";
		break;
	case 5:
		this->file = "./levels/level5.txt";
		break;
	case 6:
		this->file = "./levels/level6.txt";
		break;
	default:
		this->file = "./levels/level1.txt";
		break;
	}
}

void runnerValues::setMode(int modeNumber) {
	switch (modeNumber)
	{
	case 1:
		this->mode_ = bfs;
		break;
	case 2:
		this->mode_ = dfs;
		break;
	case 3:
		this->mode_ = iterative;
		break;
	case 4:
		this->mode_ = greedy;
		break;
	case 5:
		this->mode_ = a_star;
		break;
	default:
		this->mode_ = dfs;
		break;
	}
}

void runnerValues::setHeuristic(int heuristicNumber)
{
	switch (heuristicNumber)
	{
	case 1:
		this->heuristic_ = manhattan_distance;
		break;
	case 2:
		this->heuristic_ = euclidian_distance;
		break;
	case 3:
		this->heuristic_ = manhattan_teletransport_distance;
		break;
	case 4:
		this->heuristic_ = euclidian_teletransport_distance;
		break;
	default:
		this->heuristic_ = manhattan_distance;
		break;
	}
}

void runnerValues::setDepth(int depth) {
	this->depth = depth;
}

void runnerValues::setRunTimes(int runTimes) {
	this->runTimes = runTimes;
}


void cleanfunction()
{
	std::cin.ignore();
	std::cin.clear();
}

int getIntInInterval(int lower, int upper)
{
	int num;
	bool validInput;
	do
	{
		validInput = true;
		std::cin >> num;
		if (std::cin.fail())
		{
			validInput = false;

			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid Input!" << std::endl;

		}
		else if (!(num <= upper && num >= lower))
		{
			validInput = false;
			std::cout << "Invalid Choice!" << std::endl;
		}
	} while (!validInput);

	return num;
}

int getInt()
{
	int num;
	std::cin >> num;

	if (std::cin.fail() || num < 0)
	{
		std::cout << "Invalid Input!\n";
		std::cin.clear();
		return -1;
	}
	return num;
}

bool firstMenu(runnerValues &values)
{
	std::cout << "Hello there!" << std::endl << std::endl;
	std::cout
		<< "1- Run 1 time" << std::endl
		<< "2- Run multiple times" << std::endl
		<< "3- Quit" << std::endl
		<< "Select one" << std::endl;
	switch (getIntInInterval(1, 3))
	{
	case 1:
		values.setRunTimes(1);
		return chooseLevelMenu(values);
	case 2:
		return chooseNumberRuns(values);
	case 3:
		std::cout << "Closing..." << std::endl;
		return false;
	}
}


bool chooseNumberRuns(runnerValues &values) {
	std::cout << "How many times the agent should run? " << std::endl;
	int runTimes = getInt();
	if (runTimes == -1)
		return firstMenu(values);
	values.setRunTimes(runTimes);
	return chooseLevelMenu(values);
}

bool chooseLevelMenu(runnerValues &values)
{
	std::cout
		<< "1- Level 1" << std::endl
		<< "2- Level 2" << std::endl
		<< "3- Level 3" << std::endl
		<< "4- Level 4" << std::endl
		<< "5- Quit" << std::endl
		<< "Select one" << std::endl;
	int choice = getIntInInterval(1, 5);
	switch (choice)
	{
	case 1: case 2: case 3: case 4: 
		values.setFile(choice);
		break;
	case 5:
		std::cout << "Closing..." << std::endl;
		return false;
	}
	return chooseAlgorithmMenu(values);
}


bool chooseAlgorithmMenu(runnerValues &values)
{
	std::cout
		<< "1- Breadth-First Search (BFS)" << std::endl
		<< "2- Depth-First Search (DFS)" << std::endl
		<< "3- Iterative" << std::endl   //escolher profundidade de pesquisa
		<< "4- Greedy" << std::endl
		<< "5- A*" << std::endl
		<< "6- Go back" << std::endl
		<< "Select one" << std::endl;
	int choice = getIntInInterval(1, 6);
	switch (choice)
	{
	case 1: case 2:
		values.setMode(choice);
		break;
	case 3:
		values.setMode(choice);
		return chooseIterativeDepthMenu(values);
		break;
	case 4: case 5:
		values.setMode(choice);
		return chooseHeuristicMenu(values);
	case 6:
		return chooseLevelMenu(values);
	}
}

bool chooseHeuristicMenu(runnerValues &values)
{
	std::cout
		<< "1- Manhattan distance" << std::endl
		<< "2- Euclidian distance" << std::endl
		<< "3- Manhattan distance with teletransport" << std::endl  
		<< "4- Euclidian distance with teletransport" << std::endl
		<< "5- Go back" << std::endl
		<< "Select one" << std::endl;
	int choice = getIntInInterval(1, 5);
	switch (choice)
	{
	case 1: case 2: case 3: case 4:
		values.setHeuristic(choice);
		return true;
	case 5:
		return chooseLevelMenu(values);
	}
}


bool chooseIterativeDepthMenu(runnerValues &values) {
	std::cout << "Iterative Depth? " << std::endl;
	int depth = getInt();
	if (depth == -1)
		return chooseAlgorithmMenu(values);
	values.setDepth(depth);
	return true;
}






