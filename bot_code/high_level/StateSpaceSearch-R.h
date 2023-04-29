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

        StateSpaceSearchR(PacmanState p, Ghost red, Ghost blue, Ghost orange, Ghost pink, vector<vector<int>> g) {

            red_ghost = red;
            pacman = p;
            red_ghost = red;
            blue_ghost = blue;
            orange_ghost = orange;
            pink_ghost = pink;
            grid = g;
        }

        // enum GameState { BASE, CHERRYONE, CHERRYTWO, POWERUP, FREIGHTENED };

        void updateGameState();

        PacmanState::GameState getGameState() { return pacman.getGameState(); }

        void changeGameState(PacmanState::GameState s) { pacman.setGameState(s); }

        // Direction 


        void updatePacmanDir(PacmanState::Direction newDir) { pacman_dir = newDir; }

        PacmanState::Direction getPacmanDir() { return pacman_dir; }

        // Position

        pair<int, int> getPacmanPos() { return pacman.getBotPos(); }
        void setPacman(PacmanState p) {pacman = p;}
        void setRedGhost(Ghost r){red_ghost = r;}

        vector<vector<int>> getGrid() { return grid; }
        Ghost getRed() {return red_ghost;}

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
            Ghost::Direction red_ghost_dir;
            pair<int, int> blue_ghost_pos;
            Ghost::Direction blue_ghost_dir;
            pair<int, int> orange_ghost_pos;
            Ghost::Direction orange_ghost_dir;
            pair<int, int> pink_ghost_pos;
            Ghost::Direction pink_ghost_dir;

            vector<vector<int>> grid;
            int points; // pellets collected & distance to ghosts
            int depth; // depth of parent = 0

            bool operator<(const BaseNode& other) const {
                if (points < other.points) return true;
                if (depth < other.depth) return true;
                if (pacman_pos.first < other.pacman_pos.first) return true;
                if (pacman_pos.second < other.pacman_pos.second) return true;
                if (red_ghost_pos.first < other.red_ghost_pos.first) return true;
                if (red_ghost_pos.second < other.red_ghost_pos.second) return true;
                if (blue_ghost_pos.first < other.blue_ghost_pos.first) return true;
                if (blue_ghost_pos.second < other.blue_ghost_pos.second) return true;
                if (orange_ghost_pos.first < other.orange_ghost_pos.first) return true;
                if (orange_ghost_pos.second < other.orange_ghost_pos.second) return true;
                if (pink_ghost_pos.first < other.pink_ghost_pos.first) return true;
                if (pink_ghost_pos.second < other.pink_ghost_pos.second) return true;
                else return false;
            }
            bool operator==(const BaseNode& other) const {
                return (points == other.points && depth == other.depth && pacman_pos == other.pacman_pos && 
                pacman_dir == other.pacman_dir && red_ghost_pos == other.red_ghost_pos && red_ghost_dir == other.red_ghost_dir
                && blue_ghost_pos == other.blue_ghost_pos && blue_ghost_dir == other.blue_ghost_dir && orange_ghost_pos == other.orange_ghost_pos
                && orange_ghost_dir == other.orange_ghost_dir && pink_ghost_pos == other.pink_ghost_pos && pink_ghost_dir == other.pink_ghost_dir
                && grid == other.grid);
            }
            bool operator!=(const BaseNode& other) const {
                return !(*this == other);
            }
            BaseNode& operator=(const BaseNode& other) {
                if (this != &other) {
                    pacman_pos = other.pacman_pos;
                    pacman_dir = other.pacman_dir;
                    red_ghost_pos = other.red_ghost_pos;
                    red_ghost_dir = other.red_ghost_dir;
                    blue_ghost_pos = other.blue_ghost_pos;
                    blue_ghost_dir = other.blue_ghost_dir;
                    orange_ghost_pos = other.orange_ghost_pos;
                    orange_ghost_dir = other.orange_ghost_dir;
                    pink_ghost_pos = other.pink_ghost_pos;
                    pink_ghost_dir = other.pink_ghost_dir;
                    grid = other.grid;
                    points = other.points;
                    depth = other.depth;
                }
                return *this;
            }
            // bool cherry_eaten;
            // bool powerup_eaten;

            // bool operator<(const BaseNode& other) const {
            //     if (x < other.x) {
            //     return true;
            //     } else if (x == other.x) {
            //     return y < other.y;
            //     } else {
            //     return false;
            //     }
            // }
        };

        /*
        
        PacmanState p; // pacman_pos, pacman_dir, grid
        Ghost red; // red_ghost_pos, red_ghost_dir
        Ghost blue; // blue_ghost_pos, blue_ghost_dir
        Ghost orange; // orange_ghost_pos, orange_ghost_dir
        Ghost pink; // pink_ghost_pos, pink_ghost_dir
        
        */

        bool baseNodeEquals(BaseNode a, BaseNode b);

        // FREIGHTENED state
        struct FreightenedNode {
            pair<int, int> pacman_pos; // first = x, second - y
            PacmanState::Direction pacman_dir;

            pair<int, int> red_ghost_pos;
            Ghost::Direction red_ghost_dir;
            Ghost::GhostState red_ghost_state;

            pair<int, int> blue_ghost_pos;
            Ghost::Direction blue_ghost_dir;
            Ghost::GhostState blue_ghost_state;

            pair<int, int> orange_ghost_pos;
            Ghost::Direction orange_ghost_dir;
            Ghost::GhostState orange_ghost_state;

            pair<int, int> pink_ghost_pos;
            Ghost::Direction pink_ghost_dir;
            Ghost::GhostState pink_ghost_state;

            vector<vector<int>> grid;
            int points; // pellets collected & distance to ghosts
            int depth; // depth of parent = 0

            bool operator<(const FreightenedNode& other) const {
                if (points < other.points) return true;
                if (depth < other.depth) return true;
                if (pacman_pos.first < other.pacman_pos.first) return true;
                if (pacman_pos.second < other.pacman_pos.second) return true;
                if (red_ghost_pos.first < other.red_ghost_pos.first) return true;
                if (red_ghost_pos.second < other.red_ghost_pos.second) return true;
                if (blue_ghost_pos.first < other.blue_ghost_pos.first) return true;
                if (blue_ghost_pos.second < other.blue_ghost_pos.second) return true;
                if (orange_ghost_pos.first < other.orange_ghost_pos.first) return true;
                if (orange_ghost_pos.second < other.orange_ghost_pos.second) return true;
                if (pink_ghost_pos.first < other.pink_ghost_pos.first) return true;
                if (pink_ghost_pos.second < other.pink_ghost_pos.second) return true;
                else return false;
            }
            // bool cherry_eaten;
            // bool powerup_eaten;
        };

        bool freightenedNodeEquals(FreightenedNode a, FreightenedNode b);

        int euclideanDistance(pair<int, int> start, pair<int, int> goal);

        vector<pair<int, int>> getNeighborsBase(pair<int, int> pos, vector<vector<int>> grid);

        vector<pair<int, int>> getNeighborsCherryOne(pair<int, int> pos, vector<vector<int>> grid);

        vector<pair<int, int>> getNeighborsPowerUp(pair<int, int> pos, vector<vector<int>> grid);

        void updateFreightenedTimeLeft(int time) { freightened_time_left = time; }

        int getFreightenedTimeLeft() { return freightened_time_left; }

        // //************************ Prepowerup getter and setter
        // void setPrevPowerUpsEaten(int new_powerups_eaten) {
        //     prev_powerups_eaten = new_powerups_eaten;
        // }

        // int getPrevPowerUpsEaten() {
        //     return prev_powerups_eaten;
        // }
        // //************************
        // //*********************** Currpowerup getter and setter
        // void setCurrPowerUpsEaten(int new_powerups_eaten) {
        //     curr_powerups_eaten = new_powerups_eaten;
        // }

        // int getCurrPowerUpsEaten() {
        //     return curr_powerups_eaten;
        // }

        // //************************Prev Cherry getter and setter
        // int getPrevCherriesEaten() {
        //     return prev_cherries_eaten;
        // }

        // void setPrevCherriesEaten(int new_cherries_eaten) {
        //     prev_cherries_eaten = new_cherries_eaten;
        // }

        // //************************Curr Cherry getter and setter
        // int getCurrCherriesEaten() {
        //     return curr_cherries_eaten;
        // }

        // void setCurrCherriesEaten(int new_cherries_eaten) {
        //     curr_cherries_eaten = new_cherries_eaten;
        // }

        /////////////////////////////////////////////////////////// GHOST ////////////////////////////////////////////////////////////

        enum GhostDirection {
            right, up, left, down
        };

        enum GhostColor {
            red, blue, pink, orange
        };

        enum GhostState {
            frightened, chase, scatter
        };


        // BFS

        vector<pair<int, int>> bfsPathMultiple(pair<int, int> start, set<pair<int, int>> goals, vector<vector<int>> grid);

        vector<pair<int, int>> bfsPathUnkownGoal(pair<int, int> start, int goal, vector<vector<int>> grid);

        map<string, vector<pair<int, int>>> bfsCherry(bool check_nearest_pellet, pair<int, int> start, vector<vector<int>> grid);

        vector<pair<int, int>> getNeighborsBFS(pair<int, int> node, vector<vector<int>> grid);

        vector<pair<int, int>> bfsPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid);

    private:

        PacmanState pacman;

        Ghost red_ghost;

        Ghost blue_ghost;

        Ghost orange_ghost;

        Ghost pink_ghost;

        // PacmanState::GameState state = pacman.getGameState();

        pair<int, int> pacman_pos = pacman.getBotPos();

        PacmanState::Direction pacman_dir = pacman.getDirection();

        pair<int, int> red_ghost_pos = red_ghost.getGhostLocation();

        Ghost::Direction red_ghost_dir = red_ghost.getGhostDirection();

        Ghost::GhostState red_ghost_state = red_ghost.getGhostState();

        pair<int, int> blue_ghost_pos = blue_ghost.getGhostLocation();

        Ghost::Direction blue_ghost_dir = blue_ghost.getGhostDirection();

        Ghost::GhostState blue_ghost_state = blue_ghost.getGhostState();

        pair<int, int> orange_ghost_pos = orange_ghost.getGhostLocation();

        Ghost::Direction orange_ghost_dir = orange_ghost.getGhostDirection();

        Ghost::GhostState orange_ghost_state = orange_ghost.getGhostState();

        pair<int, int> pink_ghost_pos = pink_ghost.getGhostLocation();

        Ghost::Direction pink_ghost_dir = pink_ghost.getGhostDirection();

        Ghost::GhostState pink_ghost_state = pink_ghost.getGhostState();

        vector<vector<int>> grid;

        int pellets_eaten = pacman.getPelletsEaten();

        int freightened_time_left = 0;

        int powerups_eaten = pacman.getPowerupsEaten(); // retrieve from server

        // int curr_powerups_eaten = prev_powerups_eaten;

        int cherries_eaten = pacman.getCherriesEaten(); // retrieve from server

        // int curr_cherries_eaten = prev_cherries_eaten;

        set<pair<int, int>> POWER_POINTS_LOCATIONS = {{1, 7}, {1, 27}, {26, 7}, {26, 27}};


};