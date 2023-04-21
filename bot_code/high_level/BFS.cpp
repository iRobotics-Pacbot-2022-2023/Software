
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

vector<pair<int, int>> BFS::bfsPathUnkownGoal(pair<int, int> start, int goal, vector<vector<int>> grid) {
    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1);

    queue<pair<int, int>> queue;
    queue.push(start);

    while(!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (grid[current.first][current.second] == goal) {

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

// we r finding the distance to the cherry pos and nearest pellet
map<string, vector<pair<int, int>>> BFS::bfsCherryOne(pair<int, int> start, vector<vector<int>> grid) {
    int pellet = o;
    pair<int, int> cherry_pos = make_pair(13, 13);

    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1);

    queue<pair<int, int>> queue;
    queue.push(start);

    bool checking_for_pellet = true;
    bool checking_for_cherry = true;

    map<string, vector<pair<int, int>>> paths = {};

    while(!queue.empty() && (checking_for_pellet || checking_for_cherry)) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (checking_for_pellet && grid[current.first][current.second] == pellet
            && checking_for_cherry && current == cherry_pos) {
            checking_for_pellet = false;
            checking_for_cherry = false;

            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            paths.insert(make_pair("pellet", path));
            paths.insert(make_pair("cherry", path));

            break;
        }

        if (checking_for_pellet && grid[current.first][current.second] == pellet) {
            checking_for_pellet = false;

            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            paths.insert(make_pair("pellet", path));

        }

        if (checking_for_cherry && current == cherry_pos) {
            checking_for_cherry = false;
            
            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            paths.insert(make_pair("cherry", path));
        }

        vector<pair<int, int>> neighbors = getNeighbors(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return paths;

}

vector<pair<int, int>> BFS::getNeighbors(pair<int, int> node, vector<vector<int>> grid) {
    // grid range:v
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
        if (x < 0 || x > 27 || y > 30 || y < 0 || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n) {
            neighbors.erase(neighbors.begin() + i);
        } 
        else {
            i++;
        }
    }

    return neighbors;
}