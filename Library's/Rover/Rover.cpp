#include "Arduino.h" 
#include "Rover.h"

Rover::Rover(const int motor[4],const int dir[4]){
  _MODE = MODE_LOW;
  for(int i=0; i<4;i++){
      pinMode(motor[i], OUTPUT);
      this->MOTOR[i] = motor[i];
      pinMode(dir[i], OUTPUT);
      this->DIRECTION[i] = dir[i];
	  power[i] = STARTPWM[_MODE][i];
  }
}
int* Rover::getPower(){
  return (int*)power;
}
void Rover::stopEngine(){
  for(int i=0; i<4;i++){
	analogWrite (MOTOR[i], 0);
  }
}
void Rover::startEngine(){
  Serial.println("engine started");
  for(int i=0; i<4;i++){
	analogWrite (MOTOR[i], STARTPWM[_MODE][i]);
  }
}
void Rover::adjustEnginePower(int motor, int pwr){
	analogWrite (MOTOR[motor], power[motor] += pwr);
}
void Rover::setEnginePower(int motor, int pwr){
	analogWrite(MOTOR[motor], power[motor] = pwr);
}
void Rover::setEngineMode(int MODE){
	for(int i=0; i<4;i++){
		power[i] = STARTPWM[MODE][i];
  }
  _MODE = MODE;
}
void Rover::tankRight(){
  digitalWrite (DIRECTION[0], 0); 
  digitalWrite (DIRECTION[1], 1); 
  digitalWrite (DIRECTION[2], 1); 
  digitalWrite (DIRECTION[3], 0); 
}
void Rover::tankLeft(){
  digitalWrite (DIRECTION[0], 1); 
  digitalWrite (DIRECTION[1], 0); 
  digitalWrite (DIRECTION[2], 0); 
  digitalWrite (DIRECTION[3], 1);
}
void Rover::crapRight(){
  digitalWrite (DIRECTION[0], 0); 
  digitalWrite (DIRECTION[1], 1); 
  digitalWrite (DIRECTION[2], 0); 
  digitalWrite (DIRECTION[3], 1); 
}
void Rover::crapLeft(){
  digitalWrite (DIRECTION[0], 1); 
  digitalWrite (DIRECTION[1], 0); 
  digitalWrite (DIRECTION[2], 1); 
  digitalWrite (DIRECTION[3], 0); 
}
void Rover::moveForward(){
  digitalWrite (DIRECTION[0], 1); 
  digitalWrite (DIRECTION[1], 1); 
  digitalWrite (DIRECTION[2], 0); 
  digitalWrite (DIRECTION[3], 0); 
}
void Rover::moveBackward(){
  digitalWrite (DIRECTION[0], 0); 
  digitalWrite (DIRECTION[1], 0); 
  digitalWrite (DIRECTION[2], 1); 
  digitalWrite (DIRECTION[3], 1);
}
void Rover::leftForward(){
  setEnginePower(1, 0);
  setEnginePower(2, 0);
  digitalWrite (DIRECTION[0], 1); 
  digitalWrite (DIRECTION[3], 0);
}
void Rover::rightForward(){
  setEnginePower(0, 0);
  setEnginePower(3, 0);
  digitalWrite (DIRECTION[1], 1); 
  digitalWrite (DIRECTION[2], 0);
}

void Rover::leftBackward(){
  setEnginePower(0, 0);
  setEnginePower(3, 0);
  digitalWrite (DIRECTION[1], 0); 
  digitalWrite (DIRECTION[2], 1);
}
void Rover::rightBackward(){
  setEnginePower(1, 0);
  setEnginePower(2, 0);
  digitalWrite (DIRECTION[0], 0); 
  digitalWrite (DIRECTION[3], 1);
}