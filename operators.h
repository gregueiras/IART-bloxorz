#pragma once
#include "node.h"

typedef int(*cost_function)(const node& a);
//typedef node(*operators)(node a, cost_function foo);

node roll_up(node state, cost_function cost);

node roll_down(node state, cost_function cost);

node roll_left(node state, cost_function cost);

node roll_right(node state, cost_function cost);
