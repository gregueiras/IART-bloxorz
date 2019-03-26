#include "costs.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>


const double manhattan_distance_aux(int x1, int y1, int x2, int y2)
{
	return abs(x2 - x1) + abs(y2 - y1);
}

const double euclidian_distance_aux(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

const double heuristic_manhattan_distance_aux(const node &node, point target)
{
	if (node.pos.size() == 2)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x1 = node.pos.at(0).x;
		const auto y1 = node.pos.at(0).y;
		const auto x2 = node.pos.at(1).x;
		const auto y2 = node.pos.at(1).x;
		const auto distance_1 = manhattan_distance_aux(x1, y1, target_x, target_y);
		const auto distance_2 = manhattan_distance_aux(x2, y2, target_x, target_y);
		return std::min(distance_1, distance_2);	
	}
	else if (node.pos.size() == 1)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x = node.pos.at(0).x;
		const auto y = node.pos.at(0).y;
		return manhattan_distance_aux(x,y,target_x, target_y);
	}
	else
	{
		throw std::invalid_argument("invalid position");
	}
}

const double heuristic_euclidian_distance_aux(const node &node, point target)
{
	if (node.pos.size() == 2)
	{
		const auto target_x = target.x;
		const auto target_y = target.y;
		const auto x1 = node.pos.at(0).x;
		const auto y1 = node.pos.at(0).y;
		const auto x2 = node.pos.at(1).x;
		const auto y2 = node.pos.at(1).x;
		const auto distance_1 = euclidian_distance_aux(x1, y1, target_x, target_y);
		const auto distance_2 = euclidian_distance_aux(x2, y2, target_x, target_y);
		return std::min(distance_1, distance_2);
	}
	else if (node.pos.size() == 1)
	{
		const auto target_x = target.x;
		const auto target_y = target.y;
		const auto x = node.pos.at(0).x;
		const auto y = node.pos.at(0).y;
		return euclidian_distance_aux(x, y, target_x, target_y);
	}
	else
	{
		throw std::invalid_argument("invalid position");
	}
}

const double heuristic_manhattan_distance(const node &node) {
	return heuristic_manhattan_distance_aux(node, node.target);
}

const double heuristic_euclidian_distance(const node &node)
{
	return heuristic_euclidian_distance_aux(node, node.target);
}


const double heuristic_teletransport_manhattan_distance(const node &node) {
	const double distance_target = heuristic_manhattan_distance(node);
	double  total_distance = 0, min_tel_distance = -1;

	for (auto const& tile : node.teletransport_tiles) {
		auto next_tile = node.teletransport_tiles.at(tile.first*-1);
		total_distance = heuristic_manhattan_distance_aux(node, tile.second) + manhattan_distance_aux(next_tile.x, next_tile.y, node.target.x, node.target.y);
		if (min_tel_distance == -1)
			min_tel_distance = total_distance;
		else
			min_tel_distance = std::min(min_tel_distance, total_distance);
	}
	if (min_tel_distance == -1)
		return distance_target;
	return std::min(min_tel_distance, distance_target);
}


const double heuristic_teletransport_euclidian_distance(const node &node) {
	const double distance_target = heuristic_euclidian_distance(node);
	double  total_distance = 0, min_tel_distance = -1;

	for (auto const& tile : node.teletransport_tiles) {
		auto next_tile = node.teletransport_tiles.at(tile.first*-1);
		total_distance = heuristic_euclidian_distance_aux(node, tile.second) + euclidian_distance_aux(next_tile.x, next_tile.y, node.target.x, node.target.y);
		if (min_tel_distance == -1)
			min_tel_distance = total_distance;
		else
			min_tel_distance = std::min(min_tel_distance, total_distance);
	}
	if (min_tel_distance == -1)
		return distance_target;
	return std::min(min_tel_distance, distance_target);
}


//TODO devia atirar uma excepçao no caso de default provavelmente
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
	case  manhattan_teletransport_distance :
		return heuristic_teletransport_manhattan_distance(node);
	case  euclidian_teletransport_distance:
		return heuristic_teletransport_euclidian_distance(node);
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