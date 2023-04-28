#include <wiringSerial.h>
#include <wiringPi.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include "StateSpaceSearch-R.h"
char old;
int main() {
    int serial_port;
    const char* port = "/dev/ttyS0"; // need to set correct port name
    int baud_rate = 115200; // set baud rate to 9600 
    const int balls = 5; //sets the depth of the path searched
    serial_port = serialOpen(port, baud_rate); //begins serial connection and this specifically for UART
    if (serial_port < 0) {
        std::cout << "Error opening serial port" << std::endl;
        return 1;
    }
    
    if (wiringPiSetup () == -1)
    {
        fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
        
        return 1;
    }

    //vector<pair<int, int>> insert = generatePath(balls);
    // write data to the Teensy
    //serialPrintf(serial_port, insert);
    serialPrintf(serial_port, "Hello, Teensy!\n");
    // read data from the Teensy
    //could probably change this to something else like the entire vector we were talking about
    //They are gonna send some character or something that will tell us that they stopped and we need to recalibrate our algorithm
    char data;
    while (serialDataAvail(serial_port)) {
        data += char(serialGetchar(serial_port));
    }
    old = data;
    //set this for testing purposes
    std::cout << "Received from Teensy: " << data << std::endl;
    //they will send us a signal tha tell us that they have stopped and are awaiting new instructions
    //override store previous move
    if(data == '&'){
        //send new shit
    }
    //compare between what the current instruction the bot is going at and what the algorithm is sending
    //If there is conflict then override the current instruction and send what the algorithm is saying
    //This is commented out until we finished the high level
    //else if( != old){
       //send new shit
    //}

    serialClose(serial_port); //end serial connection
    return 0;
}