#pragma once

using namespace std;

#include <vector>
#include "variables.h"


class grid {
    public:
        grid();
        int height();
        int width();
        vector<vector<char>> & getGrid();
        void update();
    private:
        vector<vector<char>> grid_;
};
                        // Bottom Left
//     vector<vector<int>> grid = grid =  {{I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,o,I,e,e,e,I,I,I,I,I,I,I,I,I,I}, // 0
//                                         {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,o,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
//                                         {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,o,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,o,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,o,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,o,I,I,I,I,I,o,I,I,o,I,I,I,o,I}, // 5
//                                         {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
//                                         {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,o,o,o,I,I,o,o,o,o,o,o,o,o,o,o,I,I,o,o,o,o,I,I,I,o,I},
//                                         {I,o,I,I,o,I,I,o,I,I,o,I,I,o,I,I,I,I,I,o,I,I,o,I,I,o,I,I,I,o,I}, // 10
//                                         {I,o,I,I,o,I,I,o,I,I,o,I,I,o,I,n,n,n,I,o,I,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,o,o,o,I,I,o,o,o,o,I,I,o,I,n,n,n,I,o,o,o,o,I,I,o,o,o,o,o,I},
//                                         {I,o,I,I,I,I,I,o,I,I,I,I,I,o,I,n,n,n,n,o,I,I,I,I,I,o,I,I,I,I,I},
//                                         {I,o,I,I,I,I,I,o,I,I,I,I,I,o,I,n,n,n,n,o,I,I,I,I,I,o,I,I,I,I,I},
//                                         {I,o,o,o,o,I,I,o,o,o,o,I,I,o,I,n,n,n,I,o,o,o,o,I,I,o,o,o,o,o,I}, // 15
//                                         {I,o,I,I,o,I,I,o,I,I,o,I,I,o,I,n,n,n,I,o,I,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,I,I,o,I,I,o,I,I,o,I,I,I,I,I,o,I,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,o,o,o,I,I,o,o,o,o,o,o,o,o,o,o,I,I,o,o,o,o,I,I,I,o,I},
//                                         {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,I,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,I,I,I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,I,I,I,o,I,I,I,o,I}, // 20
//                                         {I,o,I,I,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,I},
//                                         {I,o,I,I,o,I,I,I,I,I,o,I,I,I,I,I,o,I,I,I,I,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,I,I,I,I,I,o,I,e,e,e,I,o,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,o,o,o,I,I,o,I,e,e,e,I,o,I,e,e,e,I,o,I,I,o,I,I,I,o,I},
//                                         {I,o,I,I,o,I,I,o,I,I,o,I,e,e,e,I,o,I,e,e,e,I,o,I,I,o,I,I,I,o,I}, // 25
//                                         {I,o,o,o,o,I,I,O,o,o,o,I,e,e,e,I,o,I,e,e,e,I,o,o,o,o,o,O,o,o,I},
//                                         {I,I,I,I,I,I,I,I,I,I,I,I,e,e,e,I,o,I,e,e,e,I,I,I,I,I,I,I,I,I,I}};
//                                 //       |         |         |         |         |         |         |
//                                 //        0         5        10        15       20         25       30