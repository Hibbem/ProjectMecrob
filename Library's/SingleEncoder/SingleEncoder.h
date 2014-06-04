#ifndef SingleEncoder_h
#define SingleEncoder_h

#include "Arduino.h"
static int anaPinA; //allemaal static, want wordt gebruikt in isr
static int anaPinB;
static int tics = 166; //in datasheet van encoder
static void updateEnc1();
static void updateEnc2();
static volatile long encPos[4] = {0,0,0,0}; //volatile, want wordt aangepast in isr
static volatile long lastPos[4] = {0,0,0,0};
static volatile float rpmPos[4] = {0,0,0,0};
static volatile boolean lastEncPos[2] = {true,true};
static volatile boolean isNewRPM = true;
static volatile long lastTime = 0;
static volatile int counter = 0;

class SingleEncoder
{
  public:
    SingleEncoder(uint8_t interrupt1, uint8_t interrupt2, uint8_t analog1,uint8_t analog2);
	long* readEnc();
	float* readRPM();
  private:
	void init_Timer();
	int intPinA;	
	int intPinB;
	int interrupt1;
	int interrupt2; 
	int analog1;
	int analog2;
};

#endif
