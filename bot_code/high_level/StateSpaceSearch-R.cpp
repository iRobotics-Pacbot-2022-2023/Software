#include "StateSpaceSearch-R.h"

// #include "BFS.h"



vector<pair<int, int>> StateSpaceSearchR::generatePath(int length) {

    cout << "The state space search says we've eaten these many pellets: " << pacman.getPelletsEaten() << endl;

    
    
    if (pacman.getGameState() == PacmanState::GameState::BASE) {
        std::cout << "state space search: base" << std::endl;
        return generatePathBase(length);
    } else if (pacman.getGameState() == PacmanState::GameState::CHERRYONE) {
        std::cout << "state space search: cherryone" << std::endl;
        return generatePathCherryOne(length);
    } else if (pacman.getGameState() == PacmanState::GameState::CHERRYTWO) {
        std::cout << "state space search: cherrytwo" << std::endl;
        return generatePathCherryTwo(length);
    } else if (pacman.getGameState() == PacmanState::GameState::POWERUP) {
        std::cout << "state space search: powerup" << std::endl;
        return generatePathPowerUp(length);
    } else if (pacman.getGameState() == PacmanState::GameState::FREIGHTENED) {
        std::cout << "state space search: freightened" << std::endl;
        return generatePathFreightened(length);
    }

    return {};
}

// ////////////////////////////////////////////////////////////// BASE //////////////////////////////////////////////////////////////

vector<pair<int, int>> StateSpaceSearchR::generatePathBase(int length) {
    /*
    - Distance to ghost (maximize) (euclidean)
    - pellet collected
    - (DO NOT COLLECT POWER UP) - 0 pts
    Only look at o & v for neighbors
    */
//    std::cout << "hello" << std::endl;
   // map<StateSpaceSearchR::BaseNode, StateSpaceSearchR::BaseNode> node_to_parent;
   std::cout << "entered base state" << std::endl;

   vector<StateSpaceSearchR::BaseNode> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<StateSpaceSearchR::BaseNode> queue;

   // StateSpaceSearchR::BaseNode nil; // represents null
   StateSpaceSearchR::BaseNode parent;
//    std::cout << getPacmanPos().first << getPacmanPos().second << std::endl;
    parent.pacman_pos = getPacmanPos();
    // std::cout << "test line 126" << std::endl;
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = red_ghost.getGhostLocation();
    // cout << "red ghost position: " << parent.red_ghost_pos.first << parent.red_ghost_pos.second << endl;
    parent.red_ghost_dir = red_ghost.getterDirection();
    parent.blue_ghost_pos = blue_ghost.getGhostLocation();
    // std::cout << "Blue ghost: " << parent.blue_ghost_pos.first << " " << parent.blue_ghost_pos.second << std::endl;
    parent.blue_ghost_dir = blue_ghost.getterDirection();
    parent.orange_ghost_pos = orange_ghost.getGhostLocation();
    // std::cout << "Orange ghost: " << parent.orange_ghost_pos.first << " " << parent.orange_ghost_pos.second << std::endl;
    parent.orange_ghost_dir = orange_ghost.getterDirection();
    parent.pink_ghost_pos = pink_ghost.getGhostLocation();
    // std::cout << "Pink ghost: " << parent.pink_ghost_pos.first << " " << parent.pink_ghost_pos.second << std::endl;
    parent.pink_ghost_dir = pink_ghost.getterDirection();

    parent.grid = grid;
    parent.points = 0;
    parent.depth = 0;
    // node_to_parent[parent] = nil;

    // node_to_parent.insert(make_pair<StateSpaceSearchR::BaseNode, StateSpaceSearchR::BaseNode>(parent, nil));
    // node_to_parent.insert(std::pair<StateSpaceSearchR::BaseNode, StateSpaceSearchR::BaseNode>(parent, nil));
    queue.push(parent);

    while (!queue.empty()) {

        StateSpaceSearchR::BaseNode curr = queue.front();
        // std::cout << "Current position is: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << std::endl;
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

        Ghost red(curr_red_ghost_pos, curr_red_ghost_dir, Ghost::Color::red, red_ghost.getGhostState()); // location, direction, color, state
        Ghost blue(curr_blue_ghost_pos, curr_blue_ghost_dir, Ghost::Color::blue, blue_ghost.getGhostState());
        Ghost orange(curr_orange_ghost_pos, curr_orange_ghost_dir, Ghost::Color::orange, orange_ghost.getGhostState());
        Ghost pink(curr_pink_ghost_pos, curr_pink_ghost_dir, Ghost::Color::pink, pink_ghost.getGhostState());

    //     // if depth = length dont add to queue

        for (pair<int, int> neighbor : neighbors) {
            // p, v, o
            // std::cout << "neighbor position is: " << neighbor.first << " " << neighbor.second << std::endl;
            StateSpaceSearchR::BaseNode child;
            child.pacman_pos = neighbor;
            

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

    //         // if one of the ghost positions is equal to the neighbor position, dont add to queue and set points to -1 or something

    //         // BEFORE MOVE SO CURR
            if (child.pacman_pos == curr.red_ghost_pos || child.pacman_pos == curr.blue_ghost_pos
                || child.pacman_pos == curr.orange_ghost_pos || child.pacman_pos == curr.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }

            pair<pair<int, int>, Ghost::Direction> red_neighbor = red._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> blue_neighbor = blue._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> orange_neighbor = orange._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> pink_neighbor = pink._get_next_state_move(child.pacman_pos, child.pacman_dir, red);

            child.red_ghost_pos = red_neighbor.first;
            child.red_ghost_dir = red_neighbor.second;
            child.blue_ghost_pos = blue_neighbor.first;
            child.blue_ghost_dir = blue_neighbor.second;
            child.orange_ghost_pos = orange_neighbor.first;
            child.orange_ghost_dir = orange_neighbor.second;
            child.pink_ghost_pos = pink_neighbor.first;
            child.pink_ghost_dir = pink_neighbor.second;

    //         // OR we could add these ghost positions to a std::set and just check
    //         // if we have pacman_pos in the set or not

    //         // if one of the ghost positions is equal to the neighbor position, dont add to queue and set points to -1 or something

    //         // DOUBLE CHECK - AFTER MOVE SO CHILD
            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }
            
            if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            else child.points = curr_points;
            // std::cout << "Curr Depth: " << curr_depth << std::endl;
            child.depth = curr_depth + 1;

    //         // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
    //         // if depth < length add to queue and node_to_parent map but not final_positions vector
            // std::cout << "The parent is at: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << "Child at: " << child.pacman_pos.first << " " << child.pacman_pos.second << 
            // "Depth: " << child.depth << std::endl;
            
            if (child.depth == length) {
                // node_to_parent[child] = curr;
                final_positions.push_back(child);
            } else if (child.depth < length) {
                // std::cout << "depth is less than length" << std::endl;
                queue.push(child);
                // node_to_parent[child] = curr;
            }
        }
    }

    /* Figure out and calculate the ghost positions for all the final positions*/
    // for all the basenodes of depth = length, calculate the ghost positions and recalulate score
    StateSpaceSearchR::BaseNode best_node;
    best_node.points = -1;

    for (auto n : final_positions) { // node_to_parent
        StateSpaceSearchR::BaseNode curr = n; // n.first
        // std::cout << "you have entered final_positions" << std::endl;
        if (curr.depth == length) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += (int) (.05 * (double) (red_distance + blue_distance + orange_distance + pink_distance));
            // std::cout << "Current node points: " << curr.points << std::endl;
            if (curr.points > best_node.points) {
                best_node.points = curr.points;
                best_node = curr;
            }

        }
    }

    // StateSpaceSearchR::BaseNode filler = best_node;
    // std::cout << "Best points is: " << filler.points << std::endl;
    // std::cout << "Final Location: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;

    updatePacmanDir(best_node.pacman_dir); // or we can get this from robomodules
    std::cout << final_positions.size() << std::endl;
    std::pair<int, int> start = std::pair<int, int>(parent.pacman_pos.first, parent.pacman_pos.second);
    vector<pair<int, int>> path = bfsPathSingle(start, best_node.pacman_pos, grid);
    cout << "PATH LENGTH: " << path.size() << endl;
    // filler = node_to_parent[filler];
    // std::cout << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;

    // for (auto & [key, value] : node_to_parent) {
    //     std::cout << "Key: " << key.pacman_pos.first << " " << key.pacman_pos.second << ", Value: " << value.pacman_pos.first << " " << value.pacman_pos.second << std::endl;
    // }

    // auto it = node_to_parent.find(filler);
    // if (it == node_to_parent.end()) {
    //     std::cout << "You reached the end and this sucks" << std::endl;
    // }
    // std::cout << parent.pacman_pos.first << " " << parent.pacman_pos.second;
    
    // while (!baseNodeEquals(filler, nil)) {
    //     path.insert(path.begin(), filler.pacman_pos);
    //     std::cout << "The child node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl; 
    //     filler = node_to_parent[filler];
    //     std::cout << "The parent node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    // }
    // for (size_t i = 0; i < path.size(); ++i) {
    //     std::cout << path.at(i).first << " " << path.at(i).second << std::endl;
    // }
    return path;

    /*
    BaseNode child = best_node;

    updatePacmanDir(child.pacman_dir); // or we can get this from robomodules

    vector<pair<int, int>> path;

    vector<char> directions;



    while (!baseNodeEquals(node_to_parent[child],nil)) { // !baseNodeEquals(child, nil)

        BaseNode parent_loop = node_to_parent[child];
        
        int x_diff = parent_loop.pacman_pos.first - child.pacman_pos.first; // parent x = 5, child x = 4, x_dff = 1, go right
        int y_diff = parent_loop.pacman_pos.second - child.pacman_pos.second; // parent y = 5, child y = 4, y_dff = 1, go up

        if (x_diff == 1) directions.insert(directions.begin(), 'e');
        else if (x_diff == -1) directions.insert(directions.begin(), 'w');
        else if (y_diff == 1) directions.insert(directions.begin(), 'n');
        else if (y_diff == -1) directions.insert(directions.begin(), 's');
        else directions.insert(directions.begin(), '!');

        // path.insert(path.begin(), child.pacman_pos);
        child = parent_loop;
    }

    return path;
    */

}

bool StateSpaceSearchR::baseNodeEquals(StateSpaceSearchR::BaseNode a, StateSpaceSearchR::BaseNode b) {
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
        if (x < 0 || x > 27 || y < 0 || y > 30 
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

   // map<StateSpaceSearchR::BaseNode, StateSpaceSearchR::BaseNode> node_to_parent;

   vector<StateSpaceSearchR::BaseNode> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<StateSpaceSearchR::BaseNode> queue;

   StateSpaceSearchR::BaseNode nil; // represents null

   StateSpaceSearchR::BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = red_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.red_ghost_pos.first << " " << parent.red_ghost_pos.second << std::endl;
    parent.red_ghost_dir = red_ghost.getterDirection();
    parent.blue_ghost_pos = blue_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.blue_ghost_pos.first << " " << parent.blue_ghost_pos.second << std::endl;
    parent.blue_ghost_dir = blue_ghost.getterDirection();
    parent.orange_ghost_pos = orange_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.orange_ghost_pos.first << " " << parent.orange_ghost_pos.second << std::endl;
    parent.orange_ghost_dir = orange_ghost.getterDirection();
    parent.pink_ghost_pos = pink_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.pink_ghost_pos.first << " " << parent.pink_ghost_pos.second << std::endl;
    parent.pink_ghost_dir = pink_ghost.getterDirection();

    parent.grid = grid;
    parent.points = 0;
    parent.depth = 0;

    // node_to_parent[parent] = nil;

    queue.push(parent);

    while (!queue.empty()) {
        StateSpaceSearchR::BaseNode curr = queue.front();
        // std::cout << "Current position is: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << std::endl;
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

        Ghost red(curr_red_ghost_pos, curr_red_ghost_dir, Ghost::Color::red, red_ghost.getGhostState()); // location, direction, color, state
        Ghost blue(curr_blue_ghost_pos, curr_blue_ghost_dir, Ghost::Color::blue, blue_ghost.getGhostState());
        Ghost orange(curr_orange_ghost_pos, curr_orange_ghost_dir, Ghost::Color::orange, orange_ghost.getGhostState());
        Ghost pink(curr_pink_ghost_pos, curr_pink_ghost_dir, Ghost::Color::pink, pink_ghost.getGhostState());

        for (auto neighbor : neighbors) {
            // std::cout << "neighbor position is: " << neighbor.first << " " << neighbor.second << std::endl;
            StateSpaceSearchR::BaseNode child;
            child.pacman_pos = neighbor;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if (child.pacman_pos == curr.red_ghost_pos || child.pacman_pos == curr.blue_ghost_pos
                || child.pacman_pos == curr.orange_ghost_pos || child.pacman_pos == curr.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }

            pair<pair<int, int>, Ghost::Direction> red_neighbor = red._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> blue_neighbor = blue._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> orange_neighbor = orange._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> pink_neighbor = pink._get_next_state_move(child.pacman_pos, child.pacman_dir, red);

            child.red_ghost_pos = red_neighbor.first;
            child.red_ghost_dir = red_neighbor.second;
            child.blue_ghost_pos = blue_neighbor.first;
            child.blue_ghost_dir = blue_neighbor.second;
            child.orange_ghost_pos = orange_neighbor.first;
            child.orange_ghost_dir = orange_neighbor.second;
            child.pink_ghost_pos = pink_neighbor.first;
            child.pink_ghost_dir = pink_neighbor.second;

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }
            
            if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector
            // std::cout << "The parent is at: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << "Child at: " << child.pacman_pos.first << " " << child.pacman_pos.second << 
            // "Depth: " << child.depth << std::endl;
            
            if (child.depth == length) {
                // node_to_parent[child] = curr;
                final_positions.push_back(child);
            } else if (child.depth < length) {
                queue.push(child);
                // node_to_parent[child] = curr;
            }
        }
    }

    /* Figure out and calculate the ghost positions for all the final positions*/
    // for all the basenodes of depth = length, calculate the ghost positions and recalulate score

    StateSpaceSearchR::BaseNode best_node;
    best_node.points = -1;

    for (auto n : final_positions) { // node_to_parent
        StateSpaceSearchR::BaseNode curr = n; // n.first
        
        if (curr.depth == length && curr.points > best_node.points) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += ((red_distance + blue_distance + orange_distance + pink_distance) / 4);
            // std::cout << "Current node points before cherry calculation: " << curr.points << std::endl;

            map<string, vector<pair<int, int>>> cherry_and_pellet = bfsCherry(true, curr.pacman_pos, curr.grid);

            curr.points += (30 / cherry_and_pellet["cherry"].size()) + (50 / cherry_and_pellet["pellet"].size());
            // std::cout << "Current node points after cherry calculation: " << curr.points << std::endl;
            
            if (curr.points > best_node.points) {
                best_node.points = curr.points;
                best_node = curr;
            }
        }
    }
    

    updatePacmanDir(best_node.pacman_dir); // or we can get this from robomodules
    std::cout << final_positions.size() << std::endl;
    std::pair<int, int> start = std::pair<int, int>(parent.pacman_pos.first, parent.pacman_pos.second);
    vector<pair<int, int>> path = bfsPathSingle(start, best_node.pacman_pos, grid);
    cout << "PATH LENGTH: " << path.size() << endl;

    // while (!baseNodeEquals(filler, nil)) {
    //     // std::cout << "The child node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    //     path.insert(path.begin(), filler.pacman_pos);
    //     filler = node_to_parent[filler];
    //     // std::cout << "The parent node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    // }

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
        if (x < 0 || x > 27 || y < 0 || y > 30 
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

    // map<StateSpaceSearchR::BaseNode, StateSpaceSearchR::BaseNode> node_to_parent;

   vector<StateSpaceSearchR::BaseNode> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<StateSpaceSearchR::BaseNode> queue;

   StateSpaceSearchR::BaseNode nil; // represents null

   StateSpaceSearchR::BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();
    if (parent.pacman_pos.first == 13 && parent.pacman_pos.second == 13) {
        std::cout << "CHANGE TO BASE" << std::endl;
        pacman.setGameState(PacmanState::GameState::BASE);
        return generatePathBase(length);
    }
    // std::cout << "test" << std::endl;
    parent.red_ghost_pos = red_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.red_ghost_pos.first << " " << parent.red_ghost_pos.second << std::endl;
    parent.red_ghost_dir = red_ghost.getterDirection();
    parent.blue_ghost_pos = blue_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.blue_ghost_pos.first << " " << parent.blue_ghost_pos.second << std::endl;
    parent.blue_ghost_dir = blue_ghost.getterDirection();
    parent.orange_ghost_pos = orange_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.orange_ghost_pos.first << " " << parent.orange_ghost_pos.second << std::endl;
    parent.orange_ghost_dir = orange_ghost.getterDirection();
    parent.pink_ghost_pos = pink_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.pink_ghost_pos.first << " " << parent.pink_ghost_pos.second << std::endl;
    parent.pink_ghost_dir = pink_ghost.getterDirection();

    parent.grid = grid;
    parent.points = 0;
    parent.depth = 0;

    // node_to_parent[parent] = nil;

    queue.push(parent);

    while (!queue.empty()) {
        StateSpaceSearchR::BaseNode curr = queue.front();
        // std::cout << "Current position is: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << std::endl;
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

        Ghost red(curr_red_ghost_pos, curr_red_ghost_dir, Ghost::Color::red, red_ghost.getGhostState()); // location, direction, color, state
        Ghost blue(curr_blue_ghost_pos, curr_blue_ghost_dir, Ghost::Color::blue, blue_ghost.getGhostState());
        Ghost orange(curr_orange_ghost_pos, curr_orange_ghost_dir, Ghost::Color::orange, orange_ghost.getGhostState());
        Ghost pink(curr_pink_ghost_pos, curr_pink_ghost_dir, Ghost::Color::pink, pink_ghost.getGhostState());

        for (auto neighbor : neighbors) {
            // std::cout << "neighbor position is: " << neighbor.first << " " << neighbor.second << std::endl;
            StateSpaceSearchR::BaseNode child;
            child.pacman_pos = neighbor;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if (child.pacman_pos == curr.red_ghost_pos || child.pacman_pos == curr.blue_ghost_pos
                || child.pacman_pos == curr.orange_ghost_pos || child.pacman_pos == curr.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }

            pair<pair<int, int>, Ghost::Direction> red_neighbor = red._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> blue_neighbor = blue._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> orange_neighbor = orange._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> pink_neighbor = pink._get_next_state_move(child.pacman_pos, child.pacman_dir, red);

            child.red_ghost_pos = red_neighbor.first;
            child.red_ghost_dir = red_neighbor.second;
            child.blue_ghost_pos = blue_neighbor.first;
            child.blue_ghost_dir = blue_neighbor.second;
            child.orange_ghost_pos = orange_neighbor.first;
            child.orange_ghost_dir = orange_neighbor.second;
            child.pink_ghost_pos = pink_neighbor.first;
            child.pink_ghost_dir = pink_neighbor.second;

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }

            if (child.pacman_pos.first == 13 && child.pacman_pos.second == 13) {

                // curr_cherries_eaten++;
                // pacman.setCherriesEaten(curr_cherries_eaten);
                // setCurrCherriesEaten(getCurrCherriesEaten() + 1);
                // std::cout << "You have reached the cherry! " << "Cherries: " << curr_cherries_eaten << std::endl; 
                updatePacmanDir(child.pacman_dir); // or we can get this from robomodules


                std::pair<int, int> start = std::pair<int, int>(parent.pacman_pos.first, parent.pacman_pos.second);
                std::pair<int, int> goal = std::pair<int, int>(child.pacman_pos.first, child.pacman_pos.second);
                vector<pair<int, int>> path = bfsPathSingle(start, goal, grid);

                // while (!baseNodeEquals(child, nil)) {
                //     // std::cout << "CherryPath: " << child.pacman_pos.first << " " << child.pacman_pos.second << std::endl;
                //     path.insert(path.begin(), child.pacman_pos);
                //     child = node_to_parent[child];
                // }

                return path;

            }
            
            // DONT NEED
            // if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            // else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector

            // std::cout << "The parent is at: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << "Child at: " << child.pacman_pos.first << " " << child.pacman_pos.second << 
            // "Depth: " << child.depth << std::endl;

            if (child.depth == length) {
                // node_to_parent[child] = curr;
                final_positions.push_back(child);
            } else if (child.depth < length) {
                queue.push(child);
                // node_to_parent[child] = curr;
            }
        }
    
    }

    /* Figure out and calculate the ghost positions for all the final positions*/
    // for all the basenodes of depth = length, calculate the ghost positions and recalulate score

    StateSpaceSearchR::BaseNode best_node;
    best_node.points = -1;
    std::cout << final_positions.size() << std::endl;
    for (auto n : final_positions) { // node_to_parent
        StateSpaceSearchR::BaseNode curr = n; // n.first
        
        if (curr.depth == length && curr.points > best_node.points) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += ((red_distance + blue_distance + orange_distance + pink_distance) / 4);
            // std::cout << "Current node points before cherry calculation: " << curr.points << std::endl;

            map<string, vector<pair<int, int>>> cherry_and_pellet = bfsCherry(false, curr.pacman_pos, curr.grid);

            curr.points += (50 / cherry_and_pellet["cherry"].size());
            // std::cout << "Current node points after cherry calculation: " << curr.points << std::endl;
            
            if (curr.points > best_node.points) {
                best_node.points = curr.points;
                best_node = curr;
            }
        }
    }

    updatePacmanDir(best_node.pacman_dir); // or we can get this from robomodules
    std::cout << final_positions.size() << std::endl;
    std::pair<int, int> start = std::pair<int, int>(parent.pacman_pos.first, parent.pacman_pos.second);
    vector<pair<int, int>> path = bfsPathSingle(start, best_node.pacman_pos, grid);
    cout << "PATH LENGTH: " << path.size() << endl;

    // StateSpaceSearchR::BaseNode filler = best_node;
    // // std::cout << "Best points is: " << filler.points << std::endl;

    // updatePacmanDir(filler.pacman_dir); // or we can get this from robomodules

    // vector<pair<int, int>> path;

    // while (!baseNodeEquals(filler, nil)) {
    //     // std::cout << "The child node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    //     path.insert(path.begin(), filler.pacman_pos);
    //     filler = node_to_parent[filler];
    //     // std::cout << "The parent node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    // }

    // pacman.setCherryTimeLeft(pacman.getCherryTimeLeft() - (length / 2));

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

    // map<StateSpaceSearchR::BaseNode, StateSpaceSearchR::BaseNode> node_to_parent;

    cout << "in the power up function" << endl;

   vector<StateSpaceSearchR::BaseNode> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<StateSpaceSearchR::BaseNode> queue;

   // StateSpaceSearchR::BaseNode nil; // represents null

   StateSpaceSearchR::BaseNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();
    if (grid[parent.pacman_pos.first][parent.pacman_pos.second] == O) {

        // POWER_POINTS_LOCATIONS.erase(POWER_POINTS_LOCATIONS.find({parent.pacman_pos.first, parent.pacman_pos.first}));
        // std::cout << "bruh" << std::endl;
        std::cout << "CHANGE TO BASE" << std::endl;
        pacman.setGameState(PacmanState::GameState::FREIGHTENED);
        pacman.setFrieghtenedTimeLeft(30);
        // updateFreightenedTimeLeft(30); // idk the time for the freightened state
        red_ghost.setGhostState(Ghost::GhostState::frightened);
        blue_ghost.setGhostState(Ghost::GhostState::frightened);
        orange_ghost.setGhostState(Ghost::GhostState::frightened);
        pink_ghost.setGhostState(Ghost::GhostState::frightened);
        // state = StateSpaceSearchR::FREIGHTENED;
        return generatePathFreightened(length);
    }

    parent.red_ghost_pos = red_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.red_ghost_pos.first << " " << parent.red_ghost_pos.second << std::endl;
    parent.red_ghost_dir = red_ghost.getterDirection();
    parent.blue_ghost_pos = blue_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.blue_ghost_pos.first << " " << parent.blue_ghost_pos.second << std::endl;
    parent.blue_ghost_dir = blue_ghost.getterDirection();
    parent.orange_ghost_pos = orange_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.orange_ghost_pos.first << " " << parent.orange_ghost_pos.second << std::endl;
    parent.orange_ghost_dir = orange_ghost.getterDirection();
    parent.pink_ghost_pos = pink_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.pink_ghost_pos.first << " " << parent.pink_ghost_pos.second << std::endl;
    parent.pink_ghost_dir = pink_ghost.getterDirection();

    parent.grid = grid;
    parent.points = 0;
    parent.depth = 0;

    // node_to_parent[parent] = nil;

    queue.push(parent);

    // cout << "about to enter while loop" << endl;

    // int i = 0;
    while (!queue.empty()) {
        // cout << "i: " << i << endl;
        StateSpaceSearchR::BaseNode curr = queue.front();
        // std::cout << "Current position is: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << std::endl;
        queue.pop();

        pair<int, int> curr_position = curr.pacman_pos;
        // cout << "Parent coordinate: " << curr_position.first << " " << curr_position.second << endl;
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
        
        // Ghost red(curr_red_ghost_pos, curr_red_ghost_dir, Ghost::Color::red, red_ghost_state); // location, direction, color, state
        // if (red.getGhostState() == Ghost::GhostState::chase) {
        //         std::cout << "ghost frightened" << std::endl;
        //     }
        Ghost red(curr_red_ghost_pos, curr_red_ghost_dir, Ghost::Color::red, red_ghost.getGhostState()); // location, direction, color, state
        Ghost blue(curr_blue_ghost_pos, curr_blue_ghost_dir, Ghost::Color::blue, blue_ghost.getGhostState());
        Ghost orange(curr_orange_ghost_pos, curr_orange_ghost_dir, Ghost::Color::orange, orange_ghost.getGhostState());
        Ghost pink(curr_pink_ghost_pos, curr_pink_ghost_dir, Ghost::Color::pink, pink_ghost.getGhostState());


        for (auto neighbor : neighbors) {
            StateSpaceSearchR::BaseNode child;
            // std::cout << "neighbor position is: " << neighbor.first << " " << neighbor.second << std::endl;
            child.pacman_pos = neighbor;

            // cout << "Child coordinate: " << child.pacman_pos.first << " " << child.pacman_pos.second << endl;

            // child.grid = changeGrid(curr_grid, curr_position, neighbor); ------- Placed after if statement

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if (child.pacman_pos == curr.red_ghost_pos || child.pacman_pos == curr.blue_ghost_pos
                || child.pacman_pos == curr.orange_ghost_pos || child.pacman_pos == curr.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }

            // if (child.pacman_pos.first == 0 && child.pacman_pos.second == 16) cout << "reached line 919" << endl;
            // cout << "red ghost position: " << red.getGhostLocation().first << " " << red.getGhostLocation().second << endl;
            // if (red.getGhostState() == Ghost::GhostState::fr) {
            //     std::cout << "ghost chase" << std::endl;
            // }

            pair<pair<int, int>, Ghost::Direction> red_neighbor = red._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            // cout << "red" << endl;
            pair<pair<int, int>, Ghost::Direction> blue_neighbor = blue._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            // cout << "blue" << endl;
            pair<pair<int, int>, Ghost::Direction> orange_neighbor = orange._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            // cout << "orange" << endl;
            pair<pair<int, int>, Ghost::Direction> pink_neighbor = pink._get_next_state_move(child.pacman_pos, child.pacman_dir, red);

            // if (child.pacman_pos.first == 0 && child.pacman_pos.second == 16) cout << "reached line 926" << endl;

            child.red_ghost_pos = red_neighbor.first;
            child.red_ghost_dir = red_neighbor.second;
            child.blue_ghost_pos = blue_neighbor.first;
            child.blue_ghost_dir = blue_neighbor.second;
            child.orange_ghost_pos = orange_neighbor.first;
            child.orange_ghost_dir = orange_neighbor.second;
            child.pink_ghost_pos = pink_neighbor.first;
            child.pink_ghost_dir = pink_neighbor.second;

            // if (child.pacman_pos.first == 0 && child.pacman_pos.second == 16) cout << "reached line 935" << endl;

            if (child.pacman_pos == child.red_ghost_pos || child.pacman_pos == child.blue_ghost_pos
                || child.pacman_pos == child.orange_ghost_pos || child.pacman_pos == child.pink_ghost_pos) {
                child.points = -1;
                // node_to_parent[child] = curr;
                // cout << "we hit a ghost - second check" << endl;
                continue;
            }

            // if (child.pacman_pos.first == 0 && child.pacman_pos.second == 16) cout << "reached line 945" << endl;

            if (grid[child.pacman_pos.first][child.pacman_pos.second] == O) {
                std::cout << "O reached" << std::endl;
                // pacman.setPowerupsEaten(curr_powerups_eaten); //maybe not needed
                // POWER_POINTS_LOCATIONS.erase(child.pacman_pos);
                // std::cout << "You have reached the powerup! " << "Powerups: " << curr_powerups_eaten << std::endl;
                child.grid = changeGrid(curr_grid, curr_position, neighbor);

                updatePacmanDir(child.pacman_dir); // or we can get this from robomodules

                std::pair<int, int> start = std::pair<int, int>(parent.pacman_pos.first, parent.pacman_pos.second);
                std::pair<int, int> goal = std::pair<int, int>(child.pacman_pos.first, child.pacman_pos.second);
                vector<pair<int, int>> path = bfsPathSingle(start, goal, grid);



                // while (!baseNodeEquals(child, nil)) {
                //     // std::cout << "PowerupPath: " << child.pacman_pos.first << " " << child.pacman_pos.second << std::endl;
                //     path.insert(path.begin(), child.pacman_pos);
                //     child = node_to_parent[child];
                // }
                return path;

            }

            // if (child.pacman_pos.first == 0 && child.pacman_pos.second == 16) cout << "reached line 971" << endl;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);
            
            if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector
            // std::cout << "The parent is at: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << "Child at: " << child.pacman_pos.first << " " << child.pacman_pos.second << 
            // "Depth: " << child.depth << std::endl;
            
            if (child.depth == length) {
                // node_to_parent[child] = curr;
                final_positions.push_back(child);
            } else if (child.depth < length) {
                queue.push(child);
                // node_to_parent[child] = curr;
            }
        }

        // i++;

    }

    // cout << "reached out of the while loop" << endl;

    /* Figure out and calculate the ghost positions for all the final positions*/
    // for all the basenodes of depth = length, calculate the ghost positions and recalulate score

    StateSpaceSearchR::BaseNode best_node;
    best_node.points = -1;

    for (auto n : final_positions) { // node_to_parent
        StateSpaceSearchR::BaseNode curr = n; // n.first
        
        if (curr.depth == length && curr.points > best_node.points) {
            int red_distance = euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            int blue_distance = euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            int orange_distance = euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            int pink_distance = euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);

            curr.points += ((red_distance + blue_distance + orange_distance + pink_distance) / 4);

            vector<pair<int, int>> nearest_powerup = bfsPathMultiple(curr.pacman_pos, POWER_POINTS_LOCATIONS, curr.grid);

            curr.points += (50 / nearest_powerup.size());
            
            if (curr.points > best_node.points) {
                best_node.points = curr.points;
                best_node = curr;
            }
        }
    }

    // StateSpaceSearchR::BaseNode filler = best_node;

    // std::cout << "Best points is: " << filler.points << std::endl;

    updatePacmanDir(best_node.pacman_dir); // or we can get this from robomodules

    std::pair<int, int> start = std::pair<int, int>(parent.pacman_pos.first, parent.pacman_pos.second);
    std::pair<int, int> goal = std::pair<int, int>(best_node.pacman_pos.first, best_node.pacman_pos.second);
    vector<pair<int, int>> path = bfsPathSingle(start, goal, grid);

    // while (!baseNodeEquals(filler, nil)) {
    //     // std::cout << "The child node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    //     path.insert(path.begin(), filler.pacman_pos);
    //     filler = node_to_parent[filler];
    //     // std::cout << "The parent node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    // }

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
        if (x < 0 || x > 27 || y < 0 || y > 30 
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

   cout << "Freigtened path start" << endl;

   // map<StateSpaceSearchR::FreightenedNode, StateSpaceSearchR::FreightenedNode> node_to_parent;

   vector<StateSpaceSearchR::FreightenedNode> final_positions; // or we could do a vector of final positions (pairs) (IDK if we need this)

   queue<StateSpaceSearchR::FreightenedNode> queue;

   StateSpaceSearchR::FreightenedNode nil; // represents null

   StateSpaceSearchR::FreightenedNode parent;
    parent.pacman_pos = getPacmanPos();
    parent.pacman_dir = getPacmanDir();

    parent.red_ghost_pos = red_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.red_ghost_pos.first << " " << parent.red_ghost_pos.second << std::endl;
    parent.red_ghost_dir = red_ghost.getterDirection();
    parent.red_ghost_state = red_ghost.getGhostState();
    

    parent.blue_ghost_pos = blue_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.blue_ghost_pos.first << " " << parent.blue_ghost_pos.second << std::endl;
    parent.blue_ghost_dir = blue_ghost.getterDirection();
    parent.blue_ghost_state = blue_ghost.getGhostState();
    

    parent.orange_ghost_pos = orange_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.orange_ghost_pos.first << " " << parent.orange_ghost_pos.second << std::endl;
    parent.orange_ghost_dir = orange_ghost.getterDirection();
    parent.orange_ghost_state = orange_ghost.getGhostState();
    

    parent.pink_ghost_pos = pink_ghost.getGhostLocation();
    // std::cout << "Red ghost: " << parent.pink_ghost_pos.first << " " << parent.pink_ghost_pos.second << std::endl;
    parent.pink_ghost_dir = pink_ghost.getterDirection();
    parent.pink_ghost_state = pink_ghost.getGhostState();
    
    parent.grid = grid;
    parent.points = 0;
    parent.depth = 0;

    // node_to_parent[parent] = nil;

    queue.push(parent);

    while (!queue.empty()) {
        StateSpaceSearchR::FreightenedNode curr = queue.front();
        // std::cout << "Current position is: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << std::endl;
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

        Ghost red(curr_red_ghost_pos, curr_red_ghost_dir, Ghost::Color::red, red_ghost.getGhostState()); // location, direction, color, state
        Ghost blue(curr_blue_ghost_pos, curr_blue_ghost_dir, Ghost::Color::blue, blue_ghost.getGhostState());
        Ghost orange(curr_orange_ghost_pos, curr_orange_ghost_dir, Ghost::Color::orange, orange_ghost.getGhostState());
        Ghost pink(curr_pink_ghost_pos, curr_pink_ghost_dir, Ghost::Color::pink, pink_ghost.getGhostState());

        for (auto neighbor : neighbors) {
            StateSpaceSearchR::FreightenedNode child;
            // std::cout << "neighbor position is: " << neighbor.first << " " << neighbor.second << std::endl;
            child.pacman_pos = neighbor;

            child.grid = changeGrid(curr_grid, curr_position, neighbor);

            if (child.pacman_pos == curr_position) child.pacman_dir = curr_direction;
            else if (child.pacman_pos.second == curr_position.second + 1) child.pacman_dir = PacmanState::Direction::up;
            else if (child.pacman_pos.second == curr_position.second - 1) child.pacman_dir = PacmanState::Direction::down;
            else if (child.pacman_pos.first == curr_position.first + 1) child.pacman_dir = PacmanState::Direction::right;
            else if (child.pacman_pos.first == curr_position.first - 1) child.pacman_dir = PacmanState::Direction::left;

            if ((child.pacman_pos == curr.red_ghost_pos && curr.red_ghost_state != Ghost::GhostState::frightened) 
                || (child.pacman_pos == curr.blue_ghost_pos && curr.red_ghost_state != Ghost::GhostState::frightened)
                || (child.pacman_pos == curr.orange_ghost_pos && curr.red_ghost_state != Ghost::GhostState::frightened) 
                || (child.pacman_pos == curr.pink_ghost_pos && curr.red_ghost_state != Ghost::GhostState::frightened)) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }

            if (child.pacman_pos == curr.red_ghost_pos && curr.red_ghost_state == Ghost::GhostState::frightened) {
                child.red_ghost_state = Ghost::GhostState::scatter; // I think
                child.points += 200;
            }

            if (child.pacman_pos == curr.blue_ghost_pos && curr.blue_ghost_state == Ghost::GhostState::frightened) {
                child.blue_ghost_state = Ghost::GhostState::scatter; // I think
                child.points += 200;
            }

            if (child.pacman_pos == curr.orange_ghost_pos && curr.orange_ghost_state == Ghost::GhostState::frightened) {
                child.orange_ghost_state = Ghost::GhostState::scatter; // I think
                child.points += 200;
            }

            if (child.pacman_pos == curr.pink_ghost_pos && curr.pink_ghost_state == Ghost::GhostState::frightened) {
                child.pink_ghost_state = Ghost::GhostState::scatter; // I think
                child.points += 200;
            }


            pair<pair<int, int>, Ghost::Direction> red_neighbor = red._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> blue_neighbor = blue._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> orange_neighbor = orange._get_next_state_move(child.pacman_pos, child.pacman_dir, red);
            pair<pair<int, int>, Ghost::Direction> pink_neighbor = pink._get_next_state_move(child.pacman_pos, child.pacman_dir, red);

            child.red_ghost_pos = red_neighbor.first;
            child.red_ghost_dir = red_neighbor.second;
            child.blue_ghost_pos = blue_neighbor.first;
            child.blue_ghost_dir = blue_neighbor.second;
            child.orange_ghost_pos = orange_neighbor.first;
            child.orange_ghost_dir = orange_neighbor.second;
            child.pink_ghost_pos = pink_neighbor.first;
            child.pink_ghost_dir = pink_neighbor.second;

            if ((child.pacman_pos == child.red_ghost_pos && child.red_ghost_state != Ghost::GhostState::frightened) 
                || (child.pacman_pos == child.blue_ghost_pos && child.red_ghost_state != Ghost::GhostState::frightened)
                || (child.pacman_pos == child.orange_ghost_pos && child.red_ghost_state != Ghost::GhostState::frightened) 
                || (child.pacman_pos == child.pink_ghost_pos && child.red_ghost_state != Ghost::GhostState::frightened)) {
                child.points = -1;
                // node_to_parent[child] = curr;
                continue;
            }

            if (child.pacman_pos == child.red_ghost_pos && child.red_ghost_state == Ghost::GhostState::frightened) {
                // child.red_ghost_state = Ghost::GhostState::scatter; // I think
                red_ghost.setGhostState(Ghost::GhostState::scatter);
                child.points += 200;
            }

            if (child.pacman_pos == child.blue_ghost_pos && child.blue_ghost_state == Ghost::GhostState::frightened) {
                // child.blue_ghost_state = Ghost::GhostState::scatter; // I think
                blue_ghost.setGhostState(Ghost::GhostState::scatter);
                child.points += 200;
            }

            if (child.pacman_pos == child.orange_ghost_pos && child.orange_ghost_state == Ghost::GhostState::frightened) {
                // child.orange_ghost_state = Ghost::GhostState::scatter; // I think
                orange_ghost.setGhostState(Ghost::GhostState::scatter);
                child.points += 200;
            }

            if (child.pacman_pos == child.pink_ghost_pos && child.pink_ghost_state == Ghost::GhostState::frightened) {
                // child.pink_ghost_state = Ghost::GhostState::scatter; // I think
                pink_ghost.setGhostState(Ghost::GhostState::scatter);
                child.points += 200;
            }
            
            // DONT NEED
            // if (curr_grid[neighbor.first][neighbor.second] == o) child.points = curr_points + 1;
            // else child.points = curr_points;
            
            child.depth = curr_depth + 1;

            // if depth = length, dont add to queue but add to the node_to_parent map & final_positions vector
            // if depth < length add to queue and node_to_parent map but not final_positions vector

            // std::cout << "The parent is at: " << curr.pacman_pos.first << " " << curr.pacman_pos.second << "Child at: " << child.pacman_pos.first << " " << child.pacman_pos.second << 
            // "Depth: " << child.depth << std::endl;

            if (child.depth == length) {
                // node_to_parent[child] = curr;
                final_positions.push_back(child);
            } else if (child.depth < length) {
                queue.push(child);
                // node_to_parent[child] = curr;
            }
        }
    }

    /* Figure out and calculate the ghost positions for all the final positions*/
    // for all the basenodes of depth = length, calculate the ghost positions and recalulate score

    StateSpaceSearchR::FreightenedNode best_node;
    best_node.points = -1;
    std::cout << final_positions.size() << std::endl;
    std::cout << "Parent location: " << parent.pacman_pos.first << " "<< parent.pacman_pos.second << std::endl;
    for (auto n : final_positions) { // node_to_parent
        StateSpaceSearchR::FreightenedNode curr = n; // n.first
        
        // if (curr.depth == length && curr.points > best_node.points) {
            // std::cout << "entered if statement" << std::endl;
            int non_frieghtened_ghosts = 0;

            set<pair<int, int>> freightened_ghosts;
    
            if (curr.red_ghost_state != Ghost::GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.red_ghost_pos);
            else freightened_ghosts.insert(curr.red_ghost_pos);

            if (curr.blue_ghost_state != Ghost::GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.blue_ghost_pos);
            else freightened_ghosts.insert(curr.blue_ghost_pos);

            if (curr.orange_ghost_state != Ghost::GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.orange_ghost_pos);
            else freightened_ghosts.insert(curr.orange_ghost_pos);

            if (curr.pink_ghost_state != Ghost::GhostState::frightened) non_frieghtened_ghosts += euclideanDistance(curr.pacman_pos, curr.pink_ghost_pos);
            else freightened_ghosts.insert(curr.pink_ghost_pos);

            curr.points += (non_frieghtened_ghosts / 20);

            vector<pair<int, int>> nearest_freightend_ghost = bfsPathMultiple(curr.pacman_pos, freightened_ghosts, curr.grid);

            curr.points += (50 / nearest_freightend_ghost.size());
            
            if (curr.points > best_node.points) {
                best_node.points = curr.points;
                best_node = curr;
            }
        // }
    }

    // StateSpaceSearchR::FreightenedNode filler = best_node;
    std::cout << "Best Node: " << best_node.pacman_pos.first << " " << best_node.pacman_pos.second << std::endl;

    // std::cout << "Best points is: " << filler.points << std::endl;

    updatePacmanDir(best_node.pacman_dir); // or we can get this from robomodules
    std::pair<int, int> start = std::pair<int, int>(parent.pacman_pos.first, parent.pacman_pos.second);
    vector<pair<int, int>> path = bfsPathSingle(start, best_node.pacman_pos, grid);

    // while (!freightenedNodeEquals(filler, nil)) {
    //     // std::cout << "The child node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    //     path.insert(path.begin(), filler.pacman_pos);
    //     filler = node_to_parent[filler];
    //     // std::cout << "The parent node traversed is: " << filler.pacman_pos.first << " " << filler.pacman_pos.second << std::endl;
    // }

    // pacman.setFrieghtenedTimeLeft(pacman.getFrieghtenedTimeLeft() - (length / 2));
    // freightened_time_left -= (length / 2);

    return path;

}

bool StateSpaceSearchR::freightenedNodeEquals(StateSpaceSearchR::FreightenedNode a, StateSpaceSearchR::FreightenedNode b) {
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



////////////////////////////////////////////////// BFS PATHS //////////////////////////////////////////////////

// use for freightened state - goals refers to all ghosts in frieghtened state
// use for power up state, goals refer to power up points
vector<pair<int, int>> StateSpaceSearchR::bfsPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid) {
    cout << "BFS start: " << start.first << " " << start.second << endl;
    cout << "BFS goal: " << goal.first << " " << goal.second << endl;
    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1); // start doesn't have a parent so we set it to (-1, -1)

    queue<pair<int, int>> queue;
    queue.push(start);

    while (!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (current == goal) { // current.x = goal.x && current.y = goal.y
            
            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            cout << "BFS PATH LENGTH: " << path.size() << endl;
            return path;

        }

        vector<pair<int, int>> neighbors = getNeighborsBFS(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    cout << "BFS returns empty vector: " << endl;
    return {};
}




vector<pair<int, int>> StateSpaceSearchR::bfsPathMultiple(pair<int, int> start, set<pair<int, int>> goals, vector<vector<int>> grid) {
    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1);

    queue<pair<int, int>> queue;
    queue.push(start);

    while (!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (goals.find(current) == goals.end()) { // current.x = goal.x && current.y = goal.y
            
            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            return path;
        }

        vector<pair<int, int>> neighbors = getNeighborsBFS(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return {};
}

vector<pair<int, int>> StateSpaceSearchR::bfsPathUnkownGoal(pair<int, int> start, int goal, vector<vector<int>> grid) {
    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1);

    queue<pair<int, int>> queue;
    queue.push(start);

    while(!queue.empty()) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (grid[current.first][current.second] == goal) {

            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            return path;
        }

        vector<pair<int, int>> neighbors = getNeighborsBFS(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return {};
}

// we r finding the distance to the cherry pos and nearest pellet
// If check_nearest_pellet=true, map will have "cherry" and "pellet" keys - cherry one
// if check_nearest_pellet=false, the map will only have "cherry" key. - cherry two
map<string, vector<pair<int, int>>> StateSpaceSearchR::bfsCherry(bool check_nearest_pellet, pair<int, int> start, vector<vector<int>> grid) {
    int pellet = o;
    pair<int, int> cherry_pos = make_pair(13, 13);

    map<pair<int, int>, pair<int, int>> visited_nodes_to_parents = {};
    visited_nodes_to_parents[start] = make_pair(-1, -1);

    queue<pair<int, int>> queue;
    queue.push(start);

    bool checking_for_pellet = (check_nearest_pellet) ? true : false;
    bool checking_for_cherry = true;

    map<string, vector<pair<int, int>>> paths = {};

    while(!queue.empty() && (checking_for_pellet || checking_for_cherry)) {
        pair<int, int> current = queue.front();
        queue.pop();

        if (checking_for_pellet && grid[current.first][current.second] == pellet
            && checking_for_cherry && current == cherry_pos) {
            checking_for_pellet = false;
            checking_for_cherry = false;

            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            paths.emplace(make_pair("pellet", path));
            paths.emplace(make_pair("cherry", path));

            break;
        }

        if (checking_for_pellet && grid[current.first][current.second] == pellet) {
            checking_for_pellet = false;

            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            paths.emplace(make_pair("pellet", path));

        }

        if (checking_for_cherry && current == cherry_pos) {
            checking_for_cherry = false;
            
            vector<pair<int, int>> path;

            while (current.first != -1 && current.second != -1) { // current != (-1, -1)
                path.insert(path.begin(), current);
                current = visited_nodes_to_parents[current];
            }

            paths.emplace(make_pair("cherry", path));
        }

        vector<pair<int, int>> neighbors = getNeighborsBFS(current, grid);

        for (pair<int, int> neighbor : neighbors) {
            if (visited_nodes_to_parents.find(neighbor) == visited_nodes_to_parents.end()) {
                visited_nodes_to_parents[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return paths;

}

vector<pair<int, int>> StateSpaceSearchR::getNeighborsBFS(pair<int, int> node, vector<vector<int>> grid) {
    // grid range:v
    // x : [0, 27]
    // y :[0, 30]

    vector<pair<int, int>> neighbors;


    neighbors.push_back(make_pair(node.first - 1, node.second)); // left
    neighbors.push_back(make_pair(node.first, node.second - 1)); // down
    neighbors.push_back(make_pair(node.first + 1, node.second)); // right
    neighbors.push_back(make_pair(node.first, node.second + 1)); // up
    
    int i = 0;
    while (i < neighbors.size()) {
        pair<int, int> neighbor = neighbors[i];
        int x = neighbor.first;
        int y = neighbor.second;
        if (x < 0 || x > 27 || y > 30 || y < 0 || grid[x][y] == I || grid[x][y] == e || grid[x][y] == n) {
            neighbors.erase(neighbors.begin() + i);
        } 
        else {
            i++;
        }
    }

    return neighbors;
}