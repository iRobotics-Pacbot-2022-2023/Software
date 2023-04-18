#include "Hash_shit.h"
//create keys that are random  unsigned long long  since they have to be at least 64 bits
//Therefore we want numbers from 0 to 2^64-1 this is also to avoid assigning the same hash values
unsigned long long ZorbTable [30][30][7]; 

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

for(i = 0; i < 30; i++){
    for(j = 0; j < 30; j++){
        for(k = 0; k < 7; k++){
        ZorbTable[i][j][k] = randomNum();
        }
    }
 
}

}

//need to figure out what would be considered empty for each cell
 unsigned long long hashgenerator(vector<vector<int>> grid){
 int i, j;

    }
    
