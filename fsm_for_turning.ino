//Enum for the switch case for the different turns
#include "Wire.h"
#include <MPU6050_light.h>
 MPU6050 mpu(Wire);

#define motor1pin1  11 //in1 to arduino
#define motor1pin2  8 //in2 to arduino 

#define motor2pin1  4 //in3 to arduino
#define motor2pin2 3 //in4 to arduino

#define IR A0
unsigned long timer = 0;
enum turn
{
   turn1, turn2, turn3, turn4, turn5, turn6 
};
typedef enum turn turn_t;

int IRread;

void setup() {
pinMode(motor1pin1, OUTPUT); // set pinmode to output 
  pinMode(motor1pin2, OUTPUT); // for High - forward or Low - backward setting
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  delay(5000);

  Serial.begin(9600);
  Wire.begin();

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  //Serial.println("Done!\n");  
motorON(); //Makes tractor start running in the first straight of the course, the rest is handled by the FSM
}

void loop() {
  mpu.update();

  if((millis()-timer)>10){ // print data every 10ms
  Serial.print("X : "); // not needed
  Serial.print(mpu.getAngleX()); // not needed
  Serial.print("\tY : ");// not needed
  Serial.print(mpu.getAngleY());// not needed
  Serial.print("\tZ : "); //get z angle aka YAW
  Serial.println(mpu.getAngleZ()); //print for verification 
  delay(500);
  timer = millis();  // set timer 


  }
  float yawAngle = mpu.getAngleZ(); //var to get use yaw angle as a float

  analogWrite(9,255);
  analogWrite(10,255);

  TurningFSM();
}


//Performs left turns by turning off the left motors
void LeftTurn(){
digitalWrite(motor1pin1, LOW);
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, HIGH);
digitalWrite(motor2pin2, LOW); 
}
//Performs right turns by turning off right motors
void RightTurn() {
digitalWrite(motor1pin1, HIGH);
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, LOW);
digitalWrite(motor2pin2, LOW);   
}
//Turns on all motors
void motorON() {
digitalWrite(motor1pin1, HIGH);
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, HIGH);
digitalWrite(motor2pin2, LOW);     
}
//FSM for turning
void TurningFSM() {
 float yawAngle = mpu.getAngleZ(); //var to get use yaw angle as a float
   IRread = analogRead(IR);
  static turn_t turn = turn1;
  switch (turn) {

 
  // if the IR sensor detects the first black tape, perform a left turn and when the gyroscope 
  //reading between 86.74 and 94.7 degrees stop turning by turning on all motors
  case turn1:
  if (IRread <= 120){
    LeftTurn();
  }
    if(94.7 >= yawAngle && yawAngle >= 86.74) {
      motorON();
      turn = turn2;
    }   
  break;
   // if the IR sensor detects the second black tape, perform a left turn and when the gyroscope 
   //reading between 176.74 and 184.7 degrees stop turning by turning on all motors
  case turn2:
  if (IRread <= 120){
    LeftTurn();
  }
    if(184.7 >= yawAngle && yawAngle >= 176.74) {
      motorON();
      turn = turn3;
    }
  break;
   // if the IR sensor detects the third black tape, perform a right turn and when the gyroscope
   //reading between 86.74 and 94.7 degrees stop turning by turning on all motors
  case turn3:
  if (IRread <= 120){
    RightTurn();
  }
    if(94.7 >= yawAngle && yawAngle >= 86.74) {
      motorON();
      turn = turn4;
    }
  break;
   // if the IR sensor detects the fourth black tape, perform a right turn and when the gyroscope
   //reading between 4.7 and -3.26  degrees stop turning by turning on all motors
  case turn4:
  if (IRread <= 120){
    RightTurn();
  }
    if(4.7 >= yawAngle && yawAngle >= -3.26) {
      motorON();
      turn = turn5;
    }
  break;
   // if the IR sensor detects the fifth black tape, perform a left turn and when the gyroscope
   //reading between 86.74 and 94.7 degrees stop turning by turning on all motors
  case turn5:
  if (IRread <= 120){
    LeftTurn();
  }
    if(94.7 >= yawAngle && yawAngle >= 86.74) {
      motorON();
      turn = turn6;
    }
  break;
   // if the IR sensor detects the sixth black tape, perform a left turn and when the gyroscope
   //reading between 175.3 and 184.7 degrees stop turning by turning on all motors
  case turn6:
  if (IRread <= 120){
    LeftTurn();
  }
    if(184.7 >= yawAngle && yawAngle >= 176.74) {
      motorON();
    }
  break;
}
}
