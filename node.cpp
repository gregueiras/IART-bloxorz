#pragma once
#include "node.h"
#include "model.h"
#include <stdexcept>
#include <iostream>


node::node(const std::vector<int> &initializer, const int &rows, const int &cols) {
  this->cost = 0;
  this->pos = {};
  this->map = {};
  this->cols = cols;
  this->rows = rows;
  this->closedTiles = true;
  this->belowBlock1 = 0;
  this->belowBlock2 = 0;

  const int length = initializer.size();
  if (length != rows * cols)
  {
    throw std::invalid_argument("number of tiles doesn't match rows*cols");
  }

  for (auto i = 0; i < length; ++i)
  {
    const auto elem = initializer[i];
	const point p(i % cols, i / cols);
    if (elem == block_tile)
    {
      this->pos.push_back(p);
      this->map.emplace_back(block_tile);
    }
    else if (elem == target_tile)
    {
      this->target = p;
      this->map.emplace_back(target_tile);
    } 
    else if (elem == empty_tile)
    {
      this->map.emplace_back(empty_tile);
    }
    else if (elem == invalid_tile)
    {
      this->map.emplace_back(invalid_tile);
    }
	else if (elem == teletransport_tile_1)
	{
		this->teletransport_tiles[teletransport_tile_1] = p;
		this->map.emplace_back(teletransport_tile_1);
	}
	else if (elem == teletransport_tile_2)
	{
		this->teletransport_tiles[teletransport_tile_2] = p;
		this->map.emplace_back(teletransport_tile_2);	
	}
	else if (elem == teletransport_tile_3)
	{
		this->teletransport_tiles[teletransport_tile_3] = p;
		this->map.emplace_back(teletransport_tile_3);
	}
	else if (elem == teletransport_tile_4)
	{
		this->teletransport_tiles[teletransport_tile_4] = p;
		this->map.emplace_back(teletransport_tile_4);
	}
	else if (elem == push_tile)
	{
		this->map.emplace_back(push_tile);
	}
	else if (elem == closed_tile)
	{
		this->map.emplace_back(closed_tile);
	}
	else if (elem == door_tile)
	{
		this->map.emplace_back(door_tile);
	}
  }
}

node::node() : node({}, 0, 0) {}

node::~node()
= default;

bool node::operator<(const node& rhs) const
{ return this->cost > rhs.cost; }

bool node::objective() const {
  return this->pos.size() == 1 && this->pos.at(0) == this->target;
}

void node::print() const
{
  for (auto point : this->pos)
  {
    std::cout << "X: " << point.x << "\tY: " << point.y << std::endl;
  }
  std::cout << "Target X: " << this->target.x << "\tY: " << this->target.y << std::endl;
  
  auto i = 0;
  for (auto tile : this->map)
  {
    i++;
    char c;
    switch (tile)
    {
      case empty_tile: c = 'O';  break;
      case target_tile: c = 'T';  break;
      case block_tile: c = 'M'; break;
	  case invalid_tile: c = 'X'; break;
	  case teletransport_tile_1: case teletransport_tile_2: c = 'S'; break;
	  case teletransport_tile_3: case teletransport_tile_4: c = 'R'; break;
	  case push_tile: c = 'P'; break;
	  case closed_tile: c = 'C'; break;
	  case door_tile: c = 'D' ; break;
      default: c = 'O';
    }

    std::cout << c;
    if (i % this->cols == 0) std::cout << std::endl;
  }
}

int get_index(const int& x, const int& y, const int &cols)
{
  return x + y * cols;
}

std::ostream &operator<<(std::ostream &os, const point &point) {
  os << "X: " << point.x << "\tY: " << point.y;
  return os;
}

std::ostream &operator<<(std::ostream &os, const node &node) {
  for (std::string step : node.steps)
  {
    os << step << "\t";
  }
  return os;
}