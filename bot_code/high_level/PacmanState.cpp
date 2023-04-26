#include "PacmanState.h"

//************************ Constructor and Destructor
// PacmanState::PacmanState() {
// }

// PacmanState::PacmanState(std::pair<int, int> botPos, PacmanState::Direction pacDirection, std::vector<std::vector<int>> grid, int pelletsLeft, int pellets_eat, int cherries_eat, int powerups) {
//      {
//         // score = 0; // retrieve from server
//         // lives = 3; // retrieve from server
//         gameover = false; // retrieve from server
//         pos = botPos; // retrieve from server
//         direction_facing = pacDirection;
//         pellets_left = pelletsLeft; // retrieve from server
//         pellets_eaten = pellets_eat; // retrieve from server
//         cherries_eaten = cherries_eat; // retrieve from server
//         powerups_eaten = powerups; // retrieve from server
//     }
// }

// PacmanState::PacmanState(PacmanState & state) {
//     pos = state.pos;
//     direction_facing = state.direction_facing;
//     grid = state.grid;
// }
//************************ Constructor and Destructor
//************************ Position getter and setter
// std::pair<int, int> PacmanState::getBotPos() {
//     return pos;
// }

// std::vector<std::pair<int, int>> PacmanState::find_possible_moves() {
        
//         std::pair<int, int> up = std::pair<int, int>(pos.first, pos.second + 1); //up
//         std::pair<int, int> left = std::pair<int, int>(pos.first - 1, pos.second); //left
//         std::pair<int, int> down = std::pair<int, int>(pos.first, pos.second - 1); //down
//         std::pair<int, int> right = std::pair<int, int>(pos.first + 1, pos.second); //right

//         std::vector<std::pair<int, int>> possible;

//         if (is_move_legal(up)) {
//             possible.push_back(up);
//         }
//         if (is_move_legal(left)) {
//             possible.push_back(left);
//         }
//         if (is_move_legal(down)) {
//             possible.push_back(down);
//         }
//         if (is_move_legal(right)) {
//             possible.push_back(right);
//         }
//         return possible;
//     }

    // bool PacmanState::is_move_legal(std::pair<int, int> move) {
    //     return (move != pos && grid[move.first][move.second] != I && 
    //     grid[move.first][move.second] != n && 
    //     grid[move.first][move.second]  != e);
    // }

// void PacmanState::move(std::pair<int, int> move) {
//     PacmanState::Direction facing = getDirection(pos, move);
//     if (facing == PacmanState::up) {
//         direction_facing = Ghost::up;
//     } else if (facing == Ghost::left) {
//         direction_facing = Ghost::left;
//     } else if (facing == Ghost::right) {
//         direction_facing = Ghost::right;
//     } else if (facing == Ghost::down) {
//         direction_facing = Ghost::down;
//     }

//     if (grid[move.first][move.second] == 2 || grid[move.first][move.second] == 4) {
//         grid[move.first][move.second] = 7;
//     }
//     pos = move;
// }


// PacmanState::Direction PacmanState::getDirection(std::pair<int, int> prevPos, std::pair<int, int> newPos) {
//         if (newPos.first > prevPos.first) {
//             return PacmanState::Direction::right;
//         } else if (newPos.first < prevPos.first) {
//             return PacmanState::Direction::left;
//         } else if (newPos.second > prevPos.second) {
//             return PacmanState::Direction::up;
//         } else if (newPos.second < prevPos.second) {
//             return PacmanState::Direction::down;
//         }
//         else {
//             return direction_facing;
//         }
//     }
//************************

// void PacmanState::movePlayer(std::pair<int, int> move) {
    
//     if (move.first > pos.first) {
//             direction_facing = PacmanState::Direction::right;
//         } else if (move.first < pos.first) {
//             direction_facing = PacmanState::Direction::left;
//         } else if (move.second > pos.second) {
//             direction_facing = PacmanState::Direction::up;
//         } else if (move.second < pos.second) {
//             direction_facing = PacmanState::Direction::down;
//         }
//         pos.first = move.first;
//         pos.second = move.second; 
// }

//     bool PacmanState::hasCollided(std::vector<std::pair<int, int>> ghostLocs) {
//         for (int i = 0; i < ghostLocs.size(); ++i) {
//             if ((ghostLocs.at(i).first == pos.first && ghostLocs.at(i).second == pos.second)) {
//                 return true;
//             }
//         }
//         return false;
//     }
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

    vector<vector<int>> PacmanState::getGrid() {
        return grid;
    }
    bool PacmanState::is_move_legal(std::pair<int, int> move) {
        // how do i check the actual grid? perhaps we should have a private member for the grid?
        // psuedo for now
        vector<vector<int>> gridCopy = getGrid();
        return (move != pos && grid[move.first][move.second] != I && grid[move.first][move.second] != n);
    } 

    //**************************************************

*/