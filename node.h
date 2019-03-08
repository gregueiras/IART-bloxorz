#pragma once
#include <vector>
#include <string>
#include "model.h"

struct point
{
  int x;
  int y;

  point(const int &x, const int &y)
  {
    this->x = x;
    this->y = y;
  }

  point()
  {
    this->x = -1;
    this->y = -1;
  }
};

class node
{
  int cost_;
  std::vector<model> map_;
  std::vector<point> pos_;
  point target_;

  std::vector<std::vector<point>> parents_ = {};
  std::vector<std::string> steps_ = {};

  int cols_;

public:
  node(const std::vector<int> &initializer, const int &rows, const int &cols);
  ~node();

  bool operator<(const node& rhs) const;
  bool operator==(const node& rhs);
  bool objective();

  void print();
};

