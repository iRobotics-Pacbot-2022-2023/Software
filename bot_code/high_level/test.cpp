#include "Ghost.h"
#include "PacmanState.h"
#include <iostream>

int main () {
    // PacBot pac;
    vector<vector<int>> grid  =  {{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
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
    std::pair<int, int> pos = {14, 7};
    int pelletsLeft = 50;
    int pellets_eat = 0;
    int prev_powerups = 0;
    int curr_powerup = 0;
    int cherries_eat = 0;
    PacmanState pac(pos, PacmanState::Direction::up, grid, pelletsLeft, pellets_eat, cherries_eat, prev_powerups, curr_powerup);

    std::pair<int, int> ghostLoc = {1, 1};
    std::pair<int, int> scatterLoc = {25, 32};
    Ghost ghost(ghostLoc, scatterLoc, pos, Ghost::Direction::up, Ghost::GhostState::chase);

    // if (pac.getDirection() == PacmanState::Direction::left) {
    //     std::cout << "you chillin" << std::endl;
    // }
    
    // std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
    // std::cout << pac.getPos().first << " " << pac.getPos().second << std::endl;
    // Ghost ghost();
    // std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
    // std::cout << ghost.is_move_legal(std::pair<int, int>(0,0)) << std::endl;
    // std::cout << ghost._get_next_pink_chase_move().first.first << " " << ghost._get_next_pink_chase_move().first.second << std::endl;
    // // std::cout << ghost_.is_move_legal
    // // pac.move(std::pair<int, int>(14,13));
    // // std::cout << ghost.getPac().getPos().first << " " << ghost.getPac().getPos().second << std::endl;
    // std::cout << ghost.getGrid().at(13).at(7) << std::endl;

    // ghost.ghostMove(std::pair<int, int>(12, 7));
    // std::cout << ghost._get_next_red_chase_move().first.first << " " << ghost._get_next_red_chase_move().first.second << std::endl;
    // // ghost.ghostMove(std::pair<int, int>(13,7));
    // // std::cout << ghost._get_next_pink_chase_move().first.first << " " << ghost._get_next_pink_chase_move().first.second << std::endl;
    // ghost.ghostMove(std::pair<int, int>(13, 7));
    // std::cout << ghost._get_next_red_chase_move().first.first << " " << ghost._get_next_red_chase_move().first.second << std::endl;
    
    // ghost.ghostMove(std::pair<int, int>(1,10));
    // std::vector<std::pair<int, int>> possible = ghost.find_possible_moves();
    // for (int i = 0; i < possible.size(); ++i) {
    //     std::cout << possible.at(i).first << " " << possible.at(i).second << std::endl;
    // }
    // newMove = std::pair<int, int>(ghost.get_move_based_on_target(pac.getPos()).first.first, ghost.get_move_based_on_target(pac.getPos()).first.second);
    // ghost.get_move_based_on_target(pac.getPos());
    // ghost.ghostMove(std::pair<int, int>(2,10));
    // if (ghost.getterDirection() == Ghost::right) {
    //     std::cout << "you went right, test successful" << std::endl;
    // }

    // std::cout << ghost.get_move_based_on_target(pac.getPos()).first.first << " " << ghost.get_move_based_on_target(pac.getPos()).first.second << std::endl;
    // ghost.ghostMove(newMove);
    // std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;



    // ghost.ghostMove(std::pair<int, int>(1,1));
    // // std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
    // // std::cout << pac.getPos().first << " " << pac.getPos().second << std::endl;

    // // (ghost.getGhostLocation().first != pac.getPos().first) || (ghost.getGhostLocation().second != pac.getPos().second)
    // int count = 100;
    while (pac.getBotPos().first != ghost.getGhostLocation().first || pac.getBotPos().second != ghost.getGhostLocation().second) {
        std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << " " << ghost.get_euclidian_distance(ghost.getGhostLocation(), pac.getBotPos()) << std::endl;
        // std::cout << ghost._get_next_red_chase_move().first.first << " " << ghost._get_next_red_chase_move().first.second << std::endl;
        std::pair<int, int> newMove(ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.first, ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.second);
        ghost.ghostMove(newMove);
    }
    std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
    return 0;
}