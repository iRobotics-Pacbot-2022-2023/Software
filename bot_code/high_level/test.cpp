#include "Ghost.h"
#include <iostream>

int main () {
    PacBot pac;
    // std::cout << pac.getPos().first << " " << pac.getPos().second << std::endl;
    Ghost ghost(pac);
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



    ghost.ghostMove(std::pair<int, int>(1,1));
    // std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
    // std::cout << pac.getPos().first << " " << pac.getPos().second << std::endl;
    while ((ghost.getGhostLocation().first != pac.getPos().first) || (ghost.getGhostLocation().second != pac.getPos().second)) {
        std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
        // std::cout << ghost._get_next_red_chase_move().first.first << " " << ghost._get_next_red_chase_move().first.second << std::endl;
        std::pair<int, int> newMove(ghost._get_next_red_chase_move().first.first, ghost._get_next_red_chase_move().first.second);
        ghost.ghostMove(newMove);
    }
    return 0;
}