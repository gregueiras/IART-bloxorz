#pragma once
#include "node.h"
#include "strategy.h"

typedef double (*cost_function)(const node &a, heuristic heuristic_);

typedef const double(*distance_aux_function)(const int x1, const int y1, const int x2, const int y2);

typedef const double (*heuristic_distance_function)(const node &a);

typedef const double(*heuristic_distance_aux_function)(const node &node, point target);


double inc(const node &node, heuristic heuristic_);

double dec(const node &node, heuristic heuristic_);

double greedy_(const node &node, heuristic heuristc_);

double a_star_(const node &node, heuristic heuristc_);

const double heuristic_func(const node &node, heuristic heuristic_);




