#pragma once

#include "variables.h"

#include <vector>
#include <utility>
#include <queue>
#include <map>
#include <set>
#include <string>


using namespace std;


vector<pair<int, int>> bfsPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid);

vector<pair<int, int>> bfsPathMultiple(pair<int, int> start, set<pair<int, int>> goals, vector<vector<int>> grid);

vector<pair<int, int>> bfsPathUnkownGoal(pair<int, int> start, int goal, vector<vector<int>> grid);

map<string, vector<pair<int, int>>> bfsCherryOne(pair<int, int> start, vector<vector<int>> grid);

vector<pair<int, int>> getNeighbors(pair<int, int> node, vector<vector<int>> grid);

