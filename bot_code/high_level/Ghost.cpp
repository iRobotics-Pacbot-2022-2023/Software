#include "Ghost.h"
    // do nothing
    Ghost::Ghost() {

    }
    Ghost::Ghost(std::pair<int, int> ghostLoc, std::pair<int, int> scatterLoc, std::pair<int, int> pacPos, Ghost::Direction facing, Ghost::GhostState state) {
        curGhostLocation = ghostLoc;
        scatterLocation = scatterLoc;
        pacBotPos = pacPos;

        direction_facing = facing;
        current_ghost_state = state;
    }
    std::pair<int, int> Ghost::getGhostLocation() {
        return curGhostLocation;
    }

    std::vector<std::vector<int>> Ghost::getGrid() {
        return grid;
    }
    void Ghost::ghostMove(std::pair<int, int> pair) {
        
        Ghost::Direction facing = getDirection(curGhostLocation, pair);
        if (facing == Ghost::up) {
            direction_facing = Ghost::up;
        } else if (facing == Ghost::left) {
            direction_facing = Ghost::left;
        } else if (facing == Ghost::right) {
            direction_facing = Ghost::right;
        } else if (facing == Ghost::down) {
            direction_facing = Ghost::down;
        }
        curGhostLocation = pair;
    }

    // we will move this to the state space search since this depends on the pacbot direction
    // im starting to think all of harvards code is kinda janky for ghost cuz 
    // this is probs not correct
    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_pink_chase_move(std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Ghost::Direction ghostDirection) {
        std::pair<int, int> pinkMove;
        if (pacbotDirection == PacmanState::Direction::up) {
            pinkMove.first = pacBotPos.first - 4;
            pinkMove.second = pacBotPos.second + 4;
        } else if (pacbotDirection == PacmanState::Direction::down) {
            pinkMove.first = pacBotPos.first;
            pinkMove.second = pacBotPos.second - 4;
        } else if (pacbotDirection == PacmanState::Direction::left) {
            pinkMove.first = pacBotPos.first - 4;
            pinkMove.second = pacBotPos.second;
        } else if (pacbotDirection == PacmanState::Direction::right) {
            pinkMove.first = pacBotPos.first + 4;
            pinkMove.second = pacBotPos.second;
        }
        return get_move_based_on_target(pinkMove);

    }
    //potential parameter
    // std::vector<std::vector<int>> grid, 
    std::pair<std::pair<int, int> , Ghost::Direction > Ghost::_get_next_state_move(std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Ghost::Direction ghostDirection) {
        if (current_ghost_state == frightened) {
            return _get_next_frightened_move();
        } else if (current_ghost_state == chase) {
            if (ghost_color == orange) {
                return _get_next_orange_chase_move(pacbotPos, ghostPos);
            } else if (ghost_color == blue) {
                return _get_next_blue_chase_move(pacbotPos, pacbotDirection,ghostPos, ghostDirection);
            } else if (ghost_color == red) {
                return _get_next_red_chase_move(pacbotPos, pacbotDirection,ghostPos, ghostDirection);
            } else {
                return _get_next_pink_chase_move(pacbotPos, pacbotDirection,ghostPos, ghostDirection);
            }
        } else {
            return _get_next_scatter_move();
        }
    }


std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_blue_chase_move(std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Ghost::Direction ghostDirection){

     std::pair<int, int> bluezooms;
        if(pacbotDirection == PacmanState::up){
        bluezooms.first = pacBotPos.first - 2;
        bluezooms.second = pacBotPos.second + 2;
        }
        else if(pacbotDirection == PacmanState::down){
        bluezooms.first = pacBotPos.first;
        bluezooms.second = pacBotPos.second - 2;
        }
        else if(pacbotDirection == PacmanState::left){
        bluezooms.first = pacBotPos.first - 2;
        bluezooms.second = pacBotPos.second;
        }
        else if(pacbotDirection == PacmanState::right){
        bluezooms.first = pacBotPos.first + 2;
        bluezooms.second = pacBotPos.second;
        }
        //Please change _get_next_red_chase_move() for current red ghost position
        //bluezooms.first = bluezooms.first + (bluezooms.first - _get_next_red_chase_move().first); make method to obtain the red ghost's current position
        //bluezooms.second = bluezooms.second + (bluezooms.first - _get_next_red_chase_move().second); Since the blue heavily relies on this red ghost position
        return get_move_based_on_target(bluezooms); 

    }
    // we will put this into the state class to have access to the pacbot location
    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_red_chase_move(std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Ghost::Direction ghostDirection) {
        return get_move_based_on_target(pacbotPos);
    }

    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_orange_chase_move(std::pair<int, int> pacbotPos, std::pair<int, int> ghostPos) {
        if (get_euclidian_distance(pacbotPos, ghostPos) < 8) {
            return _get_next_scatter_move();
        }
        return get_move_based_on_target(pacbotPos);
    }

    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_scatter_move() {
        return get_move_based_on_target(scatterLocation);
    }

    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_frightened_move() {
        std::vector<std::pair<int, int>> possible = find_possible_moves();
        std::pair<int, int> rand_move = possible[rand() % possible.size()];
        Ghost::Direction direction = getDirection(curGhostLocation, rand_move);
        std::pair<std::pair<int, int> , Ghost::Direction> finalMove = {rand_move, direction};
        return finalMove;
    }


    // fuckkkkkkkkkk i gotta do BFS
    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::get_move_based_on_target(std::pair<int, int> target) {
        // BFS does not model the ghost movement properly
        // i need to go back to euclidian but put the correct logic
        // first i need to ensure that the ghosts can never reverse during chase
        // also that they go in the right ordering

        std::vector<std::pair<int, int>> possibleMoves = find_possible_moves();
        // check if any of the possible moves make the ghost reverse
        // if so, then delete
        std::pair<int, int> reversed;
        if (direction_facing == up) {
            reversed = std::pair<int, int>(curGhostLocation.first, curGhostLocation.second - 1);
        } else if (direction_facing == down) {
            reversed = std::pair<int, int>(curGhostLocation.first, curGhostLocation.second + 1);
        } else if (direction_facing == left) {
            reversed = std::pair<int, int>(curGhostLocation.first + 1, curGhostLocation.second);
        } else if (direction_facing == right) {
            reversed = std::pair<int, int>(curGhostLocation.first - 1, curGhostLocation.second);
        }
        for (int i = 0; i < possibleMoves.size(); ++i) {
            if (possibleMoves.at(i).first == reversed.first && possibleMoves.at(i).second == reversed.second) {
                possibleMoves.erase(possibleMoves.begin() + i);
            }
        }
        // testing
        // for (int i = 0; i < possibleMoves.size(); ++i) {
        //     std::cout << possibleMoves.at(i).first << " " << possibleMoves.at(i).second << std::endl;
        // }
        

        std::vector<double> distances;
        for (std::pair<int, int> move: possibleMoves) {
            distances.push_back(get_euclidian_distance(target, move) );
        }
        double minDistance = distances[0];
        int index = 0;
        // if we will reach our target, if not take the next best route
        for (unsigned long i = 0; i < distances.size(); i++) {
            if (distances[i] < minDistance) {
                index = i;
                minDistance = distances[i];
            }
        }
        Ghost::Direction facing = getDirection(curGhostLocation, possibleMoves[index]);
        

        std::pair<std::pair<int, int> , Ghost::Direction> finalMove = {possibleMoves[index], facing};
        return finalMove;

        // std::vector<std::pair<int, int>> vect_ = bfsPathSingle(getGhostLocation(), target, grid);
        // vect_.erase(vect_.begin());
        // std::pair<int, int> toReturn = vect_.front();
        // Ghost::Direction direct;
        // if (toReturn.first == getGhostLocation().first) {
        //     if (toReturn.second < getGhostLocation().second) {
        //         direct = down;
        //     } else if (toReturn.second > getGhostLocation().second) {
        //         direct = up;
        //     }
        // } else if (toReturn.second == getGhostLocation().second) {
        //     if (toReturn.first < getGhostLocation().first) {
        //         direct = left;
        //     } else if (toReturn.first > getGhostLocation().first) {
        //         direct = right;
        //     }
        // }
        // std::pair<std::pair<int, int>, Ghost::Direction> finalMove = {toReturn, direct};
        // return finalMove;
    }

    vector<pair<int, int>> Ghost::bfsPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid) {
        map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
        visited_nodes_to_parents[start] = make_pair(-1, -1); // start doesn't have a parent so we set it to (-1, -1)

        queue<pair<int, int>> queue;
        queue.push(start);

        while (!queue.empty()) {
            pair<int, int> current = queue.front();
            queue.pop();

            if (current == goal) { // current.x = goal.x && current.y = goal.y
            
                vector<pair<int, int>> path;

                while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                    path.insert(path.begin(), current);
                    current = visited_nodes_to_parents[current];
                }

                return path;

            }

            vector<pair<int, int>> neighbors = getNeighbors(current, grid);

            for (pair<int, int> neighbor : neighbors) {
                if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                    visited_nodes_to_parents[neighbor] = current;
                    queue.push(neighbor);
                }
            }  
        }

        return {};
    }

vector<pair<int, int>> Ghost::getNeighbors(pair<int, int> node, vector<vector<int>> grid) {
    // grid range:
    // x : [0, 27]
    // y :[0, 30]

    vector<pair<int, int>> neighbors;

    neighbors.push_back(make_pair(node.first, node.second + 1)); // up
    neighbors.push_back(make_pair(node.first - 1, node.second)); // left
    neighbors.push_back(make_pair(node.first, node.second - 1)); // down
    neighbors.push_back(make_pair(node.first + 1, node.second)); // right
    
    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[i];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || x > 27 || y > 30 || y < 0 || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n) {
            neighbors.erase(neighbors.begin() + i);
        } 
        else {
            i++;
        }
    }

    return neighbors;
}

Ghost::Direction Ghost::getterDirection() {
    return direction_facing;
}

Ghost::Direction Ghost::getDirection(std::pair<int, int> prevPos, std::pair<int, int> newPos) {
        if (newPos.first > prevPos.first) {
            return Ghost::right;
        } else if (newPos.first < prevPos.first) {
            return Ghost::left;
        } else if (newPos.second > prevPos.second) {
            return Ghost::up;
        } else if (newPos.second < prevPos.second) {
            return Ghost::down;
        }
        else {
            return direction_facing;
        }
    }

    double Ghost::get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b) {
        double dx = pos_b.first - pos_a.first;
        double dy = pos_b.second - pos_b.second;
        return std::sqrt(dx*dx + dy*dy);
    }

    bool Ghost::is_move_legal(std::pair<int, int> move) {
        return (move != curGhostLocation && grid[move.first][move.second] != I && 
        grid[move.first][move.second] != n && 
        grid[move.first][move.second]  != e);
    } 
        
std::vector<std::pair<int, int>> Ghost::find_possible_moves() {
        
        std::pair<int, int> up = std::pair<int, int>(curGhostLocation.first, curGhostLocation.second + 1); //up
        std::pair<int, int> left = std::pair<int, int>(curGhostLocation.first - 1, curGhostLocation.second); //left
        std::pair<int, int> down = std::pair<int, int>(curGhostLocation.first, curGhostLocation.second - 1); //down
        std::pair<int, int> right = std::pair<int, int>(curGhostLocation.first + 1, curGhostLocation.second); //right

        std::vector<std::pair<int, int>> possible;

        if (is_move_legal(up)) {
            possible.push_back(up);
        }
        if (is_move_legal(left)) {
            possible.push_back(left);
        }
        if (is_move_legal(down)) {
            possible.push_back(down);
        }
        if (is_move_legal(right)) {
            possible.push_back(right);
        }
        return possible;
    }









