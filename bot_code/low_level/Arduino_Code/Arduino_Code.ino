#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cx_class.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include <Adafruit_BNO08x.h>

#define DEV_I2C Wire
#define SerialPort Serial

#ifndef LED_BUILTIN
  #define LED_BUILTIN 13
#endif
#define LedPin LED_BUILTIN

void tofSetup(){
  Wire.setSDA(18);
  Wire.setSCL(19);
  Wire.begin();

  VL53L4CX tof1(&DEV_I2C, 16);
  VL53L4CX tof2(&DEV_I2C, 15);
  VL53L4CX tof3(&DEV_I2C, 14);
  VL53L4CX tof4(&DEV_I2C, 13);

  digitalWrite(16, 1);
  digitalWrite(15, 0);
  digitalWrite(14, 0);
  digitalWrite(13, 0);

  tof1.begin();
  tof1.InitSensor(0x30);

  digitalWrite(16, 0);
  digitalWrite(15, 1);
  digitalWrite(14, 0);
  digitalWrite(13, 0);

  tof2.begin();
  tof2.InitSensor(0x31);

  digitalWrite(16, 0);
  digitalWrite(15, 0);
  digitalWrite(14, 1);
  digitalWrite(13, 0);

  tof3.begin();
  tof3.InitSensor(0x32);

  digitalWrite(16, 0);
  digitalWrite(15, 0);
  digitalWrite(14, 0);
  digitalWrite(13, 1);

  tof4.begin();
  tof4.InitSensor(0x33);


  //not sure if these lines are necessary
  tof1.begin();
  tof2.begin();
  tof3.begin();
  tof4.begin();

  tof1.VL53L4CX_StartMeasurement();
  tof2.VL53L4CX_StartMeasurement();
  tof3.VL53L4CX_StartMeasurement();
  tof4.VL53L4CX_StartMeasurement();
}

int tofLoop(tof){
  VL53L4CX_MultiRangingData_t MultiRangingData;
  VL53L4CX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;
  uint8_t NewDataReady = 0;
  int no_of_object_found = 0, j;
  char report[64];
  int status;
  
  status = tof.VL53L4CX_GetMeasurementDataReady(&NewDataReady);

  if ((!status) && (NewDataReady != 0)) {
    status = tof.VL53L4CX_GetMultiRangingData(pMultiRangingData);
    no_of_object_found = pMultiRangingData->NumberOfObjectsFound;
    int max = 99999999999;
    for (int i = 0; i < no_of_object_found){
      if(pMultiRangingData->RangeData[i].RangeMillimeter <= max){
        max = pMultiRangingData->RangeData[i].RangeMillimeter;
      }
    }
    if (status == 0) {
      status = sensor_vl53l4cx_sat.VL53L4CX_ClearInterruptAndStartMeasurement();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  tofSetup();
   
}

void loop() {
  // put your main code here, to run repeatedly:
  tof1_distance = tofLoop(tof1);
  tof2_distance = tofLoop(tof2);
  tof3_distance = tofLoop(tof3);
  tof4_distance = tofLoop(tof4);


}
