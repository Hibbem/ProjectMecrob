#ifndef Rover_h
#define Rover_h

#include "Arduino.h"
const int SPEED_ZERO = 0;
const int SPEED_LOW = 30;
const int SPEED_MED = 60;
const int SPEED_HIGH = 90;
const int MODE_LOW = 0;
const int MODE_MED = 1;
const int MODE_HIGH = 2;
const int MOTOR_1 = 0;
const int MOTOR_2 = 1;
const int MOTOR_3 = 2;
const int MOTOR_4 = 3;
static volatile int _MODE = 0;
static volatile int power[4] = {0,0,0,0};
static int STARTPWM[3][4]={{60,32,40,44},{61,59,71,76},{107,111,155,140}}; //calculated

class Rover
{
  public:
    Rover(const int motor[4],const int dir[4]);
	int* getPower();
    void startEngine();
	//set incremental power
	void adjustEnginePower(int motor, int pwr);
	//set actual power
	void setEnginePower(int motor, int pwr);
	//set mode to all motors
	void setEngineMode(int MODE);
    void stopEngine();
    void tankRight();
    void tankLeft();
    void crapRight();
    void crapLeft();
    void moveForward();
    void moveBackward();
	void leftForward();
	void rightForward();
	void leftBackward();
	void rightBackward();
  private:
    int MOTOR[4],DIRECTION[4];
};

#endif
