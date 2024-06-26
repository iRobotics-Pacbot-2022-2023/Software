#include "Hash.h"
//create keys that are random  unsigned long long  since they have to be at least 64 bits
//Therefore we want numbers from 0 to 2^64-1 this is also to avoid assigning the same hash values
unsigned long long ZorbTable[28][31][7]; //28 31 7
//Random Number generator for 64 bits
unsigned long long randomNum(){ 
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    
    uint64_t rand_num = dis(gen);
    return(rand_num); 
}

//fills table function with the generated keys
void tablefiller(){
int i, j, k;
//fill zorobist table
for(i = 0; i < 28; i++){
    for(j = 0; j < 31; j++) {
        for(k = 0; k < 7; k++) {
        ZorbTable[i][j][k] = randomNum();
        }
    }
 
}

}


 unsigned long long hashgenerator(vector<vector<int>> grid){
 int i, j, piece;
 unsigned long long hash = 0;
      for(i = 0; i < grid.size(); i++){
        for(j = 0; j < grid[i].size(); j++){
            if(grid[i][j] != v){ // need to figure out how to detect if a cell isnt empty
            //Need to have a specfic int value for each piece
            if(grid[i][j] == I){
                piece = I;
            }
            else if(grid[i][j] == o){
                piece = o;
            }
            else if(grid[i][j] == e){
                piece = e;
            }
            else if(grid[i][j] == O){
                piece = O;
            }
            else if(grid[i][j] == n){
                piece = n; 
            }
            else if(grid[i][j] == P){
                piece = P; 
            }
            hash ^= ZorbTable[i][j][piece]; //Use xor to calculate hash value and allows for hash's to be reused             
            }
        }
      }
      return hash; 
    }
    
