#include "AStar.h"

#include "variables.h"

/*

const int I = 1; // WALL
const int o = 2; // Pellet
const int e = 3; // unreachable
const int O = 4; // power point
const int n = 5; // untouchable
const int P = 6; // Pacbot
const int empty = 7; // No pellets here

*/


vector<pair<int, int>> AStar::aStarPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid) {
    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1);

    queue<pair<int, int>> queue;
    queue.push(start);

    while (!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (current == goal) { // current.first = goal.first && current.second = goal.second
            
            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            return path;

        }

        vector<pair<int, int>> neighbors = getNeighborsAStar(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return {};

}




vector<pair<int, int>> AStar::getNeighborsAStar(pair<int, int> node, vector<vector<int>> grid) {
    // grid range:
    // x : [0, 27]
    // y :[0, 30]

    vector<pair<int, int>> neighbors;
    neighbors.push_back(make_pair(node.first - 1, node.second)); // left
    neighbors.push_back(make_pair(node.first, node.second - 1)); // down
    neighbors.push_back(make_pair(node.first + 1, node.second)); // right
    neighbors.push_back(make_pair(node.first, node.second + 1)); // up
    
    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[i];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || y > 27 || y < 0 || y > 20 
            || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n) neighbors.erase(neighbors.begin() + i); 
        else i++;
    }

    return neighbors;
}

int AStar::euclideanDistance(pair<int, int> start, pair<int, int> goal) {
    return pow(start.first - goal.first, 2) + pow(start.second - goal.second, 2);
}