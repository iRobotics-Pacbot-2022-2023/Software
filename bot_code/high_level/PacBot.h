// file for testing
#pragma once
#include <utility>
#include <vector>
class PacBot {
            public:
                PacBot();
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