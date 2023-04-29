#pragma once

#include "grid.h"
#include "variables.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <utility>

using namespace std;


class PacmanState {
    public:

    enum Direction {
            right, up, left, down
        };    

    enum GameState { BASE, CHERRYONE, CHERRYTWO, POWERUP, FREIGHTENED };

    //************************ Constructor
    PacmanState() {
        pos = make_pair(13, 13);
        direction_facing = right;
        grid = {};
        pellets_eaten = 0;
        cherries_eaten = 0;
        powerups_eaten = 0;
    }

    PacmanState(std::pair<int, int> botPos, PacmanState::Direction pacDirection, std::vector<std::vector<int>> our_grid, int p_eaten, int c_eaten, int pu_eaten, GameState state) {
            
            pos = botPos; // retrieve from server
            direction_facing = pacDirection;
            grid = our_grid;
            pellets_eaten = p_eaten; // PELLETS_EATEN; 
            cherries_eaten = c_eaten; // CHERRIES_EATEN; // retrieve from server
            powerups_eaten = pu_eaten; // POWERUPS_EATEN; // retrieve from server
            our_game_state = state;
    }
    
    // void updateGrid(vector<vector<int>> new_grid) {
    //     grid = new_grid;
    // }

    vector<vector<int>> getGrid() {
        return grid;
    }

    void changeGrid(vector<vector<int>> grid, pair<int, int> prevPos, pair<int, int> newPos) { 
        if (prevPos.first == newPos.first && prevPos.second == newPos.second) return;

        // vector<vector<int>> newGrid = grid;
        grid[prevPos.first][prevPos.second] = v; 
        grid[newPos.first][newPos.second] = P; 
        // Grid::updateGrid(grid);
        // return newGrid; 
    }

    //************************ Position getter and setter 

    GameState getGameState() {
        return our_game_state;
    }

    void setGameState(GameState new_game_state) {
        our_game_state = new_game_state;
    }

    std::pair<int, int> getBotPos() {
        return pos;
    }
    
    void changePos(std::pair<int, int> new_pos) {
        pos = new_pos;
    }

    Direction getDirection() {
        return direction_facing;
    }

    int getPelletsEaten() {
        return pellets_eaten;
    }

    void setPelletsEaten(int new_pellets_eaten) {
        pellets_eaten = new_pellets_eaten;
    }

    int getCherriesEaten() {
        return cherries_eaten;
    }

    void setCherriesEaten(int new_cherries_eaten) {
        cherries_eaten = new_cherries_eaten;
    }

    int getPowerupsEaten() {
        return powerups_eaten;
    }

    void setPowerupsEaten(int new_powerups_eaten) {
        powerups_eaten = new_powerups_eaten;
    }

    int getCherryTimeLeft() {
        return cherry_time_left;
    }

    void setCherryTimeLeft(int new_time_left) {
        cherry_time_left = new_time_left;
    }

    int getFrieghtenedTimeLeft() {
        return freightened_time_left;
    }

    void setFrieghtenedTimeLeft(int new_time_left) {
        freightened_time_left = new_time_left;
    }

    //**************************

    //*******************Pellet getter and setter
    // int getPelletsEaten() {
    //     return pellets_eaten;
    // }

    // void setPelletsEaten(int new_pellets_eaten) {
    //     pellets_eaten = new_pellets_eaten;
    // }
    
   //************************ Direction getter and setter
    // Direction getDirection() {
    //     return direction_facing;
    // }

    void setDirection(Direction d) {
        direction_facing = d;
    }
    //************************

    //************************ Other stuff
    // double get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b);
    // std::vector<std::pair<int, int>> find_possible_moves();
    // bool is_move_legal(std::pair<int, int> move);
    // void movePlayer(std::pair<int, int> move);
    // bool hasCollided(std::vector<std::pair<int, int>> ghostLocs);
    // void introduceCherry();
    //************************
private:

    GameState our_game_state;

    // int score;
    std::pair<int, int> pos;
    // int lives;

    // bool gameover = false;
    // *************************  Data for pellets, powerups and cherries
    // int pellets_left;
    int pellets_eaten;
    int cherries_eaten;
    int powerups_eaten; 

    //***************************
  // cherry time
    
    //********************************** Direction and grid
    
    Direction direction_facing;

    std::vector<std::vector<int>> grid;

    int freightened_time_left = 0;

    int cherry_time_left = 0;
    
   //*********************/

    // //************************
    //                              // Bottom Left
        //    vector<vector<int>> grid  =  {{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
        //                                 {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
        //                                 {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I}, // 5
        //                                 {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
        //                                 {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I}, // 10
        //                                 {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I},
        //                                 {I,o,I,I,I,I,I,v,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
        //                                 {I,o,I,I,I,I,I,P,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
        //                                 {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I}, // 15
        //                                 {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
        //                                 {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I}, // 20
        //                                 {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
        //                                 {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
        //                                 {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I}, // 25
        //                                 {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
        //                                 {I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}};
    //                            //        |         |         |         |         |         |         |
    //                            //        0         5         10        15       20         25        30
};
