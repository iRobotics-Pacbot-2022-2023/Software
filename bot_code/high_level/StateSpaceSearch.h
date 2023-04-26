#pragma once

using namespace std;

#include "variables.h"
#include "grid.h"
#include "PacmanState.h"
#include "Ghost.h"
#include "BFS.h"
#include "AStar.h"

class StateSpaceSearch{
    public:
        StateSpaceSearch(PacmanState state, Ghost red, Ghost blue, Ghost orange, Ghost pink);
        std::pair<int, int> _state_space_search(int depth, PacmanState current_state);
        int evaluate(int depth, Pacmanstate current_state);
        std::vector<std::pair<int,int>> validMoves(Pacmanstate current, int depth);
        int evaluatePosition(Pacmanstate current_state);





    private:

        // State
        enum GameState { BASE, CHERRYONE, CHERRYTWO, FREIGHTENED };

        void updateGameState(GameState state);

        GameState state = BASE;


     
        
};