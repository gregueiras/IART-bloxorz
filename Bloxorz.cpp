// Bloxorz.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include "windows.h"
#include "operators.h"
#include "psapi.h"
#include "reader.h"
#include "runner.h"
#include "menu.h"
#define WIN32_LEAN_AND_MEAN

void run(int n, mode mode, heuristic heuristic, int limit, std::string file,
         std::ostream& os) {
  auto lvl = readToLevel(file);
  runner r;
  if (limit == NULL) {
    r =
        runner(mode, heuristic, lvl.level_map, lvl.num_rows, lvl.num_columns);
  } else {
    r = runner(mode, limit, lvl.level_map, lvl.num_rows, lvl.num_columns);
  }

  PROCESS_MEMORY_COUNTERS pmc;
  const auto myHandle = GetCurrentProcess();
  GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc));
  size_t res = pmc.WorkingSetSize;
  size_t res_old;

  for (auto i = 0; i < n; ++i) {
    node node;
    auto sol = r.run(n, node);

    if (GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc))) {
      res_old = res;
      res = (pmc.WorkingSetSize);
    }
    os << "TIME*" << n << ": " << sol << "\tNODES: " << r.get_nodes_analyzed()
       << "\tMEMORY EXPECTED: "
       << r.get_nodes_analyzed() * sizeof(node) / 1024.0 << " kB"
       << "\tMEMORY MEASURED: " << (res - res_old) / 1024.0 << " kB"
       << std::endl;
  }
}

int main() {

 runnerValues values;
  firstMenu(values);
  run(values.getRunTimes(), values.getMode(), values.getHeuristic(), values.getDepth(), values.getFile(), std::cout);
  //run(5, iterative, none, 5, "./levels/level1.txt", std::cout);
}
