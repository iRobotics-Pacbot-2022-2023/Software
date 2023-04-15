#include "PacBot.h"

// this is for testing
    std::pair<int, int> PacBot::getPos() {
        return pos;
    }
    PacBot::PacBot() {
        pos = std::pair<int, int>(14, 14);
        pacdirection_ = up;
    }
    void PacBot::move(std::pair<int, int> newLoc) {
        pos = newLoc;
    }

    void PacBot::changeDirection(PacBot::PacDirection newDirection) {
        pacdirection_ = newDirection;
    }   

    PacBot::PacDirection PacBot::getPacDirection() {
        return pacdirection_;
    }