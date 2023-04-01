#pragma once

using namespace std;

#include "variables.h"
#include "grid.h"
#include "PacmanState.h"
#include "BFS.h"

class StateSpaceSearch{
    public:

    







    private:

        // State
        enum GameState { BASE, CHERRYONE, CHERRYTWO, FREIGHTENED };

        void updateGameState(GameState state);

        GameState state = BASE;


     
        
};