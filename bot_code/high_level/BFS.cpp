
#include "BFS.h"

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

vector<pair<int, int>> BFS::bfsPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid) {
    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1); // start doesn't have a parent so we set it to (-1, -1)

    queue<pair<int, int>> queue;
    queue.push(start);

    while (!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (current == goal) { // current.x = goal.x && current.y = goal.y
            
            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            return path;

        }

        vector<pair<int, int>> neighbors = getNeighbors(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return {};
}

vector<pair<int, int>> BFS::bfsPathMultiple(pair<int, int> start, set<pair<int, int>> goals, vector<vector<int>> grid) {
    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1);

    queue<pair<int, int>> queue;
    queue.push(start);

    while (!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (goals.find(current) == goals.end()) { // current.x = goal.x && current.y = goal.y
            
            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            return path;
        }

        vector<pair<int, int>> neighbors = getNeighbors(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return {};
}

vector<pair<int, int>> BFS::getNeighbors(pair<int, int> node, vector<vector<int>> grid) {
    // grid range:
    // x : [0, 27]
    // y :[0, 30]

    vector<pair<int, int>> neighbors;
    neighbors[0] = make_pair(node.first - 1, node.second); // left
    neighbors[1] = make_pair(node.first, node.second - 1); // down
    neighbors[2] = make_pair(node.first + 1, node.second); // right
    neighbors[3] = make_pair(node.first, node.second + 1); // up
    
    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[0];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || y > 27 || y < 0 || y > 20 
            || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n) neighbors.erase(neighbors.begin()); 
        else i++;
    }

    return neighbors;
}