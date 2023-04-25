#include "PacmanState.h"

//************************ Constructor and Destructor
PacmanState::PacmanState() {
        gameover = false;
        pos.first = 14;
        pos.second = 7;
        pellets_left = 236;
}
PacmanState::~PacmanState() {

}
//************************ Constructor and Destructor
//************************ Position getter and setter
std::pair<int, int> PacmanState::getBotPos() {
    return pos;
}
//************************

void PacmanState::movePlayer(int dx, int dy) {
    pos.first += dx;
    pos.second += dy; 
    if (dx > 0 && dy == 0) {
        direction_facing = right;
    }   else if (dx < 0 && dy == 0) {
        direction_facing = left;
    }  else if (dx == 0 && dy > 0) {
            direction_facing = up;
    } else {
        direction_facing = down;
    }
    bool collision = hasCollided();
}

// void PacmanState::updateScore(int points) {
//         score = points;
//     }
// int PacmanState::getScore() {
//         return score;
// }

// void PacmanState::decreaseLives() {
//         // lives--;
//         // if (lives == 0) {
//         //     gameover = true;
//         // }
// }
// bool PacmanState::isGameOver() {
//         return gameover;        
//  }
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








    /*

    void PacmanState::introduceCherry() {
        if (getPelletsEaten() + getCurrPowerUpsEaten() == 170) {
            //introduce cherry at 13,13
            grid[13][13] = ch;
        }
        if (getPelletsEaten() + getCurrPowerUpsEaten() == 70) {
            //introduce cherry at 13, 13 again
            grid[13][13] = ch;
        }
    }

    //********************************** GEt Distance, Find Possible Moves,isMove Legal
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
        return possible;
    }
    bool PacmanState::is_move_legal(std::pair<int, int> move) {
        // how do i check the actual grid? perhaps we should have a private member for the grid?
        // psuedo for now
        vector<vector<int>> gridCopy = getGrid();
        return (move != pos && grid[move.first][move.second] != I && grid[move.first][move.second] != n);
    } 

    //**************************************************

*/