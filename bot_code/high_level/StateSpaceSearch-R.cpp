#include "StateSpaceSearch-R.h"

/*

    const int I = 1; // WALL
    const int o = 2; // Pellet
    const int e = 3; // unreachable
    const int O = 4; // power point
    const int n = 5; // untouchable
    const int P = 6; // Pacbot
    const int v = 7; // visited - No pellets here

*/

void StateSpaceSearchR::updateGameState() {

    pair<int, int> pacman_pos = getPacmanPos();

    pair<int, int> red_pos = Ghost::getRedGhostPos();
    pair<int, int> orange_pos = Ghost::getOrangeGhostPos();
    pair<int, int> blue_pos = Ghost::getBlueGhostPos();
    pair<int, int> pink_pos = Ghost::getPinkGhostPos();

    int cherries_eaten = PacmanState::getCherriesEaten();
    int pellets_eaten = PacmanState::getPelletsEaten();

    int prev_powerups_eaten = PacmanState::getPrevPowerupsEaten();
    int curr_powerups_eaten = PacmanState::getCurrPowerupsEaten();

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

        if (curr_powerups_eaten > prev_powerups_eaten) {
            PacmanState::setPrevPowerupsEaten(curr_powerups_eaten);
            updateFreightenedTimeLeft(30); // idk the time for the freightened state
            state = FREIGHTENED;
        }

    } else if (state == FREIGHTENED) {
        // can only change to BASE

        if (/* freightened time is up */) {
            state = BASE;
        }
    }
}

vector<pair<int, int>> StateSpaceSearchR::generatePath(int length) {

    updateGameState();

    if (state == BASE) {
        return generatePathBase(length);
    } else if (state == CHERRYONE) {
        return generatePathCherryOne(length);
    } else if (state == CHERRYTWO) {
        return generatePathCherryTwo(length);
    } else if (state == POWERUP) {
        return generatePathPowerUp(length);
    } else if (state == FREIGHTENED) {
        return generatePathFreightened(length);
    }
}

/////////////////////////////// BASE ///////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathBase(int length) {
    /*
    - Distance to ghost (maximize) (euclidean)
    - pellet collected
    - (DO NOT COLLECT POWER UP) - 0 pts
    Only look at o & v for neighbors
    */

   map<BaseNode, BaseNode> node_to_parent;

   vector<BaseNode> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<BaseNode> queue;

   BaseNode nil; // represents null

   BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = Ghost::getRedGhostPos();
    parent.blue_ghost_pos = Ghost::getBlueGhostPos();
    parent.orange_ghost_pos = Ghost::getOrangeGhostPos();
    parent.pink_ghost_pos = Ghost::getPinkGhostPos();

    parent.grid = grid;
    parent.points = 0;
    parent.depth = 0;

    node_to_parent[parent] = nil;

    queue.push(parent);

    while (!queue.empty()) {

        BaseNode curr = queue.front();
        queue.pop();

        pair<int, int> curr_position = curr.pacman_pos;
        PacmanState::Direction curr_direction = curr.pacman_dir;

        pair<int, int> curr_red_ghost_pos = curr.red_ghost_pos;
        pair<int, int> curr_blue_ghost_pos = curr.blue_ghost_pos;
        pair<int, int> curr_orange_ghost_pos = curr.orange_ghost_pos;
        pair<int, int> curr_pink_ghost_pos = curr.pink_ghost_pos;

        vector<vector<int>> curr_grid = curr.grid;
        int curr_points = curr.points;
        int curr_depth = curr.depth;

        vector<pair<int, int>> neighbors = getNeighborsBase(curr_position, curr_grid);

        // if depth = length dont add to queue

        for (pair<int, int> neighbor : neighbors) {
            // p, v, o
            BaseNode child;
            child.pacman_pos = neighbor;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::Up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::Down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::Right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::Left;

            child.red_ghost_pos = Ghost::moveRed(child.pacman_pos, child.pacman_dir, child.grid);
            child.blue_ghost_pos = Ghost::moveBlue(child.pacman_pos, child.pacman_dir, child.grid, child.red_ghost_pos);
            child.orange_ghost_pos = Ghost::moveOrange();
            child.pink_ghost_pos = Ghost::movePink(child.pacman_pos, child.pacman_dir, child.grid);;

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }
            
            if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector

            // if one of the ghost positions is equal to the neighbor position, dont add to queue and set points to -1 or something
            
            
            if (child.depth == length) {
                node_to_parent[child] = curr;
                final_positions.push_back(child);
            } else if (child.depth < length) {
                queue.push(child);
                node_to_parent[child] = curr;
            }
        }
    }

    /* Figure out and calculate the ghost positions for all the final positions*/
    // for all the basenodes of depth = length, calculate the ghost positions and recalulate score

    BaseNode best_node;
    best_node.points = -1;

    for (auto n : node_to_parent) {
        BaseNode curr = n.first;
        
        if (curr.depth == length && curr.points > best_node.points) {
            best_node = curr;
        }
    }

    BaseNode filler = best_node;

    updatePacmanDir(filler.pacman_dir);

    vector<pair<int, int>> path;

    while (filler != nil) {
        path.insert(path.begin(), filler.pacman_pos);
        filler = node_to_parent[filler];
    }

    return path;


}

// Don't hit the power up
vector<pair<int, int>> getNeighborsBase(pair<int, int> pos, vector<vector<int>> grid) {
    vector<pair<int, int>> neighbors;
    neighbors[0] = make_pair(pos.first - 1, pos.second); // left
    neighbors[1] = make_pair(pos.first, pos.second - 1); // down
    neighbors[2] = make_pair(pos.first + 1, pos.second); // right
    neighbors[3] = make_pair(pos.first, pos.second + 1); // up
    neighbors[4] = make_pair(pos.first, pos.second); // Itself

    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[0];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || y > 27 || y < 0 || y > 20 
            || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n || grid[x][y] == O) neighbors.erase(neighbors.begin()); 
        else i++;
    }

    return neighbors;
}

/////////////////////////////// CHERRY ONE ///////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathCherryOne(int length) {
    /*
    - Distance to ghost (maximize) (euclidean) (score at end)
    - pellet collected
    - distance to cherry (minimize) (BFS / A*) (score at end)
    - distance to nearest pellet (minimize) (BFS/A*) (score at end)
    Pellet's collected > distance to cherry
    don't collect power pellet
    */

}

/////////////////////////////// CHERRY TWO ///////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathCherryTwo(int length) {

}

/////////////////////////////// POWER UP ///////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathPowerUp(int length) {

}

/////////////////////////////// FREIGHTENED ///////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathFreightened(int length) {

}

int StateSpaceSearchR::euclideanDistance(pair<int, int> start, pair<int, int> goal) {
    int x1 = start.first;
    int y1 = start.second;
    int x2 = goal.first;
    int y2 = goal.second;

    return pow(x2 - x1, 2) + pow(y2 - y1, 2);
}