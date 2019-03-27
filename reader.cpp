#include "reader.h"

using namespace std;

Level readToLevel(string filePath) {
	ifstream input(filePath);
	string comma;
	string element;
	Level retLevel;

	input >> retLevel.num_rows >> comma >> retLevel.num_columns;
	while (input >> element) {
		retLevel.level_map.push_back(stoi(element));
	}

	if (retLevel.level_map.size() != retLevel.num_rows * retLevel.num_columns)
		cout << "Level loaded has inconsistent values.\n";

	return retLevel;
}