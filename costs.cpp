#include "costs.h"
#include <algorithm>
#include <stdexcept>


const double heuristic_manhattan_distance(const node &node)
{

	if (node.pos.size() == 2)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x1 = node.pos.at(0).x;
		const auto y1 = node.pos.at(0).y;
		const auto x2 = node.pos.at(1).x;
		const auto y2 = node.pos.at(1).x;
		const auto distance_1 = abs(target_x - x1) + abs(target_y - y1);
		const auto distance_2 = abs(target_x - x2) + abs(target_y - y2);
		return std::min(distance_1, distance_2);
	}
	else if (node.pos.size() == 1)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x = node.pos.at(0).x;
		const auto y = node.pos.at(0).y;
		return abs(target_x - x) + abs(target_y - y);
	}
	else
	{
		throw std::invalid_argument("invalid position");
	}
}

const double heuristic_euclidian_distance(const node &node)
{
	if (node.pos.size() == 2)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x1 = node.pos.at(0).x;
		const auto y1 = node.pos.at(0).y;
		const auto x2 = node.pos.at(1).x;
		const auto y2 = node.pos.at(1).x;
		const auto distance_1 = sqrt(pow((target_x - x1), 2) + pow((target_y - y1), 2));
		const auto distance_2 = sqrt(pow((target_x - x2), 2) + pow((target_y - y2), 2));
		return std::min(distance_1, distance_2);
	}
	else if (node.pos.size() == 1)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x = node.pos.at(0).x;
		const auto y = node.pos.at(0).y;
		return sqrt(pow((target_x - x), 2) + pow((target_y - y), 2));
	}
	else
	{
		throw std::invalid_argument("invalid position");
	}
}

//devia atirar uma excepçao no caso de default provavelmente
const double heuristic_func(const node &node, heuristic heuristic_)
{
	switch (heuristic_)
	{
	case none:
		return 0;
	case manhattan_distance:
		return heuristic_manhattan_distance(node);
	case euclidian_distance:
		return heuristic_euclidian_distance(node);
	default:
		return -1;
	}
}

double inc(const node &node, heuristic heuristic_) // TEST
{
	return node.cost + 1;
}

double dec(const node &node, heuristic heuristic_)
{
	return node.cost - 1;
}

double greedy_(const node &node, heuristic heuristc_)
{
	return heuristic_func(node, heuristc_);
}

double a_star_(const node &node, heuristic heuristc_)
{
	return node.cost + heuristic_func(node, heuristc_);
}