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
    //************************ Constructor
    PacmanState();
    PacmanState(std::pair<int, int> botPos, PacmanState::Direction pacDirection, std::vector<std::vector<int>> grid, int pelletsLeft, int pellets_eat, int cherries_eat, int powerups);
    
    void updateGrid(vector<vector<int>> new_grid); // GET FROM SYSTEM
    vector<vector<int>> getGrid();

    //************************ Position getter and setter 
    std::pair<int, int> getBotPos();
    void changePos(std::pair<int, int> new_pos);
    //**************************

    //*******************Pellet getter and setter
    int getPelletsEaten() {
        return pellets_eaten;
    }

    void setPelletsEaten(int new_pellets_eaten) {
        pellets_eaten = new_pellets_eaten;
    }
    
   //************************ Direction getter and setter
    Direction getDirection() {
        return direction_facing;
    }

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

    // int score;
    std::pair<int, int> pos;
    // int lives;

    bool gameover = false;
    // *************************  Data for pellets, powerups and cherries
    int pellets_left;
    int pellets_eaten;
    int cherries_eaten;
    int powerups_eaten; 

    //***************************
  // cherry time
    
    //********************************** Direction and grid
    
    Direction direction_facing;

    std::vector<std::vector<int>> grid;
    
   //*********************/
    // Position, gameover, pellets/cherries/powerups, direction_facing, grid
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
