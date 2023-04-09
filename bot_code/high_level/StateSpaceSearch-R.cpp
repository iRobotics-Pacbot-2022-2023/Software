#include "StateSpaceSearch-R.h"

void StateSpaceSearchR::updateGameState() {
    if (state == BASE) {
        // can only change to CHERRYONE or POWERUP

    } else if (state == CHERRYONE) {
        // can only change to CHERRYTWO

    } else if (state == CHERRYTWO) {
        // can only change to BASE

    } else if (state == POWERUP) {
        // can only change to FREIGHTENED

    } else if (state == FREIGHTENED) {
        // can only change to BASE

    }

}