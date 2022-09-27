 #include "Wire.h"
 #include <MPU6050_light.h>
 MPU6050 mpu(Wire);

void setup() {
Wire.begin();
mpu.begin();
mpu.calcOffsets();
}
map
void loop() {
  mpu.update();
  
}
  float angle  = mpu.getAngleZ();
  int correction = analogRead(0);
  correction = map(angle, 0, 180, 255, 0);
  
 if (angle > 91) {
analogWrite(9, correction);
}
 else if (angle < 89) {
analogWrite(10, correction);
}
else {
  
}
