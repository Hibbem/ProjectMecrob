#include "Arduino.h" 
#include "Rover.h"

Rover::Rover(const int motor[4],const int dir[4])
{
  for(int i=0; i<4;i++){
      pinMode(motor[i], OUTPUT);
      this->MOTOR[i] = motor[i];
      pinMode(dir[i], OUTPUT);
      this->DIRECTION[i] = dir[i];
	  power[i] = STARTPWM[0][i];
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
void Rover::startEngine(int MODE){
  for(int i=0; i<4;i++){
	analogWrite (MOTOR[i], STARTPWM[MODE][i]);
	Serial.println(power[i]);
  }
}
void Rover::adjustEnginePower(int motor, int pwr){
	analogWrite (MOTOR[motor], power[motor] += pwr);
	//Serial.println(power[motor]);
}
/*void Rover::speedUD(int x){
  analogWrite (MOTOR1, power[0]+=x);
  analogWrite (MOTOR2, power[1]+=x);
  analogWrite (MOTOR3, power[2]+=x);
  analogWrite (MOTOR4, power[3]+=x);
}*/
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
