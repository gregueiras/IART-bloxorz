// Bloxorz.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include "levels.h"
#include "operators.h"
#include "windows.h"
#include "psapi.h"
#include "runner.h"
#define WIN32_LEAN_AND_MEAN

int main() {
  auto r =
      //runner(a_star, manhattan_teletransport_distance, LVL1, LVL1_R, LVL1_C);
      runner(dfs, LVL1, LVL1_R, LVL1_C);
  
  PROCESS_MEMORY_COUNTERS pmc;
  const auto myHandle = GetCurrentProcess();
  GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc));
  size_t res = pmc.WorkingSetSize;
  size_t res_old;

  for (auto i = 0; i < 10; ++i) {
    node n;
    auto sol = r.run(50, n);

    if (GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc))) {
      res_old = res;
      res = (pmc.WorkingSetSize);
    }
    std::cout << "TIME*50: " << sol << "\tNODES: " << r.getNodes_Analyzed()
              << "\tMEMORY EXPECTED: " << r.getNodes_Analyzed()*sizeof(node) / 1024.0 << " kB" 
              << "\tMEMORY MEASURED: " << (res - res_old) / 1024.0 << " kB"
              << std::endl;
  }
}