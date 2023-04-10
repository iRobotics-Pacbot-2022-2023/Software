#include "StateSpaceSearch-R.h"

void StateSpaceSearchR::updateGameState() {

    pair<int, int> pacman_pos = getPacmanPos();

    pair<int, int> red_pos = Ghost::getRedPos();
    pair<int, int> orange_pos = Ghost::getOrangePos();
    pair<int, int> blue_pos = Ghost::getBluePos();
    pair<int, int> pink_pos = Ghost::getPinkPos();

    int cherries_eaten = PacmanState::getCherriesEaten();
        int pellets_eaten = PacmanState::getPelletsEaten();

    if (state == BASE) {
        // can only change to CHERRYONE or POWERUP

        if (euclideanDistance(pacman_pos, red_pos) <= 25 || euclideanDistance(pacman_pos, red_pos) <= 25
            || euclideanDistance(pacman_pos, red_pos) <= 25 || euclideanDistance(pacman_pos, red_pos) <= 25) {
            state = POWERUP;
        }

        if ((cherries_eaten == 0 && pellets_eaten >= 50) || (cherries_eaten == 1 && pellets_eaten >= 150)) {
            state = CHERRYONE;
        }

    } else if (state == CHERRYONE) {
        // can only change to CHERRYTWO
        if ((cherries_eaten == 0 && pellets_eaten >= 70) || (cherries_eaten == 1 && pellets_eaten >= 170)) {
            state = CHERRYTWO;
        }

    } else if (state == CHERRYTWO) {
        // can only change to BASE
        if (cherries_eaten == 2 /* or time runs out */) {
            state = BASE;
        }

    } else if (state == POWERUP) {
        // can only change to FREIGHTENED
        if (/* we collected powerup */) {
            state = FREIGHTENED;
        }

    } else if (state == FREIGHTENED) {
        // can only change to BASE
        if (/* freightened time is up */) {
            state = BASE;
        }
    }
}

vector<pair<int, int>> StateSpaceSearchR::generatePath() {

    updateGameState();

    if (state == BASE) {
        return generatePathBase();
    } else if (state == CHERRYONE) {
        return generatePathCherryOne();
    } else if (state == CHERRYTWO) {
        return generatePathCherryTwo();
    } else if (state == POWERUP) {
        return generatePathPowerUp();
    } else if (state == FREIGHTENED) {
        return generatePathFreightened();
    }
}

int StateSpaceSearchR::euclideanDistance(pair<int, int> start, pair<int, int> goal) {
    int x1 = start.first;
    int y1 = start.second;
    int x2 = goal.first;
    int y2 = goal.second;

    return pow(x2 - x1, 2) + pow(y2 - y1, 2);
}