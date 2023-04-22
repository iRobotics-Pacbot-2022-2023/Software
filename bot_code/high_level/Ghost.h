#pragma once

#include <utility>
#include <vector>
#include <string>
#include <cmath>
#include "grid.h"
#include "PacBot.h"

#include <queue>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class Ghost {
    public:

        enum Direction {
            right, up, left, down
        };

        enum Color {
            red, blue, pink, orange
        };

        enum GhostState {
            frightened, chase, scatter
        };
        Ghost();
        Ghost(PacBot & pac);
        // GETTERS
        PacBot getPac();
        std::pair<int, int> getGhostLocation();
        Direction getDirection( std::pair<int, int> prevPos, std::pair<int, int> newPos);
        std::vector<std::vector<int>> getGrid();
        Direction getterDirection();

        // CALCULATING FUNCTIONS, WILL MOST LIKELY MOVE TO DIFFERENT CLASS
        // THE PACMANSTATE::DIRECTION CAUSES ERRORS FOR NOW, BUT WE WILL FIX LATER
        std::pair<std::pair<int, int>, Ghost::Direction> get_move_based_on_target(std::pair<int, int> target);
        std::pair<std::pair<int, int>, Direction> _get_next_pink_chase_move(std::vector<std::vector<int>> grid, std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Direction ghostDirection);
        std::pair<std::pair<int, int>, Direction> _get_next_red_chase_move(std::vector<std::vector<int>> grid, std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Direction ghostDirection);
        std::pair<std::pair<int, int>, Direction> _get_next_orange_chase_move(std::vector<std::vector<int>> grid, std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Direction ghostDirection);
        std::pair<std::pair<int, int>, Direction> _get_next_blue_chase_move(std::vector<std::vector<int>> grid, std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Direction ghostDirection);
        vector<pair<int, int>> bfsPathSingle(pair<int, int> start, pair<int, int> goal, vector<vector<int>> grid);
        vector<pair<int, int>> getNeighbors(pair<int, int> node, vector<vector<int>> grid);

        // UNFINISHED/DIFFERENT STATE
        // void /* some return type for get scatter move*/ get_next_scatter_move();
        std::pair<std::pair<int, int>, Direction> _get_next_scatter_move();
        std::pair<std::pair<int, int>, Ghost::Direction> _get_next_frightened_move();
        std::pair<std::pair<int, int>, Ghost::Direction> _get_next_state_move(std::vector<std::vector<int>> grid, std::pair<int, int> pacbotPos, PacmanState::Direction pacbotDirection, std::pair<int, int> ghostPos, Direction ghostDirection);


        // UTILITY FUNCTIONS
        void ghostMove(std::pair<int, int> pair);
        double get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b);
        std::vector<std::pair<int, int>> find_possible_moves();
        bool is_move_legal(std::pair<int, int> move);
    
    private:

        GhostState current_ghost_state; //tells us what mode the ghosts are in (frightened, chase, scatter)
        Color ghost_color;
        Direction direction_facing;
        
        // RED, ORANGE, BLUE, PINK
        // vector<pair<int,int>> ghostlocs = { {13, 19}, {15,15}, {12,15}, {14, 15} };
        
        std::pair<int, int> curGhostLocation;
        std::pair<int, int> scatterLocation;

        // gonna create some variables for testing
        // Grid grid;
        PacBot pacbot;


        vector<vector<int>> grid =  {{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,v,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
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

        ///
        
        // const std::pair<int,int> red_init_pos = {13,19};
        // const std::pair<int,int> red_init_npos = {12,19};
        // Direction red_init_dir = left;

        // const std::pair<int,int> pink_init_pos = {14,15};
        // const std::pair<int,int> pink_init_npos = {14,16};
        // Direction pink_init_dir = up;

        // const std::pair<int,int> blue_init_pos = {12,15};
        // const std::pair<int,int> blue_init_npos = {12,16};
        // Direction blue_init_dir = up;

        // const std::pair<int,int> orange_init_pos = {15,15};
        // const std::pair<int,int> orange_init_npos = {15,16};
        // Direction orange_init_dir = up;

        // const std::pair<int, int> pink_scatter_pos = {2, 32};
        // const std::pair<int, int> orange_scatter_pos = {0, -1};
        // const std::pair<int, int> blue_scatter_pos = {27, -1};
        // const std::pair<int, int> red_scatter_pos = {25, 32};

        
    /*pink_start_path = [((14,17),up),((14,18),up),((14,19),up)]

blue_start_path = [((12,17),up),((12,16),down),((12,15),down),((12,16),up),((12,17),up),
            ((12,16),down),((12,15),down),((12,16),up),((12,17),up),((12,16),down),
            ((12,15),down),((12,16),up),((12,17),up),((12,16),down),((12,15),down),
            ((12,16),up),((12,17),up),((12,16),down),((12,15),down),((13,15),right),
            ((13,16),up),((13,17),up),((13,18),up),((13,19),up)]

orange_start_path = [((15,17),up),((15,16),down),((15,15),down),((15,16),up),((15,17),up),
              ((15,16),down),((15,15),down),((15,16),up),((15,17),up),((15,16),down),
              ((15,15),down),((15,16),up),((15,17),up),((15,16),down),((15,15),down),
              ((15,16),up),((15,17),up),((15,16),down),((15,15),down),((15,16),up),
              ((15,17),up),((15,16),down),((15,15),down),((15,16),up),((15,17),up),
              ((15,16),down),((15,15),down),((15,16),up),((15,17),up),((15,16),down),
              ((15,15),down),((15,16),up),((15,17),up),((15,16),down),((15,15),down),
              ((14,15),left),((14,16),up),((14,17),up),((14,18),up),((14,19),up)]*/

    // respawn_path = [((12,17),up),((12,16),down),((12,15),down),((13,15),right),((13,16),up),((13,17),up),((13,18),up),((13,19),up)]

    // We would make a separate directions vector and a separate std::pair<int int> vector

};
