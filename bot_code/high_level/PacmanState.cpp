#include "PacmanState.h"


PacmanState::PacmanState() {
        // score = 0;
        // lives = 3;
        gameover = false;
        pos.first = 14;
        pos.second = 7;
        // ghost_score = 200;
        // power_ups_left = 4;
        pellets_left = 236;
}

PacmanState::~PacmanState() {

}
std::pair<int, int> PacmanState::getBotPos() {
    return pos;
}

void PacmanState::movePlayer(double dx, double dy) {
     pos.first += dx;
    pos.second += dy; //not sure if thise will work
    if (dx > 0 && dy > 0) {
        direction  = upperRight;
    } else if (dx > 0 && dy == 0) {
        direction = right;
    } else if (dx > 0 && dy < 0) {
        direction = lowerRight;
    } else if (dx < 0 && dy > 0) {
        direction = upperLeft;
    } else if (dx < 0 && dy == 0) {
        direction = left;
    } else if (dx < 0 && dy < 0) {
        direction = lowerLeft;
    } else if (dx == 0 && dy > 0) {
            direction = up;
    } else {
        direction = down;
    }

    bool collision = hasCollided();
}
// int PacmanState::getX() {
//     return getBotPos().first;
// }

// int PacmanState::getY() {
//     return getBotPos().second;
// }

void PacmanState::changeX(int new_x) {
    pos.first = new_x;
}

void PacmanState::changeY(int new_y) {
    pos.second = new_x;
}

void PacmanState::updateScore(int points) {
        score = points;
    }
void PacmanState::decreaseLives() {
        // lives--;
        // if (lives == 0) {
        //     gameover = true;
        // }
}

void PacmanState::updateLevel(int levels) {
        // level++;
        level = levels;
    }
bool PacmanState::isGameOver() {
        // return gameover;
        return false;
    }

int PacmanState::getScore() {
        return score;
    }

    // int PacmanState::getLives() {
    //     return lives;
    // }

    // int PacmanState::getLevel() {
    //     return level;
    // }

    // void PacmanState::addPelletScore() {
    //     increaseScore(10);
    // }

    bool PacmanState::hasCollided() {
        for(int i = 0; i < ghostlocs.size(); i += 2) {
            if (ghostlocs[i].first == pos.first && ghostlocs[i].second == pos.second) {
                return true;
            }
        }
        return false;
    }
    // void PacmanState::addPowerUpScore() {
    //     increaseScore(50);
    // }

    // void PacmanState::addGhostScore() {
    //     increaseScore(ghost_score);
    //     ghost_score *= 2;
    // }
    // void PacmanState::addCherryScore() {
    //     increaseScore(100);
    // }

    void PacmanState::introduceCherry() {
        if (240 - pellets_left - power_ups_left == 170) {
            //introduce cherry at 13,13
        }
        if (240 - pellets_left - power_ups_left == 70) {
            //introduce cherry at 13, 13 again
        }
    }
    // void PacmanState::ateGhost() {
    //     addGhostScore();
    // }
    // void PacmanState::moveBlue() {
    //     if (chase) {
    //         moveBlueChase();
    //     } else {
    //         moveBlueScatter();
    //     }
    // }

    // void PacmanState::moveOrange() {
    //     if (chase) {
    //         moveOrangeChase();
    //     } else {
    //         moveOrangeScatter();
    //     }

    // }

    // void PacmanState::moveRed() {
    //     if (chase) {
    //         moveRedChase();
    //     } else {
    //         moveRedScatter();
    //     }
        
        

    // }

    // void PacmanState::movePink() {
    //     if (chase) {
    //         movePinkChase();
    //     } else {
    //         movePinkScatter();
    //     }


    // }


    // void PacmanState::moveOrangeChase() {
    //     int numPossOrangeMoves = 0;
    //     vector<string> directions;
    //     if ( grid[x_orange + 1][y_orange] != 'I' ) {
    //         directions.push_back("right");
    //     }
    //     if (grid[x_orange][y_orange - 1] != 'I') {
    //         directions.push_back("up");
    //     }
    //     if (grid[x_orange - 1][y_orange] != 'I') {
    //         directions.push_back("left");
    //     } 
    //     if (grid[x_orange][y_orange + 1] != 'I') {
    //         directions.push_back("down");
    //     }
    //     int ind = rand() % directions.size();
    //     string direction = directions[ind];
    //     if (direction == "left") {
    //         x_orange -= 1;
    //     } else if (direction == "up") {
    //         y_orange += 1;
    //     } else if (direction == "right") {
    //         x_orange += 1;
    //     } else {
    //         y_orange -= 1;
    //     }

    // }

    // void PacmanState::moveBlueChase()
    // {
    //     //Incomplete ideas; needs more work
    //     int xDiff = 0;
    //     int yDiff = 0;
    //     vector<string> directions;
    //     if (getDirection() == up)
    //     {
    //         xDiff = pos.second +  2;
    //     }
    //     if (getDirection() == down)
    //     {
    //         xDiff = pos.second - 2;
    //     }
    //     if (getDirection() == left)
    //     {
    //         xDiff = pos.first - 2;
    //     }
    //     if (getDirection() == right)
    //     {
    //         xDiff = pos.first + 2;
    //     }

    //     //Must account for chances that end result could be negative
    //     //Would be considered out of bounds
    //     int x_blue = abs(2 * (xDiff - x_red));
    //     int y_blue = abs(2 * (yDiff - y_red));


    //     if ( grid[x_blue + 1][y_blue] != 'I' ) {
    //         directions.push_back("right");
    //     }
    //     if (grid[x_blue][y_blue - 1] != 'I') {
    //         directions.push_back("up");
    //     }
    //     if (grid[x_blue - 1][y_blue] != 'I') {
    //         directions.push_back("left");
    //     } 
    //     if (grid[v_blue][y_blue + 1] != 'I') {
    //         directions.push_back("down");
    //     }
    //     //Needs more work
    // }

    // void PacmanState::moveRedChase() {
    //     vector<string> directions;
    //      if ( grid[x_red + 1][y_red] != 'I' ) {
    //         directions.push_back("right");
    //     }
    //     if (grid[x_orange][y_orange - 1] != 'I') {
    //         directions.push_back("up");
    //     }
    //     if (grid[x_orange - 1][y_orange] != 'I') {
    //         directions.push_back("left");
    //     } 
    //     if (grid[x_orange][y_orange + 1] != 'I') {
    //         directions.push_back("down");
    //     }
    //     int xDiff = xbotPos - x_red;
    //     int yDiff = ybotPos - y_red;

    //     if (xDiff <= 0 && yDiff <= 0) { //should also take into account what direction the Pacbot is facing, as that's the likely direction it's gonna go
           
    //         if (grid[x_red - 1][y_red] !=  'I' && grid[x_red ][y_red - 1] !- 'I') {
    //             if (xDiff < yDiff) {
    //                 x_orange -= 1;
    //             } 
    //         } else if (grid[x_red][y_red -1] != 'I' ) {
    //             if (yDiff < xDiff) {
    //                 y_orange -= 1;
    //             }
    //         }
            
    //     } else if (xDiff < 0 && yDiff > 0) {

    //     }
        

    // }

    // void PacmanState::movePinkChase() {
    //     if (direction_facing != up) {
    //         if (direction_facing == right) {
    //             double pinkTargetX = x + 4; // have to account for walls later
    //             double dx = pinkTargetX - x_pink;
    //             double dy = ybotPos - y_pink;
    //             if (abs(dx) > abs(dy) && dx > 0) {
    //                 x_pink += 1; // check for walls
    //             } else if (abs(dx) > abs(dy) && dx < 0) {
    //                 y_pink += 1; //have to check for walls
    //             } else if (abs(dx) < abs(dy) && dy > 0) {
    //                 y_pink -= 1;
    //             } else {
    //                 y_pink += 1;
    //             }

    //         } else if (direction_facing == down) {
    //             double pinkTargetY = ybotPos - 4; // have to account for walls later
    //             if (abs(dx) > abs(dy) && dx > 0) {
    //                 x_pink += 1;
    //             } else if (abs(dx) > abs(dy) && dx < 0) {
    //                 x_pink -= 1;
    //             } else if (abs(dx) < abs(dy) && dy < 0) {
    //                 x_pink += 1;
    //             } else  {
    //                 y_pink -= 1;
    //             }

    //         } else { // left
    //             double pinkTargetX = xbotPos - 4; //have to account for walls later
    //             if (abs(dx) > abs(dy) && dx > 0) {
    //                 y_pink += 1;
    //             } else if (abs(dx) > abs(dy) && dx < 0) {
    //                 x_pink -= 1;
    //             } else if (abs(dx) < abs(dy) && dy < 0) {
    //                 y_pink += 1;
    //             } else {
    //                 y_pink -= 1;
    //             }

    //         }

    //     } else {
    //         double pinkTargetX = xbotPos - 4;
    //         double pinkTargetY = ybotPos + 4;
    //         if (abs(dx) > abs(dy) && dx > 0) {
    //                 x_pink += 1;
    //             } else if (abs(dx) > abs(dy) && dx < 0) {
    //                 x_pink -= 1;
    //             } else if (abs(dx) < abs(dy) && dy < 0) {
    //                 y_pink += 1;
    //             } else if (abs(dx) < abs(dy) && dy > 0) {
    //                 y_pink -= 1;
    //             }

    //     }


    // }

    double PacmanState::get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b) {
        double dx = pos_b.first - pos_a.first;
        double dy = pos_b.second - pos_b.second;
        return std::sqrt(dx*dx + dy*dy);
    }


    std::vector<std::pair<int, int>> PacmanState::find_possible_moves() {
        int botx = pos.first;
        int boty = pos.second;

        std::pair<int, int> right = {botx + 1, boty};
        std::pair<int, int> up = {botx, boty + 1};
        std::pair<int, int> left = {botx - 1, boty};
        std::pair<int, int> down = {botx, boty - 1};

        std::vector<std::pair<int, int>> possible;

        if (is_move_legal(right)) {
            possible.push_back(right);
        }
        if (is_move_legal(up)) {
            possible.push_back(up);
        }
        if (is_move_legal(left)) {
            possible.push_back(left);
        }
        if (is_move_legal(down)) {
            possible.push_back(down);
        }
    }

    bool PacmanState::is_move_legal(std::pair<int, int> move, char[][]grid) {
        // how do i check the actual grid? perhaps we should have a private member for the grid?
        // psuedo for now
        return (move != pos && grid[move.first][move.second] != 'I' && grid[move.first][move.second] != 'n');
    } 

