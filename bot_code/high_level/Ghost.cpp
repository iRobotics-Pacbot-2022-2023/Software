#include "Ghost.h"

void Ghost::moveBlue() {
        if (chase) {
            moveBlueChase();
        } else {
            moveBlueScatter();
        }
    }

    void Ghost::moveOrange() {
        if (chase) {
            moveOrangeChase();
        } else {
            moveOrangeScatter();
        }

    }

    void Ghost::moveRed() {
        if (chase) {
            moveRedChase();
        } else {
            moveRedScatter();
        }
        
        

    }

    void Ghost::movePink() {
        if (chase) {
            movePinkChase();
        } else {
            movePinkScatter();
        }


    }
    
    void Ghost::moveRedChase(int xBotPos, int yBotPos, vector<vector<int>> grid) {

        int x_red = ghostlocs[0].first;
        int y_red = ghostlocs[0].second;
        // vector<string> directions;
        //  if ( grid[x_red + 1][y_red] != 'I' ) {
        //     directions.push_back("right");
        // }
        // if (grid[x_red][y_red - 1] != 'I') {
        //     directions.push_back("up");
        // }
        // if (grid[x_red - 1][y_red] != 'I') {
        //     directions.push_back("left");
        // } 
        // if (grid[x_red][y_red + 1] != 'I') {
        //     directions.push_back("down");
        // }
        int xDiff = xBotPos - x_red; //Assume we can call the xbotpos
        int yDiff = xBotPos - y_red;

        if (xDiff <= 0 && yDiff <= 0) { //should also take into account what direction the Pacbot is facing, as that's the likely direction it's gonna go
           std::pair<int, int> left = {x_red - 1, y_red};
           std::pair<int, int> up = {x_red, y_red - 1};
           
            if (is_move_legal(left)) {
                if (xDiff < yDiff) {
                    x_red -= 1;
                } 
            } else if (is_move_legal(up)) ) {
                if (yDiff < xDiff) {
                    y_red -= 1;
                }
            }
            
        } else if (xDiff < 0 && yDiff > 0) {

        } else if (xDiff > 0 && yDiff < 0) {

        } else {

        }


    }
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
    void Ghost::moveOrangeChase(int xBotPos, int yBotPos, vector<vector<int>> grid) {
        // int numPossOrangeMoves = 0;
        vector<string> directions;
        int x_orange = ghostlocs[1].first;
        int y_orange = ghostlocs[1].second;
        if ( grid[x_orange + 1][y_orange] != 'I' ) {
            directions.push_back("right");
        }
        if (grid[x_orange][y_orange - 1] != 'I') {
            directions.push_back("up");
        }
        if (grid[x_orange - 1][y_orange] != 'I') {
            directions.push_back("left");
        } 
        if (grid[x_orange][y_orange + 1] != 'I') {
            directions.push_back("down");
        }
        int ind = rand() % directions.size();
        string direction = directions[ind];
        if (direction == "left") {
            x_orange -= 1;
        } else if (direction == "up") {
            y_orange += 1;
        } else if (direction == "right") {
            x_orange += 1;
        } else {
            y_orange -= 1;
        }
    }

    void Ghost::moveBlueChase(int xBot, int yBot, vector<vector<int>> grid ){
         //Incomplete ideas; needs more work
        int xDiff = 0;
        int yDiff = 0;

        int x_red = ghostlocs[0].first;
        int y_red = ghostlocs[1].first;
        vector<string> directions;
        if (getDirection() == up)
        {
            xDiff = yBot + 2;
        }
        if (getDirection() == down)
        {
            xDiff = yBot - 2;
        }
        if (getDirection() == left)
        {
            xDiff = xBot - 2;
        }
        if (getDirection() == right)
        {
            xDiff = xBot + 2;
        }

        //Must account for chances that end result could be negative
        //Would be considered out of bounds
        int x_blue = abs(2 * (xDiff - x_red));
        int y_blue = abs(2 * (yDiff - y_red));


        if ( grid[x_blue + 1][y_blue] != 'I' ) {
            directions.push_back("right");
        }
        if (grid[x_blue][y_blue - 1] != 'I') {
            directions.push_back("up");
        }
        if (grid[x_blue - 1][y_blue] != 'I') {
            directions.push_back("left");
        } 
        if (grid[x_blue][y_blue + 1] != 'I') {
            directions.push_back("down");
        }
        //Needs more work
    }
   void Ghost::movePinkChase(int xbotPos, int ybotPos, vector<vector<int>> grid ) {
        if (direction_facing != up) {
            if (direction_facing == right) {
                double pinkTargetX = x + 4; // have to account for walls later
                double dx = pinkTargetX - x_pink;
                double dy = ybotPos - y_pink;
                if (abs(dx) > abs(dy) && dx > 0) {
                    x_pink += 1; // check for walls
                } else if (abs(dx) > abs(dy) && dx < 0) {
                    y_pink += 1; //have to check for walls
                } else if (abs(dx) < abs(dy) && dy > 0) {
                    y_pink -= 1;
                } else {
                    y_pink += 1;
                }

            } else if (direction_facing == down) {
                double pinkTargetY = ybotPos - 4; // have to account for walls later
                if (abs(dx) > abs(dy) && dx > 0) {
                    x_pink += 1;
                } else if (abs(dx) > abs(dy) && dx < 0) {
                    x_pink -= 1;
                } else if (abs(dx) < abs(dy) && dy < 0) {
                    x_pink += 1;
                } else  {
                    y_pink -= 1;
                }

            } else { // left
                double pinkTargetX = xbotPos - 4; //have to account for walls later
                if (abs(dx) > abs(dy) && dx > 0) {
                    y_pink += 1;
                } else if (abs(dx) > abs(dy) && dx < 0) {
                    x_pink -= 1;
                } else if (abs(dx) < abs(dy) && dy < 0) {
                    y_pink += 1;
                } else {
                    y_pink -= 1;
                }

            }

        } else {
            double pinkTargetX = xbotPos - 4;
            double pinkTargetY = ybotPos + 4;
            if (abs(dx) > abs(dy) && dx > 0) {
                    x_pink += 1;
                } else if (abs(dx) > abs(dy) && dx < 0) {
                    x_pink -= 1;
                } else if (abs(dx) < abs(dy) && dy < 0) {
                    y_pink += 1;
                } else if (abs(dx) < abs(dy) && dy > 0) {
                    y_pink -= 1;
                }

        }
    }

 std::pair<std::pair<int, int> , direction> Ghost::get_move_based_on_target(std::pair<int, int> target) {
        std::vector<std::pair<int, int> > possibleMoves = find_possible_moves();
        std::vector<double> distances;
        for (std::pair<int, int> move: possibleMoves) {
            distances.push_back(get_euclidian_distance(move, target) );
        }
        double minDistance = distances[0];
        int index = 0;
        for (unsigned long i = 0; i < distances.size(); i++) {
            if (distances[i] < minDistance) {
                index = i;
                minDistance = distance[i];
            }
        }


        // possible = self._find_possible_moves()
        // distances = []
        // for tile in possible:
        //     distances.append(self._get_euclidian_distance(target, tile))
        // (min_distance, index) = min((min_distance, index)
        //                             for (index, min_distance) in enumerate(distances))

        // return (possible[index], self._get_direction(self.pos["next"], possible[index]))
        std::pair<int, int> currGhostPos;
        if (color == red) {
            currGhostPos = ghostlocs[0];
        } else if (color == orange) {
            currGhostPos = ghostlocs[1];
        } else if (color == blue) {
            currGhostPos = ghostlocs[2];
        } else {
            currGhostPos = ghostlocs[3];
        }

        std::pair<std::pair<int, int> , direction> finalMove = {possibleMoves[index], getDirection( currGhostPos, possibleMoves[index] ) };
        return finalMove;
    }
        
direction Ghost::getDirection(std::pair<int, int> prevPos, std::pair<int, int> newPos) {
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
    void Ghost::moveRedScatter(){
        // vector<int> x_desired = {};
        // vector<int> y_desired = {};
        // if (x_red < 26){
        //     if (grid[x_red+1][y_red] != 'I') {
        //         x_red += 1;
        //     }

        // } if (y_red >)
         std::pair<std::pair<int, int> , direction > nextMove =  (get_move_based_on_target(red_scatter_pos) );
        std::pair<int, int> move = nextMove.first;
        ghostlocs[0].first = move.first;
        ghostlocs[0].second = move.second;
    } 

    void Ghost::moveBlueScatter() {
        std::pair<std::pair<int, int> , direction> nextMove =  (get_move_based_on_target(blue_scatter_pos) );
        std::pair<int, int> move = nextMove.first;
        ghostlocs[2].first = move.first;
        ghostlocs[2].second = move.second;
    }

    void Ghost::moveOrangeScatter() {
        std::pair<std::pair<int, int> , direction> nextMove = (get_move_based_on_target(orange_scatter_pos));
        std::pair<int, int> move = nextMove.first;
        ghostlocs[1].first = move.first;
        ghostlocs[1].second = move.second;
    } 
    
    void Ghost::movePinkScatter() {
        std::pair<std::pair<int, int> , direction> nextMove =  (get_move_based_on_target(pink_scatter_pos)) ;    
        std::pair<int, int> move = nextMove.first;
        ghostlocs[3].first = move.first;
        ghostlocs[3].second = move.second;
    }
std::pair<std::pair<int, int> , direction> Ghost::get_next_frightened_move() {
        std::vector<std::pair<int, int> > moves = find_possible_moves();
        std::pair< std::pair<int, int>, int> move = moves[rand() % moves.size()  ];

        std::pair<int, int> currGhostPos;
        if (color == red) {
            currGhostPos = ghostlocs[0];
        } else if (color == orange) {
            currGhostPos = ghostlocs[1];
        } else if (color == blue) {
            currGhostPos = ghostlocs[2];
        } else {
            currGhostPos = ghostlocs[3];
        }
        std::pair<std::pair<int, int>, direction> finalMove = {move, getDirection(currGhostPos, move)};
        return finalMove;



    }
    
        double Ghost::get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b) {
        double dx = pos_b.first - pos_a.first;
        double dy = pos_b.second - pos_b.second;
        return std::sqrt(dx*dx + dy*dy);
    }

        bool Ghost::is_move_legal(std::pair<int, int> move, vector<vector<int>> grid) {
        // how do i check the actual grid? perhaps we should have a private member for the grid?
        // psuedo for now
        return (move != pos && grid[move.first][move.second] != 'I' && grid[move.first][move.second] != 'n');
    } 
        
std::vector<std::pair<int, int>> Ghost::find_possible_moves() {
        int ghostx;
        int ghosty;
        if (ghostColor == red)  {
        ghostx = ghostlocs[0][0];
        ghosty = ghostlocs[0][1];
        } else if (ghostColor == orange) {
             ghostx = ghostlocs[1][0];
            ghosty = ghostlocs[1][1];
        } else if (ghostColor == pink) {
            ghostx = ghostlocs[2][0];
            ghosty = ghostlocs[2][1];
        } else {// blue
            ghostx = ghostlocs[3][0];
            ghosty = ghostlocs[3][1];

        }

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








