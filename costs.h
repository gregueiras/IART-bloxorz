#pragma once
#include "node.h"
#include "strategy.h"

typedef double (*cost_function)(const node &a, heuristic heuristic_);


double inc(const node &node, heuristic heuristic_);

double dec(const node &node, heuristic heuristic_);

double greedy_(const node &node, heuristic heuristc_);

double a_star_(const node &node, heuristic heuristc_);

const double heuristic_func(const node &node, heuristic heuristic_);

const double heuristic_manhattan_distance(const node &node);

const double heuristic_euclidian_distance(const node &node);

const double heuristic_teletransport_manhattan_distance(const node &node);

const double heuristic_teletransport_euclidian_distance(const node &node);



