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


Adafruit_BNO08x imu(-1);
sh2_SensorValue_t sensorValue;

VL53L4CX tof1(&DEV_I2C, 16);
VL53L4CX tof2(&DEV_I2C, 15);
VL53L4CX tof3(&DEV_I2C, 14);
VL53L4CX tof4(&DEV_I2C, 13);


void i2cSetup(){
  // DEV_I2C.setSDA(18);
  // DEV_I2C.setSCL(19);
  Serial.println("starting i2c setup");
  DEV_I2C.begin();
  Serial.println("done with i2c");
}

void imuSetup(){
  while(!imu.begin_I2C(imu_i2c_addr, &DEV_I2C, 0)){
    delay(10);
  }

  imuSetReports();
  delay(100);

  Serial.println("done withimu setup");
}

float imuLoop(Adafruit_BNO08x imu){
  if(imu.wasReset()){
    imuSetReports();
  }

  if (!imu.getSensorEvent(&sensorValue)){
    return 1000;
  }

  if (sensorValue.sensorId == SH2_GYROSCOPE_CALIBRATED){
    return sensorValue.un.gyroscope.z;
  }
  return 0;
}

void imuSetReports() {
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

  Serial.println("Starting tof starting");

  tof1.VL53L4CX_StartMeasurement();
  tof2.VL53L4CX_StartMeasurement();
  tof3.VL53L4CX_StartMeasurement();
  tof4.VL53L4CX_StartMeasurement();

  Serial.println("Done with tof setup");
}

float tofLoop(VL53L4CX tof){
  Serial.println("starting tofloop");

  VL53L4CX_MultiRangingData_t MultiRangingData;
  VL53L4CX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;
  uint8_t NewDataReady = 0;
  int no_of_object_found = 0;
  int status = 0;
  
  Serial.println("got to this point");

  status = tof.VL53L4CX_GetMeasurementDataReady(&NewDataReady);

  Serial.println("got to the second point");
  if ((!status) && (NewDataReady != 0)) {
    Serial.println("entered here");
    status = tof.VL53L4CX_GetMultiRangingData(pMultiRangingData);
    no_of_object_found = pMultiRangingData->NumberOfObjectsFound;
    float max = 99999;
    Serial.println(no_of_object_found);
    for (int i = 0; i < no_of_object_found; i++){
      if(pMultiRangingData->RangeData[i].RangeMilliMeter <= max){
        max = pMultiRangingData->RangeData[i].RangeMilliMeter;
      }
    }
    if (status == 0) {
      status = tof.VL53L4CX_ClearInterruptAndStartMeasurement();
    }
    Serial.printf("%f", max);
    return max;
  }
  Serial.println("reached end");
  return -1;
}

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial) delay(10);
  Serial.println("hi");
  i2cSetup();
  tofSetup();
  imuSetup();
  
}


float tof1_distance = 0;
float tof2_distance = 0;
float tof3_distance = 0;
float tof4_distance = 0;
float imu_angle = 0;
float temp;
void loop() {
  // put your main code here, to run repeatedly:
  
  temp = tofLoop(tof1);
  if(temp != -1){
    tof1_distance = temp;
  }


  temp = tofLoop(tof2);
  if(temp != -1){
    tof2_distance = temp;
  }

  temp = tofLoop(tof3);
  if(temp != -1){
    tof3_distance = temp;
  }

  temp = tofLoop(tof4);
  if(temp != -1){
    tof4_distance = temp;
  }

  // temp = imuLoop(imu);
  // if(temp != 1000){
  //   imu_angle = temp;
  // }

  Serial.printf("%f", tof1_distance);
  Serial.printf("%f", tof2_distance);
  Serial.printf("%f", tof3_distance);
  Serial.printf("%f", tof4_distance);
  Serial.printf("%d", imu_angle);

}
