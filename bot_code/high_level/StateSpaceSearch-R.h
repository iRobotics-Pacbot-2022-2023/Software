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

        // void updateGameState(GameState newState) { state = newState; }

        void updateGameState();

        GameState getGameState() { return state; }

        void updatePacmanDir(PacmanState::Direction newDir) { pacman_dir = newDir; }

        PacmanState::Direction getPacmanDir() { return pacman_dir; }

        pair<int, int> getPacmanPos() { return PacmanState::getBotPos(); }

        vector<vector<int>> getGrid() { return grid; }

        // no need to update grid - just assign changeGrid to a new variable
        vector<vector<int>> changeGrid(vector<vector<int>> grid, pair<int, int> prevPos, pair<int, int> newPos) { 
            if (prevPos.first == newPos.first && prevPos.second == newPos.second) return grid;

            vector<vector<int>> newGrid = grid;
            newGrid[prevPos.first][prevPos.second] = v; 
            newGrid[newPos.first][newPos.second] = P; 
            // Grid::updateGrid(grid);
            return newGrid; 
        }

        vector<pair<int, int>> generatePath(int length); // main path

        vector<pair<int, int>> generatePathBase(int length);

        vector<pair<int, int>> generatePathCherryOne(int length);

        vector<pair<int, int>> generatePathCherryTwo(int length);

        vector<pair<int, int>> generatePathPowerUp(int length);

        vector<pair<int, int>> generatePathFreightened(int length);

        // BASE state
        struct BaseNode {
            pair<int, int> pacman_pos; // first = x, second - y
            PacmanState::Direction pacman_dir;
            pair<int, int> red_ghost_pos;
            pair<int, int> blue_ghost_pos;
            pair<int, int> orange_ghost_pos;
            pair<int, int> pink_ghost_pos;
            vector<vector<int>> grid;
            int points; // pellets collected & distance to ghosts
            int depth; // depth of parent = 0
        };

        // CHERRYONE state

        int euclideanDistance(pair<int, int> start, pair<int, int> goal);

        vector<pair<int, int>> getNeighborsBase(pair<int, int> pos, vector<vector<int>> grid);

        

    private:

        GameState state = BASE;

        PacmanState::Direction pacman_dir = PacmanState::getDirection();

        vector<vector<int>> grid = PacmanState::getGrid();


        

};