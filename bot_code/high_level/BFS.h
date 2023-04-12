#pragma once

#include "variables.h"

#include <vector>
#include <utility>
#include <queue>
#include <map>
#include <set>


using namespace std;

class BFS {
private:

public:
    vector<pair<int, int>> bfsPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid);

    vector<pair<int, int>> bfsPathMultiple(pair<int, int> start, set<pair<int, int>> goals, vector<vector<int>> grid);

    vector<pair<int, int>> getNeighbors(pair<int, int> node, vector<vector<int>> grid);




};