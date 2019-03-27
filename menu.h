#pragma once
#include "runner.h"
#include "reader.h"


class runnerValues {
	std::string file;
	mode mode_;
	heuristic heuristic_;
	int depth;
	int runTimes;
public : 
	runnerValues() {
		this->depth = NULL;
	};
	void setFile(int fileNumber);
	void setMode(int modeNumber);
	void setHeuristic(int heuristicNumber);
	void setDepth(int depth);
	void setRunTimes(int runTimes);
	std::string getFile() { return this->file; };
	mode getMode() { return this->mode_; };
	heuristic getHeuristic() { return heuristic_; }
	int getDepth() { return this->depth; };
	int getRunTimes() { return this->runTimes; };


};

void firstMenu(runnerValues &values);

void chooseLevelMenu(runnerValues &values);

void chooseAlgorithmMenu(runnerValues &values);

void chooseHeuristicMenu(runnerValues &values);

void chooseHeuristicMenu(runnerValues &values);

void chooseIterativeDepthMenu(runnerValues &values);

void chooseNumberRuns(runnerValues &values);