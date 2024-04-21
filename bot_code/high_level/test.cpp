
#include "Ghost.h"
#include "PacmanState.h"
#include <iostream>
// #include "Hash.h"
#include "StateSpaceSearch-R.h"
using namespace std;
void printGrid(std::vector<std::vector<int>> grid);
void printGhostState(Ghost ghost_red, Ghost ghost_blue, Ghost ghost_orange, Ghost ghost_pink);
void printGameState(PacmanState p);
void updateGameState(PacmanState& pacman, Ghost red_ghost, Ghost blue_ghost, Ghost orange_ghost, Ghost pink_ghost);
int euclideanDistance(pair<int, int> start, pair<int, int> goal);
int main () {
    // PacBot pac;
    vector<vector<int>> grid  ={{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
                                {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
                                {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I}, // 5
                                {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
                                {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
                                {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
                                {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I}, // 10
                                {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
                                {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I},
                                {I,o,I,I,I,I,I,v,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
                                {I,o,I,I,I,I,I,P,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
                                {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I}, // 15
                                {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
                                {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
                                {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I}, // 20
                                {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
                                {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
                                {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I}, // 25
                                {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
                                {I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}};
                        //       |         |         |         |         |         |         |
                        //       0         5         10        15        20        25       30 
    // void printGrid(vector<vector<int>> grid);

    int num_pellets = 0;
    for (vector<int> vect : grid) {
        for (int i : vect) {
            if (i == o) num_pellets++;
        }
    }
    
    std::pair<int, int> pos = {14, 7};
    // int pelletsLeft = 50;
    int pellets_eat = 0;
    int prev_powerups = 0;
    int curr_powerup = 0;
    // int cherries_eat = 0;
    PacmanState pac(pos, PacmanState::Direction::right, pellets_eat, prev_powerups, curr_powerup, PacmanState::GameState::BASE);

    // std::pair<int, int> redGhostLoc = {1, 1};
    // std::pair<int, int> scatterLoc = {, 1};
    Ghost ghost_red(RED_GHOST_STARTING_POSITION, Ghost::Direction::up, Ghost::Color::red, Ghost::GhostState::chase);

    Ghost ghost_blue(BLUE_GHOST_STARTING_POSITION, Ghost::Direction::up, Ghost::Color::blue, Ghost::GhostState::chase);

    Ghost ghost_orange(ORANGE_GHOST_STARTING_POSITION, Ghost::Direction::up, Ghost::Color::orange, Ghost::GhostState::chase);
    Ghost ghost_pink(PINK_GHOST_STARTING_POSITION, Ghost::Direction::up, Ghost::Color::red, Ghost::GhostState::chase);

    

    
    // searchState.changeGameState(StateSpaceSearchR::GameState::CHERRYTWO);

    // searchState.generatePath(4);
    int count = 0;
    while (count < 25) {

        printGameState(pac);

        cout << "PACMAN STATE Pellets eaten: " << pac.getPelletsEaten() << endl;

        StateSpaceSearchR searchState(pac, ghost_red, ghost_blue, ghost_orange, ghost_pink, grid);

        cout << "COUNT = " << count << endl;

        printGhostState(ghost_red, ghost_blue, ghost_orange, ghost_pink);
        
        std::pair<int, int> pacMove;
        vector<pair<int, int>> our_path = searchState.generatePath(4);
        if (our_path.size() == 1) {
            pacMove = our_path.at(0);
        } else if (our_path.size() == 0) {
            cout << "FAIL: PATH LENGTH 0" << endl;
            break;
        } else {
            pacMove = our_path.at(1);
        }

        // std::cout << "PacMOVE: " << pacMove.first << " " << pacMove.second << std::endl;

        // update pellet count
        if (grid[pacMove.first][pacMove.second] == o) {
            pac.setPelletsEaten(pac.getPelletsEaten() + 1);
        } else if (grid[pacMove.first][pacMove.second] == O) {
            pac.setPowerupsEaten(pac.getPowerupsEaten() + 1);
        } else if (pac.getGameState() == PacmanState::GameState::CHERRYTWO 
            && pacMove.first == 13 && pacMove.second == 13) {
            pac.setCherriesEaten(pac.getCherriesEaten() + 1);
        }
        
        // update grid
        grid = searchState.changeGrid(grid, pac.getBotPos(), pacMove);
        // pac.changeGrid(grid, pac.getBotPos(), pacMove);

        // update pacman position
        pac.changePos(pacMove);
        std::cout << "Pac new move: " << pacMove.first << " " << pacMove.second << std::endl;

        // update pacman direction
        pac.setDirection(searchState.getPacmanDir());

        // RED GHOST
        cout << "Prev ghost pos: " << ghost_red.getGhostLocation().first << " " << ghost_red.getGhostLocation().second << endl;
        // PacmanState pac_test(pacMove, searchState.getPacmanDir(), grid, pellets_eat, prev_powerups, curr_powerup);
        std::pair<int, int> newRedMove(ghost_red._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_red).first.first, 
                                    ghost_red._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_red).first.second);
        ghost_red.ghostMove(newRedMove);
        cout << "Next ghost pos: " << ghost_red.getGhostLocation().first << " " << ghost_red.getGhostLocation().second << endl;
        // std::cout << "Ghost move: " << newMove.first << " " << newMove.second << std::endl;
        

        // BLUE GHOST
        cout << "Prev ghost pos: " << ghost_blue.getGhostLocation().first << " " << ghost_blue.getGhostLocation().second << endl;
        // PacmanState pac_test(pacMove, searchState.getPacmanDir(), grid, pellets_eat, prev_powerups, curr_powerup);
        std::pair<int, int> newBlueMove(ghost_blue._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_blue).first.first, 
                                    ghost_blue._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_blue).first.second);
        ghost_blue.ghostMove(newBlueMove);
        cout << "Next ghost pos: " << ghost_blue.getGhostLocation().first << " " << ghost_blue.getGhostLocation().second << endl;
        // std::cout << "Ghost move: " << newMove.first << " " << newMove.second << std::endl;
        

        // ORANGE GHOST
        cout << "Prev ghost pos: " << ghost_orange.getGhostLocation().first << " " << ghost_orange.getGhostLocation().second << endl;
        // PacmanState pac_test(pacMove, searchState.getPacmanDir(), grid, pellets_eat, prev_powerups, curr_powerup);
        std::pair<int, int> newOrangeMove(ghost_orange._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_orange).first.first, 
                                    ghost_orange._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_orange).first.second);
        ghost_orange.ghostMove(newOrangeMove);
        cout << "Next ghost pos: " << ghost_orange.getGhostLocation().first << " " << ghost_orange.getGhostLocation().second << endl;

        // PINK GHOST
        cout << "Prev ghost pos: " << ghost_pink.getGhostLocation().first << " " << ghost_pink.getGhostLocation().second << endl;
        // PacmanState pac_test(pacMove, searchState.getPacmanDir(), grid, pellets_eat, prev_powerups, curr_powerup);
        std::pair<int, int> newPinkMove(ghost_pink._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_pink).first.first, 
                                    ghost_pink._get_next_state_move(pac.getBotPos(), pac.getDirection(), ghost_pink).first.second);
        ghost_pink.ghostMove(newPinkMove);
        cout << "Next ghost pos: " << ghost_pink.getGhostLocation().first << " " << ghost_pink.getGhostLocation().second << endl;

        updateGameState(pac, ghost_red, ghost_blue, ghost_orange, ghost_pink);

        if (pac.getGameState() == PacmanState::BASE) cout << "Test file pacman state: BASE" << endl;
        else if (pac.getGameState() == PacmanState::CHERRYONE) cout << "Test file pacman state: CHERRYONE" << endl;
        else if (pac.getGameState() == PacmanState::CHERRYTWO) cout << "Test file pacman state: CHERRYTWO" << endl;
        else if (pac.getGameState() == PacmanState::POWERUP) cout << "Test file pacman state: POWERUP" << endl;
        else if (pac.getGameState() == PacmanState::FREIGHTENED) cout << "Test file pacman state: FREIGHTENED" << endl;

        count++;

        cout << "\n" << endl;
    }

    int r = 0;
    for (vector<int> vect : grid) {
        for (int i : vect) {
            if (i == I) cout << 'I' << " ";
            if (i == o) cout << 'o' << " ";
            if (i == e) cout << 'e' << " ";
            if (i == O) cout << 'O' << " ";
            if (i == n) cout << 'n' << " ";
            if (i == P) cout << 'P' << " ";
            if (i == v) cout << 'v' << " ";
        }
        cout << "\n" << endl;
        r++;
    }
    cout << "rows: " << r << endl;

    cout << "\n" << endl;
    cout << "Final position: " << pac.getBotPos().first << " " << pac.getBotPos().second << endl;
    cout << "Final pellets eaten: " << pac.getPelletsEaten() << endl;

    cout << "Total num pellets: " << num_pellets << endl;
    
    return 0;
}


void printGameState(PacmanState p) {
    if (p.getGameState() == PacmanState::GameState::BASE) cout << "PACMAN IN BASE STATE" << endl;
    else if (p.getGameState() == PacmanState::GameState::CHERRYONE) cout << "PACMAN IN CHERRYONE STATE" << endl;
    else if (p.getGameState() == PacmanState::GameState::CHERRYTWO) cout << "PACMAN IN CHERRYTWO STATE" << endl;
    else if (p.getGameState() == PacmanState::GameState::POWERUP) cout << "PACMAN IN POWERUP STATE" << endl;
    else if (p.getGameState() == PacmanState::GameState::FREIGHTENED) cout << "PACMAN IN FREIGHTENED STATE" << endl;
}

void printGhostState(Ghost ghost_red, Ghost ghost_blue, Ghost ghost_orange, Ghost ghost_pink) {
    if (ghost_red.getGhostState() == Ghost::GhostState::frightened) {
            std::cout << "red is freightened" << std::endl;
    } else if (ghost_red.getGhostState() == Ghost::GhostState::chase) {
        std::cout << "red is chase" << std::endl;
    } else if (ghost_red.getGhostState() == Ghost::GhostState::scatter) {
        std::cout << "red is scatter" << std::endl;
    }

    if (ghost_blue.getGhostState() == Ghost::GhostState::frightened) {
        std::cout << "blue is freightened" << std::endl;
    } else if (ghost_blue.getGhostState() == Ghost::GhostState::chase) {
        std::cout << "blue is chase" << std::endl;
    } else if (ghost_blue.getGhostState() == Ghost::GhostState::scatter) {
        std::cout << "blue is scatter" << std::endl;
    }

    if (ghost_orange.getGhostState() == Ghost::GhostState::frightened) {
        std::cout << "orange is freightened" << std::endl;
    } else if (ghost_orange.getGhostState() == Ghost::GhostState::chase) {
        std::cout << "orange is chase" << std::endl;
    } else if (ghost_orange.getGhostState() == Ghost::GhostState::scatter) {
        std::cout << "orange is scatter" << std::endl;
    }

    if (ghost_pink.getGhostState() == Ghost::GhostState::frightened) {
        std::cout << "pink is freightened" << std::endl;
    } else if (ghost_pink.getGhostState() == Ghost::GhostState::chase) {
        std::cout << "pink is chase" << std::endl;
    } else if (ghost_pink.getGhostState() == Ghost::GhostState::scatter) {
        std::cout << "pink is scatter" << std::endl;
    }
}

void updateGameState(PacmanState& pacman, Ghost red_ghost, Ghost blue_ghost, Ghost orange_ghost, Ghost pink_ghost) {

    // int prev_cherries_eaten = pacman.getCherriesEaten();
    // int curr_cherries_eaten = PacmanState::getCurrCherriesEaten();


    int pellets_eaten = pacman.getPelletsEaten();
    int cherries_eaten = pacman.getCherriesEaten();

    // int prev_powerups_eaten = 
    // int curr_powerups_eaten = ();

    if (pacman.getGameState() == PacmanState::GameState::BASE) {
        // std::cout << "StateSpace Search: Start in BASE" << std::endl;


        if (euclideanDistance(pacman.getBotPos(), red_ghost.getGhostLocation()) <= 5 || euclideanDistance(pacman.getBotPos(), blue_ghost.getGhostLocation()) <= 5
            || euclideanDistance(pacman.getBotPos(), orange_ghost.getGhostLocation()) <= 5 || euclideanDistance(pacman.getBotPos(), pink_ghost.getGhostLocation()) <= 5) {
                // std::cout << "YOU ARE CLOSE" << std::endl;
                std::cout << "CHANGE TO POWERUP" << std::endl;
                pacman.setGameState(PacmanState::GameState::POWERUP);
            // state = PacmanState::GameState::POWERUP;
        }

        else if ((cherries_eaten == 0 && pellets_eaten >= 50) || (cherries_eaten == 1 && pellets_eaten >= 150)) {
            // std::cout << "bruh whhat IS YOU DOING" << std::endl;
            std::cout << "CHANGE TO CHERRYONE" << std::endl;
            pacman.setGameState(PacmanState::GameState::CHERRYONE);
        }

    } else if (pacman.getGameState() == PacmanState::GameState::CHERRYONE) {
        // can only change to CHERRYTWO

        // std::cout << "StateSpace Search: Start in CHERRYONE" << std::endl;

        if ((cherries_eaten == 0 && pellets_eaten >= 70) || (cherries_eaten == 1 && pellets_eaten >= 170)) {
            std::cout << "CHANGE TO CHERRY TWO" << std::endl;
            pacman.setCherryTimeLeft(30);
            pacman.setGameState(PacmanState::GameState::CHERRYTWO);
        }

    } else if (pacman.getGameState() == PacmanState::GameState::CHERRYTWO) { // Method to change to Base in the cherrytwo function

        // std::cout << "StateSpace Search: Start in CHERRYTWO" << std::endl;
        // can only change to BASE

        // it;s inferred that if cherry is eaten, curr_cherries_eaten incrememnts
        if (pacman.getCherryTimeLeft() == 0) {
            std::cout << "CHANGE TO BASE" << std::endl;
            cherries_eaten++;
            pacman.setGameState(PacmanState::GameState::BASE);
        }

    } else if (pacman.getGameState() == PacmanState::GameState::POWERUP) { // Method to change to Freightened in powerup function
        // can only change to FREIGHTENED
        // std::cout << "StateSpace Search: Start in POWERUP" << std::endl;
        // if (curr_powerups_eaten > prev_powerups_eaten) {
        //     std::cout << curr_powerups_eaten << " " << prev_powerups_eaten << std::endl;
        //     prev_cherries_eaten = curr_cherries_eaten;
        //     updateFreightenedTimeLeft(30); // idk the time for the freightened state
        //     red_ghost.changeGhostState(Ghost::GhostState::frightened);
        //     blue_ghost.changeGhostState(Ghost::GhostState::frightened);
        //     orange_ghost.changeGhostState(Ghost::GhostState::frightened);
        //     pink_ghost.changeGhostState(Ghost::GhostState::frightened);
        //     pacman.setGameState(PacmanState::GameState::FREIGHTENED);
        // }

    } else if (pacman.getGameState() == PacmanState::GameState::FREIGHTENED) {
        // can only change to BASE

        // std::cout << "StateSpace Search: Start in FREIGHTENED" << std::endl;

        if (pacman.getFrieghtenedTimeLeft() == 0) {
            std::cout << "CHANGE TO BASE" << std::endl;
            red_ghost.setGhostState(Ghost::GhostState::chase);
            blue_ghost.setGhostState(Ghost::GhostState::chase);
            orange_ghost.setGhostState(Ghost::GhostState::chase);
            pink_ghost.setGhostState(Ghost::GhostState::chase);
            pacman.setGameState(PacmanState::GameState::BASE);
        }
    }
}

int euclideanDistance(pair<int, int> start, pair<int, int> goal) {
    int x1 = start.first;
    int y1 = start.second;
    int x2 = goal.first;
    int y2 = goal.second;

    return (int) sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}