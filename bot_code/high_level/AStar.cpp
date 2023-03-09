#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>

using namespace std;

// Function declarations
vector<int> a_star(unordered_map<int, unordered_map<int, int>> &graph, int start, int goal);
double heuristic(int node, int goal);

int main() {
    // Example graph
    unordered_map<int, unordered_map<int, int>> graph = {
        {0, {{1, 5}, {2, 3}, {3, 2}}},
        {1, {{0, 5}, {2, 2}, {4, 3}}},
        {2, {{0, 3}, {1, 2}, {3, 9}, {4, 2}}},
        {3, {{0, 2}, {2, 9}, {5, 1}}},
        {4, {{1, 3}, {2, 2}, {5, 7}}},
        {5, {{3, 1}, {4, 7}}}
    };

    // Find shortest path from node 0 to node 5
    vector<int> path = a_star(graph, 0, 5);

    // Print result
    if (path.empty()) {
        cout << "No path found" << endl;
    } else {
        cout << "Shortest path: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}

vector<int> a_star(unordered_map<int, unordered_map<int, int>> &graph, int start, int goal) {
    // Initialize data structures
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> open_set;
    unordered_map<int, int> came_from;
    unordered_map<int, double> g_score = {{start, 0}};
    unordered_map<int, double> f_score = {{start, heuristic(start, goal)}};
    open_set.push(make_pair(f_score[start], start));

    // Loop until we find the goal or exhaust all possibilities
    while (!open_set.empty()) {
        // Get the node with the lowest f-score from the open set
        int current = open_set.top().second;
        open_set.pop();

        // Check if we've reached the goal
        if (current == goal) {
            vector<int> path = {current};
            while (came_from.count(current)) {
                current = came_from[current];
                path.push_back(current);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors
        for (auto neighbor : graph[current]) {
            int neighbor_node = neighbor.first;
            int neighbor_dist = neighbor.second;

            // Calculate tentative g-score
            double tentative_g_score = g_score[current] + neighbor_dist;

            // If neighbor is not in open set, add it
            if (!g_score.count(neighbor_node) || tentative_g_score < g_score[neighbor_node]) {
                came_from[neighbor_node] = current;
                g_score[neighbor_node] = tentative_g_score;
                f_score[neighbor_node] = tentative_g_score + heuristic(neighbor_node, goal);
                open_set.push(make_pair(f_score[neighbor_node], neighbor_node));
            }
        }
    }

    // No path found
    return vector<int>();
}

double heuristic(int node, int goal) {
    // Calculates the Euclidean distance between the node and the goal node
    unordered_map<int, pair<int, int>> coordinates = {
        {0, {0,
