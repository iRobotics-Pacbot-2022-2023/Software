#pragma once

#include <utility>
#include <vector>
#include <string>
#include <cmath>

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

        Ghost(std::pair<int,int> firstPos, /*std::pair<int,int> secondPos, */ Color color_, Direction direction_, GhostState startPath, std::pair<int,int> scatter_pos );

        std::pair<std::pair<int, int>, Direction> get_move_based_on_target(std::pair<int, int> target);

        // pair<int,int> Ghost::getRedGhostPos() { return ghostlocs[0]; }
        // pair<int,int> Ghost::getOrangeGhostPos() { return ghostlocs[1]; }
        // pair<int,int> Ghost::getBlueGhostPos() { return ghostlocs[2]; }
        // pair<int,int> Ghost::getPinkGhostPos() { return ghostlocs[3]; }


        // void moveOrange();
        // void moveRed();
        // void movePink();
        // void moveBlue();

        // void moveRedChase();
        // void moveOrangeChase();
        // void moveBlueChase();
        // void movePinkChase();

        // void moveBlueScatter();
        // void moveRedScatter();
        // void moveOrangeScatter();
        // void movePinkScatter();
    
        // void moveRedFrightened();
        // void moveOrangeFrightened();
        // void moveBlueFrightened();
        // void movePinkFrightened();

        void /* some return type for get scatter move*/ get_next_scatter_move();
        double get_euclidian_distance(std::pair<int, int> pos_a, std::pair<int, int> pos_b);
        std::vector<std::pair<int, int>> find_possible_moves();
        bool is_move_legal(std::pair<int, int> move);

        std::pair<std::pair<int, int>, Direction> _get_next_pink_chase_move();
        std::pair<std::pair<int, int>, Direction> _get_next_red_chase_move();
        std::pair<std::pair<int, int>, Direction> _get_next_orange_chase_move();

        std::pair<std::pair<int, int>, Direction> _get_next_scatter_move();

        Direction getDirection( std::pair<int, int> prevPos, std::pair<int, int> newPos);
        std::pair<int, int> getGhostLocation();


        std::pair<std::pair<int, int>, Direction>  /* some return type for get frightened move*/ get_next_frightened_move();
    
    private:

        GhostState current_ghost_state; //tells us what mode the ghosts are in (frightened, chase, scatter)
        Color ghost_color;
        Direction direction_facing;
        
        // RED, ORANGE, BLUE, PINK
        // vector<pair<int,int>> ghostlocs = { {13, 19}, {15,15}, {12,15}, {14, 15} };
        std::pair<int, int> curGhostLocation;
        std::pair<int, int> scatterLocation;


        
        
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
