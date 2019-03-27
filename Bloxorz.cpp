// Bloxorz.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include "levels.h"
#include "operators.h"
#include "windows.h"
#include "psapi.h"
#include "runner.h"
#include "reader.h"
#define WIN32_LEAN_AND_MEAN

void run(int n, mode mode, heuristic heuristic, std::string file, std::ostream & os) {
	auto lvl = readToLevel(file);

	auto r =
		runner(mode, heuristic, lvl.level_map, lvl.num_rows, lvl.num_columns);

	PROCESS_MEMORY_COUNTERS pmc;
	const auto myHandle = GetCurrentProcess();
	GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc));
	size_t res = pmc.WorkingSetSize;
	size_t res_old;
	bool steps = false; //Test agent steps to resolution
	if (steps) {
		node n;
		auto sol = r.run(1, n);
		if (GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc))) {
			res_old = res;
			res = (pmc.WorkingSetSize);
		}
		os << "TIME*50: " << sol << "\tNODES: " << r.getNodes_Analyzed()
			<< "\tMEMORY EXPECTED: " << r.getNodes_Analyzed() * sizeof(node) / 1024.0 << " kB"
			<< "\tMEMORY MEASURED: " << (res - res_old) / 1024.0 << " kB"
			<< std::endl;
	}

	else {
		for (auto i = 0; i < 10; ++i) {
			node n;
			auto sol = r.run(50, n);

			if (GetProcessMemoryInfo(myHandle, &pmc, sizeof(pmc))) {
				res_old = res;
				res = (pmc.WorkingSetSize);
			}
			os << "TIME*50: " << sol << "\tNODES: " << r.getNodes_Analyzed()
				<< "\tMEMORY EXPECTED: " << r.getNodes_Analyzed() * sizeof(node) / 1024.0 << " kB"
				<< "\tMEMORY MEASURED: " << (res - res_old) / 1024.0 << " kB"
				<< std::endl;
			}
		}
}

int main()
{
	run(5, a_star, manhattan_teletransport_distance, "./levels/level1.txt", std::cout);
}
