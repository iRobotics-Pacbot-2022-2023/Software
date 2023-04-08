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
    int score;
    std::pair<int, int> pos;
    int lives;
    int level;
    bool gameover = false;
    //red, orange, blue, pink
                                                              //

    int power_up_weight = 50;
    int power_ups_left; //power ups remaining

    int pellet_weight = 10;
    int pellets_left;
    // int ghost_score;
    enum direction {
        right, up, left, down, upperRight, upperLeft, lowerRight, lowerLeft
    };
    direction direction_facing;
    bool chase = true;
    bool scatter = false;
    // void moveRedChase();
    // void moveOrangeChase();
    // void moveBlueChase();
    // void movePinkChase();

    // void moveBlueScatter();
    // void moveRedScatter();
    // void moveOrangeScatter();
    // void movePinkScatter();
public:
    PacmanState() {
        score = 0;
        lives = 3;
        level = 1;
        gameover = false;
        // xbotPos = 0;
        // ybotPos = 0;
        
    }


    std::pair<int, int> getBotPos();

    int getX();
    int getY();

    void changeX(int new_x);
    void changeY(int new_y);
    void increaseScore(int points) {
        score += points;
    }

    void decreaseLives() {
        lives--;
        if (lives == 0) {
            gameover = true;
        }
    }

    void nextLevel() {
        level++;
    }

    void gameOver() {
        gameover = true;
    }

    bool isGameOver() {
        return gameover;
    }

    int getScore() {
        return score;
    }

    int getLives() {
        return lives;
    }

    int getLevel() {
        return level;
    }
    void getDirection() {
        return direction_facing;
    }
    void setDirection(direction d) {
        direction_facing = d;
    }
    double get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b);
    std::vector<std::pair<int, int>> find_possible_moves();
    bool is_move_legal(std::pair<int, int> move);

    void movePlayer(double dx, double dy);
    bool hasCollided();
    void moveOrange();
    void moveRed();
    void movePink();
    void moveBlue();
};
