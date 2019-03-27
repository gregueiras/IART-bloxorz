#pragma once
#include "runner.h"
#include "reader.h"


class runnerValues {
	Level level;
	mode mode;
	heuristic heuristic;
	int depth;
public : 
	runnerValues() {
		this->depth = 0;
	};
	void setLevel(int levelNumber);
	void setMode(int modeNumber);
	void setHeuristic(int heuristicNumber);
	void setDepth(int depth);
};

void firstMenu(runnerValues &values);

void chooseLevelMenu(runnerValues &values);

void chooseAlgorithmMenu(runnerValues &values);

void chooseHeuristicMenu(runnerValues &values);

void chooseHeuristicMenu(runnerValues &values);

void chooseIterativeDepthMenu(runnerValues &values);