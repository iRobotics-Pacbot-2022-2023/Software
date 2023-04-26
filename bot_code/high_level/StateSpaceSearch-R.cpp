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

    int prev_cherries_eaten = PacmanState::getPrevCherriesEaten();
    int curr_cherries_eaten = PacmanState::getCurrCherriesEaten();


    int pellets_eaten = PacmanState::getPelletsEaten();

    int prev_powerups_eaten = getPrevPowerupsEaten();
    int curr_powerups_eaten = getCurrPowerupsEaten();

    if (state == BASE) {
        // can only change to CHERRYONE or POWERUP

        if (euclideanDistance(pacman_pos, red_pos) <= 5 || euclideanDistance(pacman_pos, red_pos) <= 5
            || euclideanDistance(pacman_pos, red_pos) <= 5 || euclideanDistance(pacman_pos, red_pos) <= 5) {
            state = POWERUP;
        }

        else if ((curr_cherries_eaten == 0 && pellets_eaten >= 50) || (curr_cherries_eaten == 1 && pellets_eaten >= 150)) {
            state = CHERRYONE;
        }

    } else if (state == CHERRYONE) {
        // can only change to CHERRYTWO

        if ((curr_cherries_eaten == 0 && pellets_eaten >= 70) || (curr_cherries_eaten == 1 && pellets_eaten >= 170)) {
            state = CHERRYTWO;
        }

    } else if (state == CHERRYTWO) {
        // can only change to BASE

        // it;s inferred that if cherry is eaten, curr_cherries_eaten incrememnts

        if (curr_cherries_eaten > prev_cherries_eaten /* or time runs out */) {
            setPrevCherriesEaten(curr_cherries_eaten);
            state = BASE;
        }

    } else if (state == POWERUP) {
        // can only change to FREIGHTENED

        if (curr_powerups_eaten > prev_powerups_eaten) {
            setPrevPowerupsEaten(curr_powerups_eaten);
            updateFreightenedTimeLeft(30); // idk the time for the freightened state
            red_ghost_state = GhostState::freightened;
            blue_ghost_state = GhostState::freightened;
            orange_ghost_state = GhostState::freightened;
            pink_ghost_state = GhostState::freightened;
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

////////////////////////////////////////////////////////////// BASE //////////////////////////////////////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathBase(int length) {
    /*
    - Distance to ghost (maximize) (euclidean)
    - pellet collected
    - (DO NOT COLLECT POWER UP) - 0 pts
    Only look at o & v for neighbors
    */

   map<BaseNode, BaseNode> node_to_parent;

   vector<BaseNode&> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<BaseNode> queue;

   BaseNode nil; // represents null

   BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = Ghost::getRedGhostPos();
    parent.red_ghost_dir = Ghost::getRedGhostDir();
    parent.blue_ghost_pos = Ghost::getBlueGhostPos();
    parent.blue_ghost_dir = Ghost::getBlueGhostDir();
    parent.orange_ghost_pos = Ghost::getOrangeGhostPos();
    parent.orange_ghost_dir = Ghost::getOrangeGhostDir();
    parent.pink_ghost_pos = Ghost::getPinkGhostPos();
    parent.pink_ghost_dir = Ghost::getPinkGhostDir();

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
        Ghost::Direction curr_red_ghost_dir = curr.red_ghost_dir;
        pair<int, int> curr_blue_ghost_pos = curr.blue_ghost_pos;
        Ghost::Direction curr_blue_ghost_dir = curr.blue_ghost_dir;
        pair<int, int> curr_orange_ghost_pos = curr.orange_ghost_pos;
        Ghost::Direction curr_orange_ghost_dir = curr.orange_ghost_dir;
        pair<int, int> curr_pink_ghost_pos = curr.pink_ghost_pos;
        Ghost::Direction curr_pink_ghost_dir = curr.pink_ghost_dir;

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
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            // if one of the ghost positions is equal to the neighbor position, dont add to queue and set points to -1 or something

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            child.red_ghost_pos, child.red_ghost_dir = Ghost::moveRed(child.pacman_pos, child.pacman_dir, curr_red_ghost_pos, curr_red_ghost_dir);
            child.blue_ghost_pos, child.blue_ghost_dir = Ghost::moveBlue(child.pacman_pos, child.pacman_dir, child.red_ghost_pos, child.red_ghost_dir, curr_blue_ghost_pos, curr_blue_ghost_dir);
            child.orange_ghost_pos, child.orange_ghost_dir = Ghost::moveOrange(curr_orange_ghost_pos, curr_orange_ghost_dir);
            child.pink_ghost_pos, child.pink_ghost_dir = Ghost::movePink(child.pacman_pos, child.pacman_dir, curr_pink_ghost_pos, curr_pink_ghost_dir);

            // OR we could add these ghost positions to a std::set and just check
            // if we have pacman_pos in the set or not

            // if one of the ghost positions is equal to the neighbor position, dont add to queue and set points to -1 or something

            // DOUBLE CHECK
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

    for (auto n : final_positions) { // node_to_parent
        BaseNode curr = n; // n.first

        if (curr.depth == length) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += (red_distance + blue_distance + orange_distance + pink_distance);

            if (curr.points > best_node.points) best_node = curr;

        }
    }

    BaseNode filler = best_node;

    updatePacmanDir(filler.pacman_dir); // or we can get this from robomodules

    vector<pair<int, int>> path;

    while (!baseNodeEquals(filler, nil)) {
        path.insert(path.begin(), filler.pacman_pos);
        filler = node_to_parent[filler];
    }

    return path;

}

bool StateSpaceSearchR::baseNodeEquals(BaseNode a, BaseNode b) {
    return a.pacman_pos == b.pacman_pos && a.pacman_dir == b.pacman_dir && a.red_ghost_pos == b.red_ghost_pos
        && a.blue_ghost_pos == b.blue_ghost_pos && a.orange_ghost_pos == b.orange_ghost_pos
        && a.pink_ghost_pos == b.pink_ghost_pos && a.points == b.points && a.depth == b.depth;
    // return a.grid == b.grid;
}

// Don't hit the power up
vector<pair<int, int>> StateSpaceSearchR::getNeighborsBase(pair<int, int> pos, vector<vector<int>> grid) {
    vector<pair<int, int>> neighbors;
    neighbors.push_back(make_pair(pos.first - 1, pos.second)); // left
    neighbors.push_back(make_pair(pos.first, pos.second - 1)); // down
    neighbors.push_back(make_pair(pos.first + 1, pos.second)); // right
    neighbors.push_back(make_pair(pos.first, pos.second + 1)); // up
    neighbors.push_back(make_pair(pos.first, pos.second)); // Itself

    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[i];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || y > 27 || y < 0 || y > 30 
            || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n || grid[x][y] == O) neighbors.erase(neighbors.begin() + i); 
        else i++;
    }

    return neighbors;
}

////////////////////////////////////////////////////////////// CHERRY ONE //////////////////////////////////////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathCherryOne(int length) {
    /*
    - Distance to ghost (maximize) (euclidean) (score at end)
    - pellet collected
    - distance to cherry (minimize) (BFS / A*) (score at end) (DO NOT HIT THE POSITION) (!= )
    - distance to nearest pellet (minimize) (BFS/A*) (score at end)
    Pellet's collected > distance to cherry
    don't collect power pellet (neighbor thing)
    */

   map<BaseNode, BaseNode> node_to_parent;

   vector<BaseNode&> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<BaseNode> queue;

   BaseNode nil; // represents null

   BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = Ghost::getRedGhostPos();
    parent.red_ghost_dir = Ghost::getRedGhostDir();
    parent.blue_ghost_pos = Ghost::getBlueGhostPos();
    parent.blue_ghost_dir = Ghost::getBlueGhostDir();
    parent.orange_ghost_pos = Ghost::getOrangeGhostPos();
    parent.orange_ghost_dir = Ghost::getOrangeGhostDir();
    parent.pink_ghost_pos = Ghost::getPinkGhostPos();
    parent.pink_ghost_dir = Ghost::getPinkGhostDir();

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
        Ghost::Direction curr_red_ghost_dir = curr.red_ghost_dir;
        pair<int, int> curr_blue_ghost_pos = curr.blue_ghost_pos;
        Ghost::Direction curr_blue_ghost_dir = curr.blue_ghost_dir;
        pair<int, int> curr_orange_ghost_pos = curr.orange_ghost_pos;
        Ghost::Direction curr_orange_ghost_dir = curr.orange_ghost_dir;
        pair<int, int> curr_pink_ghost_pos = curr.pink_ghost_pos;
        Ghost::Direction curr_pink_ghost_dir = curr.pink_ghost_dir;

        vector<vector<int>> curr_grid = curr.grid;
        int curr_points = curr.points;
        int curr_depth = curr.depth;

        vector<pair<int, int>> neighbors = getNeighborsCherryOne(curr_position, curr_grid);

        for (auto neighbor : neighbors) {
            BaseNode child;
            child.pacman_pos = neighbor;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            child.red_ghost_pos, child.red_ghost_dir = Ghost::moveRed(child.pacman_pos, child.pacman_dir, curr_red_ghost_pos, curr_red_ghost_dir);
            child.blue_ghost_pos, child.blue_ghost_dir = Ghost::moveBlue(child.pacman_pos, child.pacman_dir, child.red_ghost_pos, child.red_ghost_dir, curr_blue_ghost_pos, curr_blue_ghost_dir);
            child.orange_ghost_pos, child.orange_ghost_dir = Ghost::moveOrange(curr_orange_ghost_pos, curr_orange_ghost_dir);
            child.pink_ghost_pos, child.pink_ghost_dir = Ghost::movePink(child.pacman_pos, child.pacman_dir, curr_pink_ghost_pos, curr_pink_ghost_dir);

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

    for (auto n : final_positions) { // node_to_parent
        BaseNode curr = n; // n.first
        
        if (curr.depth == length && curr.points > best_node.points) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += ((red_distance + blue_distance + orange_distance + pink_distance) / 4);

            map<string, vector<pair<int, int>>> cherry_and_pellet = bfsCherry(true, curr.pacman_pos, curr.grid);

            curr.points += (30 / cherry_and_pellet["cherry"].size()) + (50 / cherry_and_pellet["pellet"].size());
            
            if (curr.points > best_node.points) best_node = curr;
        }
    }

    BaseNode filler = best_node;

    updatePacmanDir(filler.pacman_dir); // or we can get this from robomodules

    vector<pair<int, int>> path;

    while (!baseNodeEquals(filler, nil)) {
        path.insert(path.begin(), filler.pacman_pos);
        filler = node_to_parent[filler];
    }

    return path;

}

// Don't hit the power up and cherry
vector<pair<int, int>> StateSpaceSearchR::getNeighborsCherryOne(pair<int, int> pos, vector<vector<int>> grid) {
    vector<pair<int, int>> neighbors;
    neighbors.push_back(make_pair(pos.first - 1, pos.second)); // left
    neighbors.push_back(make_pair(pos.first, pos.second - 1)); // down
    neighbors.push_back(make_pair(pos.first + 1, pos.second)); // right
    neighbors.push_back(make_pair(pos.first, pos.second + 1)); // up
    neighbors.push_back(make_pair(pos.first, pos.second)); // Itself

    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[i];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || y > 27 || y < 0 || y > 30 
            || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n 
            || grid[x][y] == O || (x == 13 && y == 13)) neighbors.erase(neighbors.begin() + i); 
        else i++;
    }

    return neighbors;
}

////////////////////////////////////////////////////////////// CHERRY TWO //////////////////////////////////////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathCherryTwo(int length) {

    /*
    - Distance to ghost (maximize) (euclidean)
    - Distance to cherry (minimize) (BFS / A*)
    */

    map<BaseNode, BaseNode> node_to_parent;

   vector<BaseNode&> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<BaseNode> queue;

   BaseNode nil; // represents null

   BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = Ghost::getRedGhostPos();
    parent.red_ghost_dir = Ghost::getRedGhostDir();
    parent.blue_ghost_pos = Ghost::getBlueGhostPos();
    parent.blue_ghost_dir = Ghost::getBlueGhostDir();
    parent.orange_ghost_pos = Ghost::getOrangeGhostPos();
    parent.orange_ghost_dir = Ghost::getOrangeGhostDir();
    parent.pink_ghost_pos = Ghost::getPinkGhostPos();
    parent.pink_ghost_dir = Ghost::getPinkGhostDir();

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
        Ghost::Direction curr_red_ghost_dir = curr.red_ghost_dir;
        pair<int, int> curr_blue_ghost_pos = curr.blue_ghost_pos;
        Ghost::Direction curr_blue_ghost_dir = curr.blue_ghost_dir;
        pair<int, int> curr_orange_ghost_pos = curr.orange_ghost_pos;
        Ghost::Direction curr_orange_ghost_dir = curr.orange_ghost_dir;
        pair<int, int> curr_pink_ghost_pos = curr.pink_ghost_pos;
        Ghost::Direction curr_pink_ghost_dir = curr.pink_ghost_dir;

        vector<vector<int>> curr_grid = curr.grid;
        int curr_points = curr.points;
        int curr_depth = curr.depth;

        vector<pair<int, int>> neighbors = getNeighborsBase(curr_position, curr_grid); // Base works fine for cherry two

        for (auto neighbor : neighbors) {
            BaseNode child;
            child.pacman_pos = neighbor;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            child.red_ghost_pos, child.red_ghost_dir = Ghost::moveRed(child.pacman_pos, child.pacman_dir, curr_red_ghost_pos, curr_red_ghost_dir);
            child.blue_ghost_pos, child.blue_ghost_dir = Ghost::moveBlue(child.pacman_pos, child.pacman_dir, child.red_ghost_pos, child.red_ghost_dir, curr_blue_ghost_pos, curr_blue_ghost_dir);
            child.orange_ghost_pos, child.orange_ghost_dir = Ghost::moveOrange(curr_orange_ghost_pos, curr_orange_ghost_dir);
            child.pink_ghost_pos, child.pink_ghost_dir = Ghost::movePink(child.pacman_pos, child.pacman_dir, curr_pink_ghost_pos, curr_pink_ghost_dir);

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            if (child.pacman_pos.first == 13 && child.pacman_pos.second == 13) {

                setCurrCherriesEaten(getCurrCherriesEaten() + 1);

                updatePacmanDir(child.pacman_dir); // or we can get this from robomodules

                vector<pair<int, int>> path;

                while (!baseNodeEquals(child, nil)) {
                    path.insert(path.begin(), child.pacman_pos);
                    child = node_to_parent[child];
                }

                return path;

            }
            
            // DONT NEED
            // if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            // else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector

            
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

    for (auto n : final_positions) { // node_to_parent
        BaseNode curr = n; // n.first
        
        if (curr.depth == length && curr.points > best_node.points) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += ((red_distance + blue_distance + orange_distance + pink_distance) / 4);

            map<string, vector<pair<int, int>>> cherry_and_pellet = bfsCherry(false, curr.pacman_pos, curr.grid);

            curr.points += (50 / cherry_and_pellet["cherry"].size());
            
            if (curr.points > best_node.points) best_node = curr;
        }
    }

    BaseNode filler = best_node;

    updatePacmanDir(filler.pacman_dir); // or we can get this from robomodules

    vector<pair<int, int>> path;

    while (!baseNodeEquals(filler, nil)) {
        path.insert(path.begin(), filler.pacman_pos);
        filler = node_to_parent[filler];
    }

    return path;

}

////////////////////////////////////////////////////////////// POWER UP //////////////////////////////////////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathPowerUp(int length) {
    /*
    - Distance to ghost (maximize) (euclidean)
    - Distance to power up (minimize) (BFS / A*)
    - pellet collection

    if we hit power up, add it to map, but not to queue, but put a special condition on it.
    */

    map<BaseNode, BaseNode> node_to_parent;

   vector<BaseNode&> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<BaseNode> queue;

   BaseNode nil; // represents null

   BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = Ghost::getRedGhostPos();
    parent.red_ghost_dir = Ghost::getRedGhostDir();
    parent.blue_ghost_pos = Ghost::getBlueGhostPos();
    parent.blue_ghost_dir = Ghost::getBlueGhostDir();
    parent.orange_ghost_pos = Ghost::getOrangeGhostPos();
    parent.orange_ghost_dir = Ghost::getOrangeGhostDir();
    parent.pink_ghost_pos = Ghost::getPinkGhostPos();
    parent.pink_ghost_dir = Ghost::getPinkGhostDir();

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
        Ghost::Direction curr_red_ghost_dir = curr.red_ghost_dir;
        pair<int, int> curr_blue_ghost_pos = curr.blue_ghost_pos;
        Ghost::Direction curr_blue_ghost_dir = curr.blue_ghost_dir;
        pair<int, int> curr_orange_ghost_pos = curr.orange_ghost_pos;
        Ghost::Direction curr_orange_ghost_dir = curr.orange_ghost_dir;
        pair<int, int> curr_pink_ghost_pos = curr.pink_ghost_pos;
        Ghost::Direction curr_pink_ghost_dir = curr.pink_ghost_dir;

        vector<vector<int>> curr_grid = curr.grid;
        int curr_points = curr.points;
        int curr_depth = curr.depth;

        vector<pair<int, int>> neighbors = getNeighborsPowerUp(curr_position, curr_grid);

        for (auto neighbor : neighbors) {
            BaseNode child;
            child.pacman_pos = neighbor;

            // child.grid = changeGrid(curr_grid, curr_position, neighbor); ------- Placed after if statement

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            child.red_ghost_pos, child.red_ghost_dir = Ghost::moveRed(child.pacman_pos, child.pacman_dir, curr_red_ghost_pos, curr_red_ghost_dir);
            child.blue_ghost_pos, child.blue_ghost_dir = Ghost::moveBlue(child.pacman_pos, child.pacman_dir, child.red_ghost_pos, child.red_ghost_dir, curr_blue_ghost_pos, curr_blue_ghost_dir);
            child.orange_ghost_pos, child.orange_ghost_dir = Ghost::moveOrange(curr_orange_ghost_pos, curr_orange_ghost_dir);
            child.pink_ghost_pos, child.pink_ghost_dir = Ghost::movePink(child.pacman_pos, child.pacman_dir, curr_pink_ghost_pos, curr_pink_ghost_dir);

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            if (grid[child.pacman_pos.first][child.pacman_pos.second] == O) {

                setCurrPowerUpsEaten(getCurrPowerUpsEaten() + 1);

                child.grid = changeGrid(curr_grid, curr_position, neighbor);

                updatePacmanDir(child.pacman_dir); // or we can get this from robomodules

                vector<pair<int, int>> path;

                while (!baseNodeEquals(child, nil)) {
                    path.insert(path.begin(), child.pacman_pos);
                    child = node_to_parent[child];
                }

                return path;

            }

            child.grid = changeGrid(curr_grid, curr_position, neighbor);
            
            if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector

            
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

    for (auto n : final_positions) { // node_to_parent
        BaseNode curr = n; // n.first
        
        if (curr.depth == length && curr.points > best_node.points) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += ((red_distance + blue_distance + orange_distance + pink_distance) / 4);

            vector<pair<int, int>> nearest_powerup = bfsPathMultiple(curr.pacman_pos, ("set of powerups"), curr.grid);

            curr.points += (50 / nearest_powerup.size());
            
            if (curr.points > best_node.points) best_node = curr;
        }
    }

    BaseNode filler = best_node;

    updatePacmanDir(filler.pacman_dir); // or we can get this from robomodules

    vector<pair<int, int>> path;

    while (!baseNodeEquals(filler, nil)) {
        path.insert(path.begin(), filler.pacman_pos);
        filler = node_to_parent[filler];
    }

    return path;

}

// Can hit the power up
vector<pair<int, int>> StateSpaceSearchR::getNeighborsPowerUp(pair<int, int> pos, vector<vector<int>> grid) {
    vector<pair<int, int>> neighbors;
    neighbors.push_back(make_pair(pos.first - 1, pos.second)); // left
    neighbors.push_back(make_pair(pos.first, pos.second - 1)); // down
    neighbors.push_back(make_pair(pos.first + 1, pos.second)); // right
    neighbors.push_back(make_pair(pos.first, pos.second + 1)); // up
    neighbors.push_back(make_pair(pos.first, pos.second)); // Itself

    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[i];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || y > 27 || y < 0 || y > 30 
            || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n) neighbors.erase(neighbors.begin() + i); 
        else i++;
    }

    return neighbors;
}

////////////////////////////////////////////////////////////// FREIGHTENED //////////////////////////////////////////////////////////////


vector<pair<int, int>> StateSpaceSearchR::generatePathFreightened(int length) {
    /*
    - Distance to frieghtened ghost (minimize) (BFS / A*) 
    - Distance to normal ghost (maximize) (average)
    */

   map<FreightenedNode, FreightenedNode> node_to_parent;

   vector<FreightenedNode> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<FreightenedNode> queue;

   FreightenedNode nil; // represents null

   FreightenedNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = Ghost::getRedGhostPos();
    parent.red_ghost_dir = Ghost::getRedGhostDir();
    parent.red_ghost_state = Ghost::getRedGhostState();

    parent.blue_ghost_pos = Ghost::getBlueGhostPos();
    parent.blue_ghost_dir = Ghost::getBlueGhostDir();
    parent.blue_ghost_state = Ghost::getBlueGhostState();

    parent.orange_ghost_pos = Ghost::getOrangeGhostPos();
    parent.orange_ghost_dir = Ghost::getOrangeGhostDir();
    parent.orange_ghost_state = Ghost::getOrangeGhostState();

    parent.pink_ghost_pos = Ghost::getPinkGhostPos();
    parent.pink_ghost_dir = Ghost::getPinkGhostDir();
    parent.pink_ghost_state = Ghost::getPinkGhostState();

    parent.grid = grid;
    parent.points = 0;
    parent.depth = 0;

    node_to_parent[parent] = nil;

    queue.push(parent);

    while (!queue.empty()) {
        FreightenedNode curr = queue.front();
        queue.pop();

        pair<int, int> curr_position = curr.pacman_pos;
        PacmanState::Direction curr_direction = curr.pacman_dir;

        pair<int, int> curr_red_ghost_pos = curr.red_ghost_pos;
        Ghost::Direction curr_red_ghost_dir = curr.red_ghost_dir;
        Ghost::GhostState curr_red_ghost_state = curr.red_ghost_state;

        pair<int, int> curr_blue_ghost_pos = curr.blue_ghost_pos;
        Ghost::Direction curr_blue_ghost_dir = curr.blue_ghost_dir;
        Ghost::GhostState curr_blue_ghost_state = curr.blue_ghost_state;

        pair<int, int> curr_orange_ghost_pos = curr.orange_ghost_pos;
        Ghost::Direction curr_orange_ghost_dir = curr.orange_ghost_dir;
        Ghost::GhostState curr_orange_ghost_state = curr.orange_ghost_state;
        
        pair<int, int> curr_pink_ghost_pos = curr.pink_ghost_pos;
        Ghost::Direction curr_pink_ghost_dir = curr.pink_ghost_dir;
        Ghost::GhostState curr_pink_ghost_state = curr.pink_ghost_state;

        vector<vector<int>> curr_grid = curr.grid;
        int curr_points = curr.points;
        int curr_depth = curr.depth;

        vector<pair<int, int>> neighbors = getNeighborsBase(curr_position, curr_grid); // Base works fine for freightened

        for (auto neighbor : neighbors) {
            FreightenedNode child;
            child.pacman_pos = neighbor;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if ((child.pacman_pos == child.red_ghost_pos && child.red_ghost_state != GhostState::frightened) 
                || (child.pacman_pos == child.blue_ghost_pos && child.red_ghost_state != GhostState::frightened)
                || (child.pacman_pos == child.orange_ghost_pos && child.red_ghost_state != GhostState::frightened) 
                || (child.pacman_pos == child.pink_ghost_pos && child.red_ghost_state != GhostState::frightened)) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            child.red_ghost_pos, child.red_ghost_dir = Ghost::moveRed(child.pacman_pos, child.pacman_dir, curr_red_ghost_pos, curr_red_ghost_dir);
            child.blue_ghost_pos, child.blue_ghost_dir = Ghost::moveBlue(child.pacman_pos, child.pacman_dir, child.red_ghost_pos, child.red_ghost_dir, curr_blue_ghost_pos, curr_blue_ghost_dir);
            child.orange_ghost_pos, child.orange_ghost_dir = Ghost::moveOrange(curr_orange_ghost_pos, curr_orange_ghost_dir);
            child.pink_ghost_pos, child.pink_ghost_dir = Ghost::movePink(child.pacman_pos, child.pacman_dir, curr_pink_ghost_pos, curr_pink_ghost_dir);

            if ((child.pacman_pos == child.red_ghost_pos && child.red_ghost_state != GhostState::frightened) 
                || (child.pacman_pos == child.blue_ghost_pos && child.red_ghost_state != GhostState::frightened)
                || (child.pacman_pos == child.orange_ghost_pos && child.red_ghost_state != GhostState::frightened) 
                || (child.pacman_pos == child.pink_ghost_pos && child.red_ghost_state != GhostState::frightened)) {
                child.points = -1;
                node_to_parent[child] = curr;
                continue;
            }

            if (child.pacman_pos == child.red_ghost_pos && child.red_ghost_state == GhostState::frightened) {
                child.red_ghost_state = GhostState::scatter; // I think
                child.points += 200;
            }

            if (child.pacman_pos == child.blue_ghost_pos && child.blue_ghost_state == GhostState::frightened) {
                child.blue_ghost_state = GhostState::scatter; // I think
                child.points += 200;
            }

            if (child.pacman_pos == child.orange_ghost_pos && child.orange_ghost_state == GhostState::frightened) {
                child.orange_ghost_state = GhostState::scatter; // I think
                child.points += 200;
            }

            if (child.pacman_pos == child.pink_ghost_pos && child.pink_ghost_state == GhostState::frightened) {
                child.pink_ghost_state = GhostState::scatter; // I think
                child.points += 200;
            }
            
            // DONT NEED
            // if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            // else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector

            
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

    FreightenedNode best_node;
    best_node.points = -1;

    for (auto n : final_positions) { // node_to_parent
        FreightenedNode curr = n; // n.first
        
        if (curr.depth == length && curr.points > best_node.points) {

            int non_frieghtened_ghosts = 0;

            set<pair<int, int>> freightened_ghosts;

            if (curr.red_ghost_state != GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            else freightened_ghosts.insert(curr.red_ghost_pos);

            if (curr.blue_ghost_state != GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            else freightened_ghosts.insert(curr.blue_ghost_pos);

            if (curr.orange_ghost_state != GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            else freightened_ghosts.insert(curr.orange_ghost_pos);

            if (curr.pink_ghost_state != GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);
            else freightened_ghosts.insert(curr.pink_ghost_pos);

            curr.points += (non_frieghtened_ghosts / 4);

            vector<pair<int, int>> nearest_powerup = bfsPathMultiple(curr.pacman_pos, freightened_ghosts, curr.grid);

            curr.points += (50 / nearest_powerup.size());
            
            if (curr.points > best_node.points) best_node = curr;
        }
    }

    FreightenedNode filler = best_node;

    updatePacmanDir(filler.pacman_dir); // or we can get this from robomodules

    vector<pair<int, int>> path;

    while (!freightenedNodeEquals(filler, nil)) {
        path.insert(path.begin(), filler.pacman_pos);
        filler = node_to_parent[filler];
    }

    return path;

}

bool StateSpaceSearchR::freightenedNodeEquals(FreightenedNode a, FreightenedNode b) {
    return a.pacman_pos == b.pacman_pos && a.pacman_dir == b.pacman_dir && a.red_ghost_pos == b.red_ghost_pos
        && a.blue_ghost_pos == b.blue_ghost_pos && a.orange_ghost_pos == b.orange_ghost_pos
        && a.pink_ghost_pos == b.pink_ghost_pos && a.points == b.points && a.depth == b.depth;
    // return a.grid == b.grid;
}

int StateSpaceSearchR::euclideanDistance(pair<int, int> start, pair<int, int> goal) {
    int x1 = start.first;
    int y1 = start.second;
    int x2 = goal.first;
    int y2 = goal.second;

    return (int) sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}