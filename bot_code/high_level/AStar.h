#pragma once

#include "variables.h"

#include <vector>
#include <utility>
#include <queue>
#include <map>
#include <set>
#include <cmath>

using namespace std;

class AStar {
private:
    
public:

    vector<pair<int, int>> aStarPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid);

    vector<pair<int, int>> getNeighborsAStar(pair<int, int> node, vector<vector<int>> grid);

    int euclideanDistance(pair<int, int> start, pair<int, int> goal);

};