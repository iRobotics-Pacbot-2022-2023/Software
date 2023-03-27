#include <Arduino.h>
#include <Encoder.h>
#include <ADC.h>
#include <vl53l4cx_class.h>

VL53L4CX tof(&Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  Serial.println("Start");

  tof.VL53L4CX_SetDeviceAddress(0x29);
  int status = tof.InitSensor(0x29);
  Serial.printf("start status: %d\n", status);
  status = tof.VL53L4CX_StartMeasurement();
  Serial.printf("start status: %d\n", status);
  Serial.println("starting fr");
  tof.VL53L4CX_ClearInterruptAndStartMeasurement();
}

void loop() {
  VL53L4CX_MultiRangingData_t data;
  uint8_t hasNewData = 0;
  int status;
  do {
    status = tof.VL53L4CX_GetMeasurementDataReady(&hasNewData);
  } while (!hasNewData);

  Serial.printf("ready status: %d\n", status);
  status = tof.VL53L4CX_GetMultiRangingData(&data);
  for (int i = 0; i < data.NumberOfObjectsFound; ++i) {
    Serial.printf("read status: %d, mm: %hd\n", status, data.RangeData[i].RangeMilliMeter);
  }
  status = tof.VL53L4CX_ClearInterruptAndStartMeasurement();
  Serial.printf("clear status: %d\n", status);
}