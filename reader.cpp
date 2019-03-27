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

	return retLevel;
}