#pragma once

using namespace std;

#include <vector>

#include <utility>

// Variables

// Game params
const pair<int,int> PACBOT_STARTING_POSITION = {14, 7};

// Cherry param
const pair<int,int> CHERRY_POS = {13, 13};

// Ghost Exit
const pair<float,int> GHOST_EXIT = {13.5, 19};

// Ghost starting positions
const pair<int,int> RED_GHOST_STARTING_POSITION = {13, 11};
const pair<int,int> PINK_GHOST_STARTING_POSITION = {13, 12};
const pair<int,int> BLUE_GHOST_STARTING_POSITION = {13, 13};
const pair<int,int> ORANGE_GHOST_STARTING_POSITION = {13, 14};
const pair<int,int> GHOST_STARTING_POSITIONS[4] = {{13, 11}, {13, 12}, {13, 13}, {13, 14}};

// Ghost scatter locations
const pair<int, int> RED_GHOST_SCATTER_LOCATION = {1, 1};
const pair<int, int> PINK_GHOST_SCATTER_LOCATION = {1, 19};
const pair<int, int> BLUE_GHOST_SCATTER_LOCATION = {26, 1};
const pair<int, int> ORANGE_GHOST_SCATTER_LOCATION = {26, 19};
// const pair<int,int> GHOST_SCATTER_LOCATIONS[4] = {{1, 1}, {1, 19}, {26, 1}, {26, 19}};

// Grid Parameters
const int I = 1; // WALL
const int o = 2; // Pellet
const int e = 3; // unreachable
const int O = 4; // power point
const int n = 5; // untouchable
const int P = 6; // Pacbot
const int v = 7; // visited - No pellets here
// const int ch = 8; // cherry

// Points
const int CHERRY_POINTS = 100;
const int POWER_POINTS = 50;
const int PELLET_POINTS = 10;

/* Ghosts Points
first = 200
second = 400
third = 800
fourth = 1600
*/


