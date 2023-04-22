#pragma once
#include "grid.h"
#include <iostream>
#include <random>
#include <list> 
using namespace std;
//Important stuff of the Zoribist hashing implementation
unsigned long long randomNum();
void tablefiller();
unsigned long long hashgenerator(vector<vector<int>> grid); 
unsigned long long ZorbTable [28][31][7]; 
