// values & weights for certain constants
#include <vector>
#include "PacmanState.h"
#include "StateSpaceSearch.h"

//frightened state
// number of points on the way
// distance to power ups. ghosts
// if there is a cherry (potentailly switch to pathfinding)
// 


//for now im going to have some weird parameters since I don't know how to code
// the grid 

// return final position
std::pair<int, int> _state_space_search(int depth, PacmanState current_state) {
    // std::vector<>
    int bestMove = 0; //just to initialize
    std::pair<int, int> finalcoordinate = {0,0};
    // char bestMoveFound = ''; // for now im thinking we will have the best move be a char representing which direction to move
    // PacmanGame p;
    // p.changeX(self.x_pos);
    // p.changeY(self.y_pos);

    // move should be a vector of coordinates we have traversed
    for (auto move : current_state.find_possible_moves()) {
        const PacmanState child = current_state; // potentially have this be a copy of the state itself. Psuedo, no class implemented yet
        // child.Move(move);
        Move(move, child); //this function essentially simulates what the grid/state will look like after the move
        int value = evaluate(depth-1, &child); // function that will go down the tree of possible moves
        if (value >= bestMove) {
            bestMove = value;
            bestMoveFound = {child.}; //psuedo, i havent set up the pacman class
        }
    }
    return bestMoveFound;
}

int evaluate(int depth, Pacmanstate current_state) {
    if (depth == 0) {
        return evaluatePosition(current_state);
    }
    if (current_state.gameOver() == true) {
        return -100;
    }

    int bestMove = 0; //negative inf, just to initialize
    for (auto move : grid.validMoves()) {
        Pacmanstate child = current_state;
        Move(move, child);
        bestScore = max(bestMove, child.getScore() + evaluate(depth-1, child));
    }
    return bestScore; 
}

std::vector<std::pair<int,int>> validMoves(Pacmanstate current, int depth) {
    // look at the grid and determine which moves are legitimate
    // return a vector containing all the possible moves
    // within a certain distance

    std::vector<char> moves;
    
    // need to access current position
    // pseudocode cuz i dont know how to access positions 

    //check to see if the next position is either empty or a wall
    // if its either, then dont push it onto the vector because we cant visit it 

    // one of the biggest functions i need to update

    if (global_grid[current.getX()][current.getY()] != 'n' &&
        global_grid[p_loc[0] + 1][p_loc[1]] != 'w') {
            moves.push_back('E');
    } else if (global_grid[p_loc[0] - 1][p_loc[1]] != 'n' &&
                global_grid[p_loc[0] - 1][p_loc[1]] != 'w') {
                    moves.push_back('W');
    } else if (global_grid[p_loc[0]][p_loc[1] + 1] != 'n' &&
                global_grid[p_loc[0]][p_loc[1] + 1] != 'w') {
                    moves.push_back('N');
    } else if (global_grid[p_loc[0]][p_loc[1] - 1] != 'n' &&
                global_grid[p_loc[0]][p_loc[1] - 1] != 'w') {
                    moves.push_back('S');
    }
    return moves;

}

int evaluatePosition(Pacmanstate current_state) {
    //this is a function that will evalaute the MPS (max-possible-score)
    // at a certain position
    // it is called within evaluate to determine which paths to go down
    

    // in order to calculate this MPS, we should look at the most important items on the board
    // and then determine how much score we have left

    // finally, we need to include some time decay so our robot will actually move 
    // instead of just standing still

    // for right now, this MPS will be calculated with a very simple approach

    // essentially think of opportunity cost
    
    int total = current_state.power_ups_left() * current_state.power_up_weight() + current_state.pellets_left() * current_state.pellets_weight(); //these params are from the current_state
    return total;
}

void Move(std::vector<std::pair<int,int>> move_s, Pacmanstate & current) {
    if (move_s.size() == 0) return;
    // this function needs to simulate how the grid will look like after we move

    // we need to take into account whatever we eat will be removed from the board,
    // and that the ghosts will be moving along with us
    // everything else should be static
    
}
