#include "runner.h"
#include <algorithm>
#include "levels.h"
#include <chrono>
#include <iostream>


node runner::find_solution() {
  std::priority_queue<node> queue;
  node initial(this->map_, this->rows_, this->cols_);
  queue.push(initial);

  while (!queue.empty() && !queue.top().objective()) {
    this->nodes_analyzed_++;
    auto no = queue.top();
    queue.pop();
	if(this->steps)
		no.print();

    for (auto& op : this->ops_) {
      try {
        auto child = op(no, this->cost_, this->heuristic_);

        auto conditions = false;

        if (this->mode_ == iterative) {
          conditions = std::find(no.parents.begin(), no.parents.end(),
                                 child.pos) == no.parents.end() &&
                       -child.cost <= this->limit_;
        } else {
          conditions = std::find(no.parents.begin(), no.parents.end(),
                                 child.pos) == no.parents.end();
        }

        if (conditions) {
          /*
            for (size_t j = 0; j < child.steps.size(); j++)
            {
              std::cout << child.steps.at(j) << "  ";
            }
            std::cout << "\t" << child.parents.size() << std::endl;
           */
          child.parents.emplace_back(no.pos);
          queue.emplace(child);
        }
      } catch (...) {
      }
    }
  }

  if (!queue.empty()) {
	return queue.top();
  }

  throw std::exception("NO MORE NODES");
}

//CORRE (2)
//node runner::run() { return find_solution(true, NULL); }

long long runner::run(const int i, node& node_ret) {
  this->nodes_analyzed_ = 0;
  const auto begin =
      std::chrono::steady_clock::now();

  for (auto j = 0; j < i; ++j)
  {
	  try {
		node_ret = find_solution();
	  }
	  catch (std::exception e) {
		  std::cout << "No solution found! \n";
	  }
	  if (this->steps)
		  node_ret.print();
	  
	
  }
  const auto end = std::chrono::steady_clock::now();
  
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

runner::runner() {
  this->ops_ = {roll_up, roll_down, roll_left, roll_right};
  this->mode_ = dfs;
  this->heuristic_ = none;
  this->map_ = LVL1;
  this->cols_ = 7;
  this->rows_ = 5;
  this->cost_ = inc;
  this->limit_ = -1;
}

runner::runner(const mode mode, const std::vector<int>& map, const int rows,
               const int cols, bool steps)
    : runner() {
  this->mode_ = mode;
  this->map_ = map;
  this->cols_ = cols;
  this->rows_ = rows;
  this->steps = steps;
  switch(mode) {
  case bfs:
  case iterative :
	  this->cost_ = dec;
	  break;
  case dfs:
	  this->cost_ = inc;
	  break;
  case greedy :
	  this->cost_ = greedy_;
	  break;
  case a_star :
	  this->cost_ = a_star_;
	  break;
  default:
	  break;
  }
}

runner::runner(const mode mode, const heuristic heuristic,
               const std::vector<int>& map, const int rows, const int cols, bool steps)
    : runner(mode, map, rows, cols, steps) {
  this->heuristic_ = heuristic;
}

runner::runner(const mode mode, const int limit,
               const std::vector<int>& map, const int rows, const int cols, bool steps)
    : runner(mode, map, rows, cols, steps) {
  this->limit_ = limit;
}

runner::~runner() = default;

int runner::get_nodes_analyzed() const
{ return nodes_analyzed_; }
