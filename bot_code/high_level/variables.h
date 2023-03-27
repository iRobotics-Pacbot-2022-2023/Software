#pragma once

using namespace std;

#include <vector>

// Variables

// Game params
const vector<int> PACBOT_STARTING_POSITION = {14, 7};

// Cherry param
const vector<int> CHERRY_POS = {13, 13};

// Grid Parameters
const int I = 1; // WALL
const int o = 2; // Pellet
const int e = 3; // unreachable
const int O = 4; // power point
const int n = 5; // untouchable
const int P = 6; // Pacbot

// Points
const int CHERRY_POINTS = 100;
const int POWER_POINTS = 50;
const int PELLET_POINTS = 10;
// int GHOST_POINTS = 200;


