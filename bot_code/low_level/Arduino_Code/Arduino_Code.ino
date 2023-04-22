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

#define tof1_i2c_addr 0x30
#define tof2_i2c_addr 0x31
#define tof3_i2c_addr 0x32
#define tof4_i2c_addr 0x33
#define imu_i2c_addr 0x4A


Adafruit_BNO08x imu();
sh2_sensorValue_t sensorValue;

VL53L4CX tof1(&DEV_I2C, 16);
VL53L4CX tof2(&DEV_I2C, 15);
VL53L4CX tof3(&DEV_I2C, 14);
VL53L4CX tof4(&DEV_I2C, 13);


void i2cSetup(){
  DEV_I2C.setSDA(18);
  DEV_I2C.setSCL(19);
  DEV_I2C.begin();
}

void imuSetup(){
  while(!imu.begin_I2C(imu_i2c_addr, &Dev_I2C, 0)){
    delay(10);
  }

  imuSetReports();
  delay(100);
}

float imuLoop(Adafruit_BNO08x imu){
  if(imu.wasReset()){
    imuSetReports();
  }

  if (!imu.getSensorEvent(&sensorValue)){
    return;
  }

  if (sensorValue.sensorId == SH2_GYROSCOPE_CALIBRATED){
    return sensorValue.un.gyroscope.z;
  }
}

void imuSetReports(void) {
  imu.enableReport(SH2_GYROSCOPE_CALIBRATED);
}


void tofSetup(){
  digitalWrite(16, 1);
  digitalWrite(15, 0);
  digitalWrite(14, 0);
  digitalWrite(13, 0);

  // tof1.begin(tof1_i2c_addr);
  tof1.InitSensor(tof1_i2c_addr);

  digitalWrite(16, 0);
  digitalWrite(15, 1);
  digitalWrite(14, 0);
  digitalWrite(13, 0);

  // tof2.begin(tof2_i2c_addr);
  tof2.InitSensor(tof2_i2c_addr);

  digitalWrite(16, 0);
  digitalWrite(15, 0);
  digitalWrite(14, 1);
  digitalWrite(13, 0);

  // tof3.begin(tof3_i2c_addr);
  tof3.InitSensor(tof3_i2c_addr);

  digitalWrite(16, 0);
  digitalWrite(15, 0);
  digitalWrite(14, 0);
  digitalWrite(13, 1);

  // tof4.begin(tof4_i2c_addr);
  tof4.InitSensor(tof4_i2c_addr);

  // tof1.begin(tof1_i2c_addr);
  // tof2.begin(tof2_i2c_addr);
  // tof3.begin(tof3_i2c_addr);
  // tof4.begin(tof4_i2c_addr);

  tof1.VL53L4CX_StartMeasurement();
  tof2.VL53L4CX_StartMeasurement();
  tof3.VL53L4CX_StartMeasurement();
  tof4.VL53L4CX_StartMeasurement();
}

float tofLoop(tof){
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
    return max;
  }
}

void setup() {
  // put your setup code here, to run once:
  i2cSetup();
  tofSetup();
  imuSetup();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  tof1_distance = tofLoop(tof1);
  tof2_distance = tofLoop(tof2);
  tof3_distance = tofLoop(tof3);
  tof4_distance = tofLoop(tof4);
  imu_angle = imuLoop(imu);

  

}
