// file for testing
#include "Ghost.h"
class PacBot {
            public:
                PacBot() {
                    pos = std::pair<int, int>(5, 5);
                }
                std::pair<int, int> getPos();
                void move(std::pair<int, int> newLoc);
                enum PacDirection {
                    right, up, left, down
                };
                void changeDirection(PacDirection newDirection);
                PacDirection getPacDirection();
            private:
                std::pair<int, int> pos;
                PacDirection pacdirection_;
};