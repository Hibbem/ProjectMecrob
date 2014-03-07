#ifndef Rover_h
#define Rover_h

#include "Arduino.h"
const int SPEED_LOW = 30;
const int SPEED_MED = 60;
const int SPEED_HIGH = 90;
const int MOTOR_1 = 0;
const int MOTOR_2 = 1;
const int MOTOR_3 = 2;
const int MOTOR_4 = 3;
static volatile int power[4] = {0,0,0,0};
static int STARTPWM[3][4]={{30,30,38,40},{56,58,73,73},{104,109,139,132}}; //calculated

class Rover
{
  public:
    Rover(const int motor[4],const int dir[4]);
	int* getPower();
    void startEngine(int speed);
	void adjustEnginePower(int motor, int pwr);
    void stopEngine();
    void tankRight();
    void tankLeft();
    void crapRight();
    void crapLeft();
    void moveForward();
    void moveBackward();
    void speedUD(int x);
  private:
    int MOTOR[4],DIRECTION[4];
};

#endif
