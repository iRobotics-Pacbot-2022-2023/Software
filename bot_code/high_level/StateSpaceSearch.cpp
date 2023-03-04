// values & weights for certain constants
#include <vector>

int power_up = 500;
int pellet = 10;
int power_ups_left = 4;
int pellets_left = 100;

//for now im going to have some weird parameters since I don't know how to code
// the grid 

char _state_space_search(int depth, grid) {
    int bestMove = 0; //just to initialize
    char bestMoveFound = ''; // for now im thinking we will have the best move be a char representing which direction to move

    for (auto move : pos.validMoves()) {
        child = grid;
        child.Move(move); //this function essentially simulates what the grid will look like after the move
        value = evaluate(depth-1, child); // function that will go down the tree of possible moves
        if value >= bestMove {
            bestMove = value;
            bestMoveFound = move;
        }
    }
    return bestMoveFound;
}

int evaluate(int depth, grid) {
    if (depth == 0 || game.Position().Status() == game_end) {
        return evaluatePosition(position);
    }

    int bestMove = 0; //negative inf, just to initialize
    for (auto move : grid.validMoves()) {
        child = grid;
        child.Move(move);
        bestMove = max(bestMove, evaluate(depth-1));
    }
    return bestMove; 
}

std::vector<char> validMoves() {
    // look at the grid and determine which moves are legitimate
    // return a vector containing all the possible moves
    // within a certain distance

    std::vector<char> moves;
    
    // need to access current position
    // pseudocode cuz i dont know how to access positions 

    p_loc = {x_current_location, y_current_location}; //this is terrible

    //check to see if the next position is either empty or a wall
    // if its either, then dont push it onto the vector because we cant visit it 

    if (global_grid[p_loc[0] + 1][p_loc[1]] != 'e' &&
        global_grid[p_loc[0] + 1][p_loc[1]] != 'W') {
            moves.push_back('E');
    } else if (global_grid[p_loc[0] - 1][p_loc[1]] != 'e' &&
                global_grid[p_loc[0] - 1][p_loc[1]] != 'W') {
                    moves.push_back('W');
    } else if (global_grid[p_loc[0]][p_loc[1] + 1] != 'e' &&
                global_grid[p_loc[0]][p_loc[1] + 1] != 'W') {
                    moves.push_back('N');
    } else if (global_grid[p_loc[0]][p_loc[1] - 1] != 'e' &&
                global_grid[p_loc[0]][p_loc[1] - 1] != 'W') {
                    moves.push_back('S');
    }
    return moves;

}

int evaluatePosition() {
    //this is a function that will evalaute the MPS (max-possible-score)
    // at a certain position
    // it is called within evaluate to determine which paths to go down
    

    // in order to calculate this MPS, we should look at the most important items on the board
    // and then determine how much score we have left

    // finally, we need to include some time decay so our robot will actually move 
    // instead of just standing still

    // for right now, this MPS will be calculated with a very simple approach

    // essentially think of opportunity cost
    
    int total = (power_up * power_ups_left) + (pellet * pellets_left);
    return total;
}

Move() {
    // this function needs to simulate how the grid will look like after we move

    // we need to take into account whatever we eat will be removed from the board,
    // and that the ghosts will be moving along with us
    // everything else should be static
}