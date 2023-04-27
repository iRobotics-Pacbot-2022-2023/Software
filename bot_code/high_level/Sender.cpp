#include <wiringSerial.h>
#include <iostream>
#include <string>

int main() {
    int serial_port;
    const char* port = "/dev/ttyAMA0"; // need to set correct port name
    const int baud_rate = 9600; // set baud rate to 9600

    serial_port = serialOpen(port, baud_rate);
    if (serial_port < 0) {
        std::cout << "Error opening serial port" << std::endl;
        return 1;
    }

    // write data to the Teensy
    serialPrintf(serial_port, "Hello, Teensy!\n");

    // read data from the Teensy
    std::string data;
    while (serialDataAvail(serial_port)) {
        data += char(serialGetchar(serial_port));
    }
    //set this for testing purposes
    std::cout << "Received from Teensy: " << data << std::endl;

    serialClose(serial_port);
    return 0;
}