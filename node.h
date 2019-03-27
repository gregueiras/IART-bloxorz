#pragma once
#include <string>
#include <vector>
#include "model.h"
#include <map>

class point {
 public:
  int x;
  int y;

  point(const int &x, const int &y) {
    this->x = x;
    this->y = y;
  }
  point() {
    this->x = -1;
    this->y = -1;
  }

  bool operator<(const point &rhs) const {
    return this->x < rhs.x && this->y < rhs.y;
  }

  bool operator==(const point &rhs) const {
    return this->x == rhs.x && this->y == rhs.y;
  }

  friend std::ostream &operator<<(std::ostream &os, const point &point);
};



class node {
 public:
  double cost;
  std::vector<model> map;
  std::vector<point> pos;
  point target;

  std::vector<std::vector<point>> parents = {};
  std::vector<std::string> steps = {};

  int cols;
  int rows;

  std::map<int, point> teletransport_tiles = {};
 
  bool closedTiles;

  node(const std::vector<int> &initializer, const int &rows, const int &cols);
  ~node();
  node();

  bool operator<(const node &rhs) const;
  bool operator==(const node &rhs) const;
  bool objective() const;
  void print() const;
  friend std::ostream &operator<<(std::ostream &os, const node &node);
};

int get_index(const int &x, const int &y, const int &cols);