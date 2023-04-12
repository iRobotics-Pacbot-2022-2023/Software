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
private:

    // int score;

    std::pair<int, int> pos;
    
    // int lives;

    bool gameover = false;
    //red, orange, blue, pink


    int pellets_left;

    int pellets_eaten;

    int cherries_eaten;

    int prev_powerups_eaten; // update after we change state (+1) (POWERUP -> FREIGHTENED)

    int curr_powerups_eaten; // update after we eat a powerup (+1)

    // cherry time
    

    enum Direction {
        right, up, left, down, upperRight, upperLeft, lowerRight, lowerLeft
    };

    Direction direction_facing;
   
public:

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


    std::pair<int, int> getBotPos() { return pos; }

    void changePos(std::pair<int, int> new_pos) {
        pos = new_pos;
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

    void setPrePowerUpsEaten(int new_powerups_eaten) {
        prev_powerups_eaten = new_powerups_eaten;
    }

    int getPrePowerUpsEaten() {
        return prev_powerups_eaten;
    }

    void setCurrPowerUpsEaten(int new_powerups_eaten) {
        curr_powerups_eaten = new_powerups_eaten;
    }

    int getCurrPowerUpsEaten() {
        return curr_powerups_eaten;
    }

    // int getScore() {
    //     return score;
    // }

    // int getLives() {
    //     return lives;
    // }

    Direction getDirection() {
        return direction_facing;
    }

    void setDirection(Direction d) {
        direction_facing = d;
    }
    

    double get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b);

    std::vector<std::pair<int, int>> find_possible_moves();

    bool is_move_legal(std::pair<int, int> move);

    void movePlayer(double dx, double dy);

    bool hasCollided();

    // void moveOrange();
    // void moveRed();
    // void movePink();
    // void moveBlue();
};
