#include "node.h"
#include "model.h"
#include <stdexcept>
#include <iostream>


node::node(const std::vector<int> &initializer, const int &rows, const int &cols) {
  this->cost_ = 0;
  this->pos_ = {};
  this->map_ = {};
  this->cols_ = cols;

  const int length = initializer.size();
  if (length != rows * cols)
  {
    throw std::invalid_argument("number of tiles doesn't match rows*cols");
  }

  for (auto i = 0; i < length; ++i)
  {
    const auto elem = initializer[i];
    if (elem == block)
    {
      const point p(i % cols, i / cols);
      this->pos_.emplace_back(p);
      this->map_.emplace_back(block);
    }
    else if (elem == target)
    {
      const point t(i % cols, i / cols);
      this->target_ = t;
      this->map_.emplace_back(target);
    } 
    else if (elem == empty_tile)
    {
      this->map_.emplace_back(empty_tile);
    }
  }

}


node::~node()
= default;

void node::print()
{
  auto i = 0;
  for (auto tile : this->map_)
  {
    i++;
    char c;
    switch (tile)
    {
      case empty_tile: c = 'O';  break;
      case target: c = 'T';  break;
      case block: c = 'M'; break;
      default: c = 'O';
    }

    std::cout << c;
    if (i % this->cols_ == 0) std::cout << std::endl;
  }
}
