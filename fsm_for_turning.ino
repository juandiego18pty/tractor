enum turn
{
   turn1, turn2, turn3, turn4, turn5, turn6
};
typedef enum turn turn_t;

//I need all th gyro set up stuff
//I also need the IRread stuff 
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  TurningFSM();
}

void LeftTurn(){
digitalWrite(motor1pin1, LOW);
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, HIGH);
digitalWrite(motor2pin2, LOW); 
}

void RightTurn() {
digitalWrite(motor1pin1, HIGH);
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, LOW);
digitalWrite(motor2pin2, LOW);   
}
void motorON() {
digitalWrite(motor1pin1, HIGH);
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, HIGH);
digitalWrite(motor2pin2, LOW);     
}

void TurningFSM() {
  switch(turn)
  case turn1:
  if (IRread <= 120){
    LeftTurn();
  }
    if(yawAngle = 90) {
      motorON();
      turn = turn2;
    }   
  break;
  case turn2:
  if (IRread <= 120){
    LeftTurn();
  }
    if(yawAngle = 180) {
      motorON();
      turn = turn3;
    }
  break;
  case turn3:
  if (IRread <= 120){
    RightTurn();
  }
    if(yawAngle = 90) {
      motorON();
      turn = turn4;
    }
  break;
  case turn4:
  if (IRread <= 120){
    RightTurn();
  }
    if(yawAngle = 0) {
      motorON();
      turn = turn5;
    }
  break;
  case turn5:
  if (IRread <= 120){
    LeftTurn();
  }
    if(yawAngle = 90) {
      motorON();
      turn = turn6;
    }
  break;
  case turn6:
  if (IRread <= 120){
    LeftTurn();
  }
    if(yawAngle = 180) {
      motorON();
    }
  break;
}
