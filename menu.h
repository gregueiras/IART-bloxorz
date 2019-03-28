#pragma once
#include "runner.h"
#include "reader.h"


class runnerValues {
	std::string file;
	mode mode_;
	heuristic heuristic_;
	int depth;
	int runTimes;
	bool steps;
public : 
	runnerValues() {
		this->depth = NULL;
	};
	void setFile(int fileNumber);
	void setMode(int modeNumber);
	void setHeuristic(int heuristicNumber);
	void setDepth(int depth);
	void setRunTimes(int runTimes);
	void setSteps(bool steps);
	std::string getFile() { return this->file; };
	mode getMode() { return this->mode_; };
	heuristic getHeuristic() { return heuristic_; }
	int getDepth() { return this->depth; };
	int getRunTimes() { return this->runTimes; };
	bool getSteps() { return this->steps;  }


};

bool firstMenu(runnerValues &values);

bool chooseNumberRuns(runnerValues &values);

bool chooseLevelMenu(runnerValues &values);

bool chooseAlgorithmMenu(runnerValues &values);

bool chooseHeuristicMenu(runnerValues &values);

bool chooseHeuristicMenu(runnerValues &values);

bool chooseIterativeDepthMenu(runnerValues &values);
