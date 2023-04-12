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

    







    private:

        // State
        enum GameState { BASE, CHERRYONE, CHERRYTWO, FREIGHTENED };

        void updateGameState(GameState state);

        GameState state = BASE;


     
        
};