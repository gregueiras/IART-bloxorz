#pragma once
#include "node.h"

typedef int (*cost_function)(const node& a);
typedef node (*operators)(node a, cost_function foo);

node roll_up(node state, cost_function cost);

node roll_down(node state, cost_function cost);

node roll_left(node state, cost_function cost);

node roll_right(node state, cost_function cost);


node standing_move(node& state, const cost_function cost, const int x, const int y, const int direction_x, const int direction_y);
node sideways_move(node& state, const cost_function cost, const int x1, const int y1, const int x2, const int y2, const int direction_x, const int direction_y);
node forewards_move(node& state, const cost_function cost, const int x1, const int y1, const int x2, const int y2, const int m_x, const int m_y, const int direction_x, const int direction_y);

inline int inc(const node& node)  // TEST
{
  return node.cost + 1;
}