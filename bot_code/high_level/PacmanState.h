

#include <cstdlib>
#include "grid.h"
#include <vector>
#include <iostream>
#include <string>
#include "variables.h"
#include <cmath>
#pragma once


class PacmanState {
private:
    int score;
    // bool gameover;
    double xbotPos;
    double ybotPos;
    int lives;
    int level;
    bool gameover;

    // double x;
    // double y;

    // position by ghosts
    // int x_red;
    // int y_red;

    // int x_orange;
    // int y_orange;

    // int x_blue;
    // int y_blue;

    // int x_pink;
    // int y_pink;

    vector<double> ghostlocs = {14, 14, 14, 14, 14, 14, 14, 14}; //red, orange, blue, pink
                                                              //

    int power_up_weight;
    int power_ups_left; //power ups remaining

    int pellet_weight;
    int pellets_left;
    int ghost_score;
    enum direction {
        right, up, left, down, upperRight, upperLeft, lowerRight, lowerLeft;
    }
    direction direction_facing;
    void moveRedChase();
    void moveOrangeChase();
    void moveBlueChase();
    void movePinkChase();

    void moveBlueScatter();
    void moveRedScatter();
    void moveOrangeScatter();
    void movePinkScatter();
public:
    PacmanState() {
        score = 0;
        lives = 3;
        level = 1;
        gameover = false;
        x = 0;
        y = 0;
    }
    void changeX(int new_x) {
        x = new_x;
    }
    void changeY(int new_y) {
        y = new_y;
    }
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
        return direction;
    }
    void setDirection(int d) {
        direction = d;
    }
    void movePlayer(double dx, double dy);
    bool hasCollided();
    void moveOrange();
    void moveRed();
    void movePink();
    void moveBlue();
};
