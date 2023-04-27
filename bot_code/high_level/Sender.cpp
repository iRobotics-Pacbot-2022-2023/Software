#include <wiringSerial.h>
#include <wiringPi.h>
#include <iostream>
#include <string>
#include <stdio.h>

int main() {
    int serial_port;
    const char* port = "/dev/ttyS0"; // need to set correct port name
    const int baud_rate = 9600; // set baud rate to 9600 
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

    // write data to the Teensy
    serialPrintf(serial_port, "Hello, Teensy!\n");

    // read data from the Teensy
    //could probably change this to something else like the entire vector we were talking about
    std::string data;
    while (serialDataAvail(serial_port)) {
        data += char(serialGetchar(serial_port));
    }
    //set this for testing purposes
    std::cout << "Received from Teensy: " << data << std::endl;

    serialClose(serial_port); //end serial connection
    return 0;
}