#pragma once

#include "grid.h"
#include "variables.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <utility>



class PacmanState {
    public:
    enum Direction {
            right, up, left, down
        };    
    
private:

    // int score;
    std::pair<int, int> pos;
    // int lives;

    bool gameover = false;
    // *************************  Data for pellets, powerups and cherries
    int pellets_left;
    int pellets_eaten;
    int cherries_eaten;
    int prev_powerups_eaten; // update after we change state (+1) (POWERUP -> FREIGHTENED)
    int curr_powerups_eaten; // update after we eat a powerup (+1)
    //***************************
  // cherry time
    
    //********************************** Direction and grid
    
    Direction direction_facing = up;
    void updateGrid(vector<vector<int>> new_grid) { grid = new_grid; } // GET FROM SYSTEM
    vector<vector<int>> getGrid() { return grid; }
   //*********************/
    // Position, gameover, pellets/cherries/powerups, direction_facing, grid
public:
    //************************ Constructor
    PacmanState();
    PacmanState(std::pair<int, int> botPos) {
        // score = 0; // retrieve from server
        // lives = 3; // retrieve from server
        gameover = false; // retrieve from server
        pos = botPos; // retrieve from server
        pellets_left = 0; // retrieve from server
        pellets_eaten = 0; // retrieve from server
        cherries_eaten = 0; // retrieve from server
        prev_powerups_eaten = 0; // retrieve from server
        curr_powerups_eaten = 0; // retrieve from server
    }
    
    //************************
                                 // Bottom Left
<<<<<<< HEAD
           vector<vector<int>> grid =  {{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
=======
           vector<vector<int>> grid  =  {{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
>>>>>>> 5dc61725c88512c6a127e055262389e64cdc354f
                                        {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
                                        {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I}, // 5
                                        {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
                                        {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
                                        {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I}, // 10
                                        {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I},
                                        {I,o,I,I,I,I,I,v,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
                                        {I,o,I,I,I,I,I,P,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
                                        {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I}, // 15
                                        {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
                                        {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I}, // 20
                                        {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
                                        {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                        {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I}, // 25
                                        {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
                                        {I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}};
                               //        |         |         |         |         |         |         |
                               //        0         5         10        15       20         25        30

    //************************ Position getter and setter 
    std::pair<int, int> getBotPos() { return pos; }
    void changePos(std::pair<int, int> new_pos) {
        pos = new_pos;
    }
    //**************************

    //*******************Pellet getter and setter
    int getPelletsEaten() {
        return pellets_eaten;
    }

    void setPelletsEaten(int new_pellets_eaten) {
        pellets_eaten = new_pellets_eaten;
    }
    //*****************************

    //************************Cherry getter and setter
    int getCherriesEaten() {
        return cherries_eaten;
    }

    void setCherriesEaten(int new_cherries_eaten) {
        cherries_eaten = new_cherries_eaten;
    }
    //************************

    //************************ Prepowerup getter and setter
    void setPrePowerUpsEaten(int new_powerups_eaten) {
        prev_powerups_eaten = new_powerups_eaten;
    }

    int getPrePowerUpsEaten() {
        return prev_powerups_eaten;
    }
    //************************
    //*********************** Currpowerup getter and setter
    void setCurrPowerUpsEaten(int new_powerups_eaten) {
        curr_powerups_eaten = new_powerups_eaten;
    }

    int getCurrPowerUpsEaten() {
        return curr_powerups_eaten;
    }
    //************************
   //************************ Direction getter and setter
    Direction getDirection() {
        return direction_facing;
    }

    void setDirection(Direction d) {
        direction_facing = d;
    }
    //************************

    //************************ Other stuff
    double get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b);
    std::vector<std::pair<int, int>> find_possible_moves();
    bool is_move_legal(std::pair<int, int> move);
    void movePlayer(int dx, int dy);
    bool hasCollided();
    void introduceCherry();
    //************************
};
