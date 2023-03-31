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
    void Ghost::moveRedChase() {
        vector<string> directions;
         if ( grid[x_red + 1][y_red] != 'I' ) {
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
        int xDiff = xbotPos - x_red;
        int yDiff = ybotPos - y_red;

        if (xDiff <= 0 && yDiff <= 0) { //should also take into account what direction the Pacbot is facing, as that's the likely direction it's gonna go
           
            if (grid[x_red - 1][y_red] !=  'I' && grid[x_red ][y_red - 1] !- 'I') {
                if (xDiff < yDiff) {
                    x_orange -= 1;
                } 
            } else if (grid[x_red][y_red -1] != 'I' ) {
                if (yDiff < xDiff) {
                    y_orange -= 1;
                }
            }
            
        } else if (xDiff < 0 && yDiff > 0) {

        }
    }
    void Ghost::moveOrangeChase() {
        int numPossOrangeMoves = 0;
        vector<string> directions;
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
    void Ghost::moveBlueChase(){
         //Incomplete ideas; needs more work
        int xDiff = 0;
        int yDiff = 0;
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
        if (grid[v_blue][y_blue + 1] != 'I') {
            directions.push_back("down");
        }
        //Needs more work
    }
    void Ghost::movePinkChase() {
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
    void Ghost::moveRedScatter(){
        // vector<int> x_desired = {};
        // vector<int> y_desired = {};
        // if (x_red < 26){
        //     if (grid[x_red+1][y_red] != 'I') {
        //         x_red += 1;
        //     }

        // } if (y_red >)
        return (get_move_based_on_target(red_scatter_pos.first, red_scatter_pos.second));
    } 
    void Ghost::moveBlueScatter() {
        return (get_move_based_on_target(blue_scatter_pos.first, blue_scatter_pos.second));
    }
    void Ghost::moveOrangeScatter() {
        return (get_move_based_on_target(orange_scatter_pos.first, orange_scatter_pos.second));
    } 
    void Ghost::movePinkScatter() {
        return (get_move_based_on_target(pink_scatter_pos.first, pink_scatter_pos.second));    
    }

    











