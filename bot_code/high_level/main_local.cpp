#include "Ghost.h"
#include "PacmanState.h"

#include "StateSpaceSearch-R.h"

#include <iostream>

using namespace std;

int main() {

    PacmanState* pac = new PacmanState();

    Ghost red = new Ghost();

    Ghost blue = new Ghost();

    Ghost yellow = new Ghost();

    Ghost pink = new Ghost();

    pac->setGameState(GameState::base);
    
    int lives = 3; // not needed for server testing - Just check for dead or alive state 

    while (lives > 0) {

        SSS obj(pac, red, blue, yellow, pink);

        while (pac->getStatus()) { // might need to change this to a getter since alive_ will be private

            vector<pair<int,int>> path = obj.generatePath(4);

            
        }

        lives--;

        pac->reset();

        red.reset();

        blue.reset();

        yellow.reset();
        
        pink.reset();

        pac->setGameState(GameState::base);

    }

}