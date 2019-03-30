// Bloxorz.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <string>
#include "getRSS.c"
#include "menu.h"
#include "operators.h"
#include "reader.h"
#include "runner.h"

void run(int n, mode mode, heuristic heuristic, int limit, std::string file,
         std::ostream& os, bool steps) {
  auto lvl = readToLevel(file);
  runner r;
  if (limit == NULL) {
    r = runner(mode, heuristic, lvl.level_map, lvl.num_rows, lvl.num_columns,
               steps);
  } else {
    r = runner(mode, limit, lvl.level_map, lvl.num_rows, lvl.num_columns,
               steps);
  }

  auto res = getCurrentRSS();
  auto res_old = res;

  for (auto i = 0; i < n; ++i) {
    node node;
    auto sol = r.run(n, node);

    res_old = res;
    res = getCurrentRSS();

    /*
    os << "TIME*" << n << ": " << sol << "\tNODES: " << r.get_nodes_analyzed()
       << "\tMEMORY EXPECTED: "
       << r.get_nodes_analyzed() * sizeof(node) / 1024.0 << " kB"
       << "\tMEMORY MEASURED: " << (res - res_old) / 1024.0 << " kB"
       << std::endl;
    */

    auto nodes = r.get_nodes_created();
    os << n << " " << sol << " " << nodes << " " << sizeof(node) * nodes << " "
       << (res - res_old) << std::endl;
  }
}

int main() {
  while (true) {
  runnerValues values;

  if(firstMenu(values))
   run(values.getRunTimes(), values.getMode(), values.getHeuristic(),
   values.getDepth(), values.getFile(), std::cout, values.getSteps());
  }
  /*
 
  heuristic heuristics[] = {manhattan_distance, euclidian_distance,
                            manhattan_teletransport_distance,
                            euclidian_teletransport_distance};

  std::string heuristics_names[] = {"manhattan_distance", "euclidian_distance",
                            "manhattan_teletransport_distance",
                            "euclidian_teletransport_distance"};

  const auto n = 5;
  for (auto level = 3; level <= 6; ++level) {
    for (auto i = 0; i < 4; ++i) {
      std::ofstream my_file;
      auto file_name = "./out/greedy+" + heuristics_names[i] + "+" + std::to_string(level) + ".csv";
      const auto file_level = "./Levels/Level" + std::to_string(level) + ".txt";
      std::cout << "Creating " << file_name << std::endl;

      my_file.open(file_name);
      run(n, greedy, heuristics[i], NULL, file_level, my_file, false);
      my_file.flush();
      my_file.close();

      file_name = "./out/a_star+" + heuristics_names[i] + "+" + std::to_string(level) + ".csv";
      std::cout << "Creating " << file_name << std::endl;

      my_file.open(file_name);
      run(n, a_star, heuristics[i], NULL, file_level, my_file, false);
      my_file.close();
    }
  }
   */
  return 0;
}
