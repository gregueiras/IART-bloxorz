#include "costs.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cmath>


const double manhattan_distance_aux(const int x1, const int y1, const int x2, const int y2){
	return abs(x2 - x1) + abs(y2 - y1);
}

const double euclidian_distance_aux(const int x1, const int y1, const int x2, const int y2){
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

const double heuristic_distance_aux(const node &node, point target, distance_aux_function distance_function)
{
	if (node.pos.size() == 2)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x1 = node.pos.at(0).x;
		const auto y1 = node.pos.at(0).y;
		const auto x2 = node.pos.at(1).x;
		const auto y2 = node.pos.at(1).x;
		const auto distance_1 = distance_function(x1, y1, target_x, target_y) / (1 << 2);
		const auto distance_2 = distance_function(x2, y2, target_x, target_y) / (1 << 2);
		return std::min(distance_1, distance_2);
	}
	else if (node.pos.size() == 1)
	{
		const auto target_x = node.target.x;
		const auto target_y = node.target.y;
		const auto x = node.pos.at(0).x;
		const auto y = node.pos.at(0).y;
		return (distance_function(x, y, target_x, target_y) / (1 << 2));
	}
	else
	{
		throw std::invalid_argument("invalid position");
	}
}


const double heuristic_manhattan_distance_aux(const node &node, point target){
	return heuristic_distance_aux(node, target, manhattan_distance_aux);
}

const double heuristic_euclidian_distance_aux(const node &node, point target){
	return heuristic_distance_aux(node, target, euclidian_distance_aux);
}

const double heuristic_manhattan_distance(const node &node) {
	return heuristic_manhattan_distance_aux(node, node.target);
}

const double heuristic_euclidian_distance(const node &node){
	return heuristic_euclidian_distance_aux(node, node.target);
}


const double heuristic_teletransport_distance_aux(const node &node, heuristic_distance_function heuristic_function, heuristic_distance_aux_function heuristic_function_aux,distance_aux_function distance_function) {
	const double distance_target = heuristic_function(node);
	double  total_distance = 0, min_tel_distance = -1;

	for (auto const& tile : node.teletransport_tiles) {
		auto next_tile = node.teletransport_tiles.at(tile.first*-1);
		total_distance = heuristic_function_aux(node, tile.second) + distance_function(next_tile.x, next_tile.y, node.target.x, node.target.y);
		if (min_tel_distance == -1)
			min_tel_distance = total_distance;
		else
			min_tel_distance = std::min(min_tel_distance, total_distance);
	}
	if (min_tel_distance == -1)
		return distance_target;
	return std::min(min_tel_distance, distance_target);
}



const double heuristic_teletransport_manhattan_distance(const node &node) {
	return  heuristic_teletransport_distance_aux(node, heuristic_manhattan_distance, heuristic_manhattan_distance_aux, manhattan_distance_aux);
}


const double heuristic_teletransport_euclidian_distance(const node &node) {
	return  heuristic_teletransport_distance_aux(node, heuristic_euclidian_distance, heuristic_euclidian_distance_aux, euclidian_distance_aux);
}


const double heuristic_door_distance_aux(const node &node, distance_aux_function distance_function) {
	if (node.closedTiles && node.door.x != -1 && node.door.y != -1)
		return heuristic_distance_aux(node, node.door, distance_function);
	else
		return heuristic_distance_aux(node, node.target, distance_function);
}


const double heuristic_door_manhattan_distance(const node &node) {
	return heuristic_door_distance_aux(node, manhattan_distance_aux);
}

const double heuristic_door_euclidian_distance(const node &node) {
	return heuristic_door_distance_aux(node, euclidian_distance_aux);
}


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
	case manhattan_teletransport_distance :
		return heuristic_teletransport_manhattan_distance(node);
	case euclidian_teletransport_distance:
		return heuristic_teletransport_euclidian_distance(node);
	case manhattan_door_distance:
		return heuristic_door_manhattan_distance(node);
	case euclidian_door_distance :
		return heuristic_door_euclidian_distance(node);
	default:
		throw std::invalid_argument("invalid heuristic");
	}
}

double inc(const node &node, heuristic heuristic_) 
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