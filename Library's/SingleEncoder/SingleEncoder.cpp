#include "Arduino.h" 
#include "SingleEncoder.h"

void SingleEncoder::init_Timer(){
  cli();//stop interrupts
  //set timer2 interrupt at 1 kHz --> 1 msec
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 500hz increments
  OCR2A = 124;// = [(16*10^6) / (256*500)] - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS22 bit for 64 prescaler
  //TCCR2B |= (1 << CS22);
  //Set T2 256 prescaler
  TCCR2B = 1<<CS22 | 1<<CS21; 
  //TCCR2B |= (1<<CS22)  | (1<<CS20); // Set bits
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei();//allow interrupts 
}
void updateEnc1(){
  encPos[0]++;
}
void updateEnc2(){
  encPos[1]++;
}
SingleEncoder::SingleEncoder(uint8_t interrupt1, uint8_t interrupt2, uint8_t analog1,uint8_t analog2)
{
	intPinA = interrupt1;
	intPinB = interrupt2;
	anaPinA = analog1;
	anaPinB = analog2;
	pinMode(intPinA, INPUT);
	pinMode(intPinB, INPUT);
	attachInterrupt(0, updateEnc1, CHANGE); 
	attachInterrupt(1, updateEnc2, CHANGE);
	init_Timer();	
}

long* SingleEncoder::readEnc(){
	return (long*)encPos;
}
float* SingleEncoder::readRPM(){
	return (float*)rpmPos;
}

ISR(TIMER2_COMPA_vect){ //wordt elke 2ms getriggerd --> per += 100 ms rpm lezen
  counter++;
  if(isNewRPM){
	memcpy((void*)lastPos,(void*) encPos, sizeof(encPos));
	isNewRPM = false;
  }
  bool read3 = digitalRead(anaPinA);
  bool read4 = digitalRead(anaPinB);
  if(lastEncPos[2] != read3){
	 encPos[2]++;
  }
  lastEncPos[2] = read3;

  if(lastEncPos[3] != read4){
	 encPos[3]++;
   }
  lastEncPos[3] = read4;
  if(counter>50){
	long timeNow = millis();
	for(int i = 0; i<4;i++){
		rpmPos[i] = ((encPos[i]-lastPos[i])*((float)(60000/(timeNow-lastTime))))/tics;
	}
	lastTime = millis();
	counter = 0;
	isNewRPM=true;
  }
}