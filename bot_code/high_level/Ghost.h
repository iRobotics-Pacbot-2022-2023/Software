#include <pair>

class Ghost {
    public:
        enum direction {
        right, up, left, down, upperRight, upperLeft, lowerRight, lowerLeft;
    }
    enum color{
        red, blue, pink, orange;
    }
    enum start_path {
        frightened, chase, scatter;
    }
    Ghost(std::pair<int,int> firstPos, /*std::pair<int,int> secondPos, */ color color_, direction direction_, start_path startPath, std::pair<int,int> scatter_pos );

    void moveOrange();
    void moveRed();
    void movePink();
    void moveBlue();

    void moveRedChase();
    void moveOrangeChase();
    void moveBlueChase();
    void movePinkChase();

    void moveBlueScatter();
    void moveRedScatter();
    void moveOrangeScatter();
    void movePinkScatter();

    void /* some return type for get scatter move*/ get_next_scatter_move() ;
    
    private:

    vector<pair<int>>ghostlocs = { {13, 19}, {15,15}, {12,15}, {14, 15} };

    const std::pair<int,int> red_init_pos = {13,19};
    const std::pair<int,int> red_init_npos = {12,19};
    direction red_init_dir = left;

    const std::pair<int,int> pink_init_pos = {14,15}
    const std::pair<int,int> pink_init_npos = {14,16};
    direction pink_init_dir = up

    const std::pair<int,int> blue_init_pos = {12,15};
    const std::pair<int,int> blue_init_npos = {12,16};
    direction blue_init_dir = up;

    const std::pair<int,int> orange_init_pos = {15,15};
    const std::pair<int,int> orange_init_npos = {15,16};
    direction orange_init_dir = up;

    const std::pair<int, int> pink_scatter_pos = {2, 32};
    const std::pair<int, int> orange_scatter_pos = {0, -1};
    const std::pair<int, int> blue_scatter_pos = {27, -1};
    const std::pair<int, int> red_scatter_pos = {25, 32};

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

}