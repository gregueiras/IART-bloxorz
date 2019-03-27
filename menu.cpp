
#include <iostream>
#include "menu.h"


void runnerValues::setLevel(int levelNumber) {
	switch (levelNumber) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

void runnerValues::setMode(int modeNumber) {
	switch (modeNumber)
	{
	case 1:
		this->mode = bfs;
		break;
	case 2:
		this->mode = dfs;
		break;
	case 3:
		this->mode = iterative;
		break;
	case 4:
		this->mode = greedy;
		break;
	case 5:
		this->mode = a_star;
		break;
	default:
		this->mode = dfs;
		break;
	}
}

void runnerValues::setHeuristic(int heuristicNumber)
{
	switch (heuristicNumber)
	{
	case 1:
		this->heuristic = manhattan_distance;
		break;
	case 2:
		this->heuristic = euclidian_distance;
		break;
	case 3:
		this->heuristic = manhattan_teletransport_distance;
		break;
	case 4:
		this->heuristic = euclidian_teletransport_distance;
		break;
	default:
		this->heuristic = manhattan_distance;
		break;
	}
}

void runnerValues::setDepth(int depth) {
	this->depth = depth;
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

void firstMenu(runnerValues &values)
{
	std::cout << "Hello there!" << std::endl << std::endl;
	std::cout
		<< "1- Choose level" << std::endl
		<< "2- Quit" << std::endl
		<< "Select one" << std::endl;
	switch (getIntInInterval(1, 2))
	{
	case 1:
		return chooseLevelMenu(values);
	case 2:
		std::cout << "Closing..." << std::endl;
		return;
	}
}

void chooseLevelMenu(runnerValues &values)
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
		values.setLevel(choice);
		break;
	case 5:
		std::cout << "Closing..." << std::endl;
		return;
	}
	return chooseAlgorithmMenu(values);
}


void chooseAlgorithmMenu(runnerValues &values)
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

void chooseHeuristicMenu(runnerValues &values)
{
	std::cout
		<< "1- Manhattan distance" << std::endl
		<< "2- Euclidian distance" << std::endl
		<< "3- Manhattan distance with teletransport" << std::endl  
		<< "4- Euclidina distance with teletransport" << std::endl
		<< "5- Go back" << std::endl
		<< "Select one" << std::endl;
	int choice = getIntInInterval(1, 5);
	switch (choice)
	{
	case 1: case 2: case 3: case 4:
		values.setHeuristic(choice);
		break;
	case 5:
		return chooseLevelMenu(values);
	}
}


void chooseIterativeDepthMenu(runnerValues &values) {
	std::cout << "Starting location? " << std::endl;
	int depth = getInt();
	if (depth == -1)
		return chooseAlgorithmMenu(values);
	values.setDepth(depth);
}




