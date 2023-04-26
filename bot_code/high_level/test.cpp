#include "Ghost.h"
#include "PacmanState.h"
#include <iostream>
#include "Hash_shit.h"

using namespace std;
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
    PacmanState pac(pos, PacmanState::Direction::right, grid, cherries_eat, curr_powerup);

    std::pair<int, int> ghostLoc = {1, 1};
    // std::pair<int, int> scatterLoc = {, 1};
    Ghost ghost(ghostLoc, Ghost::Direction::up, Ghost::Color::red, Ghost::GhostState::chase);

    Ghost ghost_blue(ghostLoc, Ghost::Direction::up, Ghost::Color::blue, Ghost::GhostState::chase);

    // std::cout << "Blue" << " " << ghost_blue.getGhostLocation().first << " " << ghost_blue.getGhostLocation().second << " " << ghost_blue.get_euclidian_distance(ghost_blue.getGhostLocation(), pac.getBotPos()) << std::endl;
    // std::cout << "Red" << " " << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << " " << ghost.get_euclidian_distance(ghost.getGhostLocation(), pac.getBotPos()) << std::endl;


    // std::pair<int, int> newMoveRed(ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.first, ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.second);
    // std::pair<int, int> newMove(ghost_blue._get_next_blue_chase_move(pac.getBotPos(), pac.getDirection(), ghost_blue.getGhostLocation(), ghost.getGhostLocation()).first.first, ghost_blue._get_next_blue_chase_move(pac.getBotPos(), pac.getDirection(), ghost_blue.getGhostLocation(), ghost.getGhostLocation()).first.second);
    // ghost_blue.ghostMove(newMove);
    // ghost.ghostMove(newMoveRed);

    // std::cout << "Blue" << " " << ghost_blue.getGhostLocation().first << " " << ghost_blue.getGhostLocation().second << " " << ghost_blue.get_euclidian_distance(ghost_blue.getGhostLocation(), pac.getBotPos()) << std::endl;
    // std::cout << "Red" << " " << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << " " << ghost.get_euclidian_distance(ghost.getGhostLocation(), pac.getBotPos()) << std::endl;

    // std::pair<int, int> newMoveRedTwo(ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.first, ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.second);
    // std::pair<int, int> newMoveTwo(ghost_blue._get_next_blue_chase_move(pac.getBotPos(), pac.getDirection(), ghost_blue.getGhostLocation(), ghost.getGhostLocation()).first.first, ghost_blue._get_next_blue_chase_move(pac.getBotPos(), pac.getDirection(), ghost_blue.getGhostLocation(), ghost.getGhostLocation()).first.second);
    // ghost_blue.ghostMove(newMoveTwo);
    // ghost.ghostMove(newMoveRedTwo);

    // std::cout << "Blue" << " " << ghost_blue.getGhostLocation().first << " " << ghost_blue.getGhostLocation().second << " " << ghost_blue.get_euclidian_distance(ghost_blue.getGhostLocation(), pac.getBotPos()) << std::endl;
    // std::cout << "Red" << " " << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << " " << ghost.get_euclidian_distance(ghost.getGhostLocation(), pac.getBotPos()) << std::endl;
    // if (pac.getDirection() == PacmanState::Direction::left) {
    //     std::cout << "you chillin" << std::endl;
    // }
    
    // std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
    //PacBot pac;
    // std::cout << pac.getPos().first << " " << pac.getPos().second << std::endl;
    //Ghost ghost(pac);
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




    // std::cout << pac.getBotPos().first << " " << pac.getBotPos().second << std::endl;
    // while (pac.getBotPos().first != ghost_blue.getGhostLocation().first || pac.getBotPos().second != ghost_blue.getGhostLocation().second) {
    //     std::cout << "Blue" << " " << ghost_blue.getGhostLocation().first << " " << ghost_blue.getGhostLocation().second << " " << ghost_blue.get_euclidian_distance(ghost_blue.getGhostLocation(), pac.getBotPos()) << std::endl;
    //     std::cout << "Red" << " " << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << " " << ghost.get_euclidian_distance(ghost.getGhostLocation(), pac.getBotPos()) << std::endl;
    //     // std::cout << ghost._get_next_red_chase_move().first.first << " " << ghost._get_next_red_chase_move().first.second << std::endl;
    //     std::pair<int, int> newMoveRed(ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.first, ghost._get_next_red_chase_move(pac.getBotPos(), pac.getDirection(), ghost.getGhostLocation(), ghost.getterDirection()).first.second);
    //     std::pair<int, int> newMove(ghost_blue._get_next_blue_chase_move(pac.getBotPos(), pac.getDirection(), ghost_blue.getGhostLocation(), ghost.getGhostLocation()).first.first, ghost_blue._get_next_blue_chase_move(pac.getBotPos(), pac.getDirection(), ghost_blue.getGhostLocation(), ghost.getGhostLocation()).first.second);
    //     ghost_blue.ghostMove(newMove);
    //     ghost.ghostMove(newMoveRed);

    // }
    // std::cout << ghost_blue.getGhostLocation().first << " " << ghost_blue.getGhostLocation().second << std::endl;

    //ghost.ghostMove(std::pair<int, int>(1,1));
    // std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
    // std::cout << pac.getPos().first << " " << pac.getPos().second << std::endl;
    while ((ghost.getGhostLocation().first != pac.getBotPos().first) || (ghost.getGhostLocation().second != pac.getBotPos().second)) {
        std::cout << ghost.getGhostLocation().first << " " << ghost.getGhostLocation().second << std::endl;
        // std::cout << ghost._get_next_red_chase_move(pac.getBotPos()).first.first << " " << ghost._get_next_red_chase_move(pac.getBotPos()).first.second << std::endl;
        std::pair<int, int> newMove(ghost._get_next_red_chase_move(pac.getBotPos()).first.first, ghost._get_next_red_chase_move(pac.getBotPos()).first.second);
        ghost.ghostMove(newMove);
    }

    // this is for testing the hashing 
    //run g++ test.cpp Hashing_shit.cpp -o testing
    // then run the exe file
    

    // vector<vector<int>> grid =  {{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
    //                                     {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
    //                                     {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I}, // 5
    //                                     {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
    //                                     {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I}, // 10
    //                                     {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I},
    //                                     {I,o,I,I,I,I,I,v,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
    //                                     {I,o,I,I,I,I,I,P,I,I,I,I,I,v,I,n,n,n,n,v,I,I,I,I,I,o,I,I,I,I,I},
    //                                     {I,o,o,o,o,I,I,o,o,o,o,I,I,v,I,n,n,n,I,v,v,v,o,I,I,o,o,o,o,o,I}, // 15
    //                                     {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,n,n,n,I,v,I,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,I,I,o,I,I,o,I,I,v,I,I,I,I,I,v,I,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,o,o,o,I,I,o,v,v,v,v,v,v,v,v,v,I,I,o,o,o,o,I,I,I,o,I},
    //                                     {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,v,I,I,I,I,I,I,I,I,o,I,I,I,o,I}, // 20
    //                                     {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
    //                                     {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,v,I,I,I,I,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
    //                                     {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,v,I,e,e,e,I,o,I,I,o,I,I,I,o,I}, // 25
    //                                     {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,v,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
    //                                     {I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}};
                               //        |         |         |         |         |         |         |
                               //        0         5         10        15       20         25        30 
    // tablefiller(); 
    // unsigned long long grit = hashgenerator(grid); 
    //initial grid state
    // std::cout << "Hash Value: " << grit << std::endl; 
    //if we change the grid state
    // int piece = grid[22][14]; 
    // grid[22][14] = v; 
    ///grit ^= ZorbTable[22][14][piece]; 
    return 0;
}