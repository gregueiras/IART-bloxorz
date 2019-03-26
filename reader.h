#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Level {
	unsigned int num_columns;
	unsigned int num_rows;
	unsigned int level_number;
	std::vector<int> level_map;
};

Level readToLevel(std::string filePath);

