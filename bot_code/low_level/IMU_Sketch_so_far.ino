#include <Adafruit_BNO08x.h>
sh2_SensorValue_t sensorValue;

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200); //establishes connection with teensy
  while(!Serial) delay(10); //will wait till the serial console opens
  Serial.println("Running IMU measurements!");
  if (!bno08x.being_IC2()) {
    Serial.println("Failed to find chip"); //error message
    while (1) {delay(10);}
  }
/*  Serial.println("BN0080 Found!");
   for (int n = 0; n < bno08x.prodIds.numEntries; n++) {
    Serial.print("Part ");
    Serial.print(bno08x.prodIds.entry[n].swPartNumber);
    Serial.print(": Version :");
    Serial.print(bno08x.prodIds.entry[n].swVersionMajor);
    Serial.print(".");
    Serial.print(bno08x.prodIds.entry[n].swVersionMinor);
    Serial.print(".");
    Serial.print(bno08x.prodIds.entry[n].swVersionPatch);
    Serial.print(" Build ");
    Serial.println(bno08x.prodIds.entry[n].swBuildNumber);
}*/
}

setReports();
/*We want to aquire the rotation vector and calibrated gyroscope data.*/
/*This part will initialize what specfic data the IMU should report back to the teensy*/
void setReports(void) {
  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(SH2_GAME_ROTATION_VECTOR)) {
    Serial.println("Could not enable game vector");
  }
  if (!bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED)) {
    Serial.println("Could not enable gyroscope");
  }
}
void loop() {
  // put your main code here, to run repeatedly:
if (bno08x.wasReset()) {
    Serial.print("sensor was reset "); //If for whatever reason the sensor was reset then print that it was
    setReports();
  }
   if (!bno08x.getSensorEvent(&sensorValue)) { //If we don't find a sensor event we return nothing
    return;
  }
}
