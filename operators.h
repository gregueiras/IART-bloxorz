#pragma once
#include "node.h"
#include "strategy.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

typedef double (*cost_function)(const node &a, heuristic heuristic_);
typedef node (*operators)(node a, cost_function foo, heuristic heuristic_);

node roll_up(node state, cost_function cost, heuristic heuristic_);

node roll_down(node state, cost_function cost, heuristic heuristic_);

node roll_left(node state, cost_function cost, heuristic heuristic_);

node roll_right(node state, cost_function cost, heuristic heuristic_);

node standing_move(node &state, const cost_function cost, heuristic heuristic_, const int x, const int y, const int direction_x, const int direction_y);
node sideways_move(node &state, const cost_function cost, heuristic heuristic_, const int x1, const int y1, const int x2, const int y2, const int direction_x, const int direction_y);
node forewards_move(node &state, const cost_function cost, heuristic heuristic_, const int x1, const int y1, const int x2, const int y2, const int m_x, const int m_y, const int direction_x, const int direction_y);

inline const double heuristic_manhattan_distance(const node &node)
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

inline const double heuristic_euclidian_distance(const node &node)
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

inline const double heuristic_func(const node &node, heuristic heuristic_)
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

inline double inc(const node &node, heuristic heuristic_) // TEST
{
	return node.cost + 1;
}

inline double dec(const node &node, heuristic heuristic_)
{
	return node.cost - 1;
}

inline double greedy_(const node &node, heuristic heuristc_)
{
	return heuristic_func(node, heuristc_);
}

inline double a_star_(const node &node, heuristic heuristc_)
{
	return node.cost + heuristic_func(node, heuristc_);
}
