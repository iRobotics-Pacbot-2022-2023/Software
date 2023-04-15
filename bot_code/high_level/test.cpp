#include "Ghost.h"
#include <iostream>

int main () {
    PacBot pac;
    Ghost ghost(pac);
    std::cout << ghost.is_move_legal(std::pair<int, int>(1, 1)) << std::endl;
    // std::cout << ghost_.is_move_legal
    return 0;
}