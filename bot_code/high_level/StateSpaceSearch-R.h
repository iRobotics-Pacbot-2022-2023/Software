#pragma once

#include "variables.h"
#include "grid.h"
#include "PacmanState.h"
#include "Ghost.h"

#include "BFS.h"
#include "AStar.h"

#include <vector>
#include <utility>
#include <queue>
#include <map>
#include <set>
#include <cmath>

class StateSpaceSearchR {
    public:

        enum GameState { BASE, CHERRYONE, CHERRYTWO, POWERUP, FREIGHTENED };

        void updateGameState(GameState state);

        GameState getGameState();

        // BASE state
        struct baseNode {
            pair<int, int> pacman_pos; // first = x, second - y
            vector<vector<int, int>> grid;
            int points; // pellets collected & distance to ghosts
            int heuristic;
            int totalCost;
            // node* parent;
        };

        

    private:

        GameState state = BASE;

        

};