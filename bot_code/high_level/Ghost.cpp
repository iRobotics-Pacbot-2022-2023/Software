#include "Ghost.h"

    // void Ghost::moveBlue() {
    //     if (chase) {
    //         moveBlueChase();
    //     } else {
    //         moveBlueScatter();
    //     }
    // }

    // void Ghost::moveOrange() {
    //     if (chase) {
    //         moveOrangeChase();
    //     } else {
    //         moveOrangeScatter();
    //     }

    // }

    // void Ghost::moveRed() {
    //     if (chase) {
    //         moveRedChase();
    //     } else {
    //         moveRedScatter();
    //     }
        
        

    // }

    // void Ghost::movePink() {
    //     if (chase) {
    //         movePinkChase();
    //     } else {
    //         movePinkScatter();
    //     }


    // }
    
    // void Ghost::moveRedChase(int xBotPos, int yBotPos, vector<vector<int>> grid) {

    //     int x_red = ghostlocs[0].first;
    //     int y_red = ghostlocs[0].second;
    //     // vector<string> directions;
    //     //  if ( grid[x_red + 1][y_red] != 'I' ) {
    //     //     directions.push_back("right");
    //     // }
    //     // if (grid[x_red][y_red - 1] != 'I') {
    //     //     directions.push_back("up");
    //     // }
    //     // if (grid[x_red - 1][y_red] != 'I') {
    //     //     directions.push_back("left");
    //     // } 
    //     // if (grid[x_red][y_red + 1] != 'I') {
    //     //     directions.push_back("down");
    //     // }
    //     int xDiff = xBotPos - x_red; //Assume we can call the xbotpos
    //     int yDiff = xBotPos - y_red;

    //     if (xDiff <= 0 && yDiff <= 0) { //should also take into account what direction the Pacbot is facing, as that's the likely direction it's gonna go
    //        std::pair<int, int> left = {x_red - 1, y_red};
    //        std::pair<int, int> up = {x_red, y_red - 1};
           
    //         if (is_move_legal(left)) {
    //             if (xDiff < yDiff) {
    //                 x_red -= 1;
    //             } 
    //         } else if (is_move_legal(up)) ) {
    //             if (yDiff < xDiff) {
    //                 y_red -= 1;
    //             }
    //         }
            
    //     } else if (xDiff < 0 && yDiff > 0) {

    //     } else if (xDiff > 0 && yDiff < 0) {

    //     } else {

    //     }


    // do nothing
    Ghost::Ghost() {

    }

    Ghost::Ghost(PacBot & test) {
        // grid = grid;
        pacbot = test;
        curGhostLocation = std::pair<int, int>(1, 1);
    }

    PacBot Ghost::getPac() {
        return pacbot;
    }


    std::vector<std::vector<int>> Ghost::getGrid() {
        return grid;
    }
    void Ghost::ghostMove(std::pair<int, int> pair) {
        curGhostLocation = pair;
    }

    // we will move this to the state space search since this depends on the pacbot direction
    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_pink_chase_move() {
        std::pair<int, int> pinkMove;
        if (pacbot.getPacDirection() == PacBot::up) {
            pinkMove.first = pacbot.getPos().first - 4;
            pinkMove.second = pacbot.getPos().second + 4;
        } else if (pacbot.getPacDirection() == PacBot::down) {
            pinkMove.first = pacbot.getPos().first;
            pinkMove.second = pacbot.getPos().second - 4;
        } else if (pacbot.getPacDirection() == PacBot::left) {
            pinkMove.first = pacbot.getPos().first - 4;
            pinkMove.second = pacbot.getPos().second;
        } else if (pacbot.getPacDirection() == PacBot::right) {
            pinkMove.first = pacbot.getPos().first + 4;
            pinkMove.second = pacbot.getPos().second;
        }
        return get_move_based_on_target(pinkMove);

    }

    // we will put this into the state class to have access to the pacbot location
    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_red_chase_move() {
        return get_move_based_on_target(pacbot.getPos());
    }

    // std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_orange_chase_move() {
    //     if (get_euclidian_distance(curGhostLocation, pacbot.getPos()) < 8) {
    //         return _get_next_scatter_move();
    //     }
    //     return get_move_based_on_target(pacbot.getPos());
    // }

    // std::pair<std::pair<int, int>, Ghost::Direction> Ghost::_get_next_scatter_move() {
    //     return get_move_based_on_target(scatterLocation);
    // }
        

        
//     void Ghost::moveRedChase() {
//         vector<string> directions;
//          if ( grid[x_red + 1][y_red] != 'I' ) {
//             directions.push_back("right");
//         }
//         if (grid[x_orange][y_orange - 1] != 'I') {
//             directions.push_back("up");
//         }
//         if (grid[x_orange - 1][y_orange] != 'I') {
//             directions.push_back("left");
//         } 
//         if (grid[x_orange][y_orange + 1] != 'I') {
//             directions.push_back("down");
//         }
//         int xDiff = xbotPos - x_red;
//         int yDiff = ybotPos - y_red;

//         if (xDiff <= 0 && yDiff <= 0) { //should also take into account what direction the Pacbot is facing, as that's the likely direction it's gonna go
           
//             if (grid[x_red - 1][y_red] !=  'I' && grid[x_red ][y_red - 1] !- 'I') {
//                 if (xDiff < yDiff) {
//                     x_orange -= 1;
//                 } 
//             } else if (grid[x_red][y_red -1] != 'I' ) {
//                 if (yDiff < xDiff) {
//                     y_orange -= 1;
//                 }
//             }
            
//         } else if (xDiff < 0 && yDiff > 0) {

//         }
//     }
    // void Ghost::moveOrangeChase(int xBotPos, int yBotPos, vector<vector<int>> grid) {
    //     // int numPossOrangeMoves = 0;
    //     vector<string> directions;
    //     int x_orange = ghostlocs[1].first;
    //     int y_orange = ghostlocs[1].second;
    //     if ( grid[x_orange + 1][y_orange] != 'I' ) {
    //         directions.push_basck("right");
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

    // void Ghost::moveBlueChase(int xBot, int yBot, vector<vector<int>> grid ){
    //      //Incomplete ideas; needs more work
    //     int xDiff = 0;
    //     int yDiff = 0;

    //     int x_red = ghostlocs[0].first;
    //     int y_red = ghostlocs[1].first;
    //     vector<string> directions;
    //     if (getDirection() == up)
    //     {
    //         xDiff = yBot + 2;
    //     }
    //     if (getDirection() == down)
    //     {
    //         xDiff = yBot - 2;
    //     }
    //     if (getDirection() == left)
    //     {
    //         xDiff = xBot - 2;
    //     }
    //     if (getDirection() == right)
    //     {
    //         xDiff = xBot + 2;
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
    //     if (grid[x_blue][y_blue + 1] != 'I') {
    //         directions.push_back("down");
    //     }
    //     //Needs more work
    // }

    // std::pair<std::pair<int, int> , Direction> Ghost::get_move_based_on_target(std::pair<int, int> target)


    // fuckkkkkkkkkk i gotta do BFS
    std::pair<std::pair<int, int>, Ghost::Direction> Ghost::get_move_based_on_target(std::pair<int, int> target) {
        // std::vector<std::pair<int, int>> possibleMoves = find_possible_moves();
        // std::vector<double> distances;
        // for (std::pair<int, int> move: possibleMoves) {
        //     distances.push_back(get_euclidian_distance(target, move) );
        // }
        // double minDistance = distances[0];
        // int index = 0;
        // // if we will reach our target, if not take the next best route
        // for (unsigned long i = 0; i < distances.size(); i++) {
        //     if (distances[i] < minDistance) {
        //         index = i;
        //         minDistance = distances[i];
        //     }
        // }
        // std::pair<std::pair<int, int> , Ghost::Direction> finalMove = {possibleMoves[index], getDirection(curGhostLocation, possibleMoves[index])};
        // return finalMove;
        std::vector<std::pair<int, int>> vect_ = bfsPathSingle(getGhostLocation(), target, grid);
        vect_.erase(vect_.begin());
        std::pair<int, int> toReturn = vect_.front();
        Ghost::Direction direct;
        if (toReturn.first == getGhostLocation().first) {
            if (toReturn.second < getGhostLocation().second) {
                direct = down;
            } else if (toReturn.second > getGhostLocation().second) {
                direct = up;
            }
        } else if (toReturn.second == getGhostLocation().second) {
            if (toReturn.first < getGhostLocation().first) {
                direct = left;
            } else if (toReturn.first > getGhostLocation().first) {
                direct = right;
            }
        }
        std::pair<std::pair<int, int>, Ghost::Direction> finalMove = {toReturn, direct};
        return finalMove;
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


    neighbors.push_back(make_pair(node.first - 1, node.second)); // left
    neighbors.push_back(make_pair(node.first, node.second - 1)); // down
    neighbors.push_back(make_pair(node.first + 1, node.second)); // right
    neighbors.push_back(make_pair(node.first, node.second + 1)); // up
    
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
        
Ghost::Direction Ghost::getDirection(std::pair<int, int> prevPos, std::pair<int, int> newPos) {
        if (newPos.first > prevPos.first) {
            return right;
        } else if (newPos.first < prevPos.first) {
            return left;
        } else if (newPos.second > prevPos.second) {
            return up;
        } else if (newPos.second < prevPos.second) {
            return down;
        }
        else {
            return direction_facing;
        }
        return down;

        // def _get_direction(self, pos_prev, pos_new):
        // if pos_new[0] > pos_prev[0]:
        //     return right
        // elif pos_new[0] < pos_prev[0]:
        //     return left
        // elif pos_new[1] > pos_prev[1]:
        //     return up
        // elif pos_new[1] < pos_prev[1]:
        //     return down
        // else:
        //     return self.direction

    }
    // void Ghost::moveRedScatter(){
    //     // vector<int> x_desired = {};
    //     // vector<int> y_desired = {};
    //     // if (x_red < 26){
    //     //     if (grid[x_red+1][y_red] != 'I') {
    //     //         x_red += 1;
    //     //     }

    //     // } if (y_red >)
    //      std::pair<std::pair<int, int> , Ghost::Direction > nextMove =  (get_move_based_on_target(red_scatter_pos) );
    //     std::pair<int, int> move = nextMove.first;
    //     ghostlocs[0].first = move.first;
    //     ghostlocs[0].second = move.second;
    // } 

    // void Ghost::moveBlueScatter() {
    //     std::pair<std::pair<int, int> , direction> nextMove =  (get_move_based_on_target(blue_scatter_pos) );
    //     std::pair<int, int> move = nextMove.first;
    //     ghostlocs[2].first = move.first;
    //     ghostlocs[2].second = move.second;
    // }

    // void Ghost::moveOrangeScatter() {
    //     std::pair<std::pair<int, int> , direction> nextMove = (get_move_based_on_target(orange_scatter_pos));
    //     std::pair<int, int> move = nextMove.first;
    //     ghostlocs[1].first = move.first;
    //     ghostlocs[1].second = move.second;
    // } 
    
    // void Ghost::movePinkScatter() {
    //     std::pair<std::pair<int, int> , direction> nextMove =  (get_move_based_on_target(pink_scatter_pos)) ;    
    //     std::pair<int, int> move = nextMove.first;
    //     ghostlocs[3].first = move.first;
    //     ghostlocs[3].second = move.second;
    // }
std::pair<std::pair<int, int> , Ghost::Direction> Ghost::get_next_frightened_move() {
        std::vector<std::pair<int, int> > moves = find_possible_moves();
        std::pair<int, int> move = moves[rand() % moves.size()];

        // std::pair<int, int> currGhostPos;
        // if (color == red) {
        //     currGhostPos = ghostlocs[0];
        // } else if (color == orange) {
        //     currGhostPos = ghostlocs[1];
        // } else if (color == blue) {
        //     currGhostPos = ghostlocs[2];
        // } else {
        //     currGhostPos = ghostlocs[3];
        // }
        std::pair<std::pair<int, int>, Ghost::Direction> finalMove = {move, getDirection(curGhostLocation, move)};
        return finalMove;



    }
    
    double Ghost::get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b) {
        double dx = pos_b.first - pos_a.first;
        double dy = pos_b.second - pos_b.second;
        return std::sqrt(dx*dx + dy*dy);
    }

    // we plan on moving this over to the statespacesearch class for OOP reasons
    bool Ghost::is_move_legal(std::pair<int, int> move) {
        return (move != curGhostLocation && grid[move.first][move.second] != 1 && grid[move.first][move.second] != 5);
    } 
    std::pair<int, int> Ghost::getGhostLocation() {
        return curGhostLocation;
    }

    std::vector<std::pair<int, int>> Ghost::find_possible_moves() {
        int ghostx = getGhostLocation().first;
        int ghosty = getGhostLocation().second;

        std::pair<int, int> right = {ghostx + 1, ghosty};
        std::pair<int, int> up = {ghostx, ghosty + 1};
        std::pair<int, int> left = {ghostx - 1, ghosty};
        std::pair<int, int> down = {ghostx, ghosty - 1};

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








