/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
#define DIRECTION1 11
#define MOTOR1 10 

#define DIRECTION2 8
#define MOTOR2 9

#define DIRECTION3 4
#define MOTOR3 5

#define DIRECTION4 7
#define MOTOR4 6

Encoder encOne(2, A1);
Encoder encTwo(3, A2);
Encoder encThree(13, A3);
Encoder encFour(12, A4);
long startTime, newTime;
const int STARTPOWER=200;
//short power1 = power, power2 = power ,power3 = power,power4 = power;
int power[4];
long positionOne  = -999;
long positionTwo = -999;
long positionThree = -999;
long positionFour = -999;
long rpmPosOne,rpmPosTwo,rpmPosThree,rpmPosFour;
boolean isRPM = true;
//RPM met 4 bijhoorende PWM
const int SPEED_LOW = 30;
const int SPEED_MED = 60;
const int SPEED_HIGH = 90;
int servoSpeed = SPEED_LOW;
//startpwm = berekend
const int STARTPWM[3][4] = {{30,30,38,40},{56,58,73,73},{104,109,139,132}};

void stopEngine(){
  analogWrite (MOTOR1, 0);
  analogWrite (MOTOR2, 0);
  analogWrite (MOTOR3, 0);
  analogWrite (MOTOR4, 0);
}
void startEngine(){
  analogWrite (MOTOR1, power[0]);
  analogWrite (MOTOR2, power[1]);
  analogWrite (MOTOR3, power[2]);
  analogWrite (MOTOR4, power[3]);
}
void speedUD(int x){
  analogWrite (MOTOR1, power[0]+=x);
  analogWrite (MOTOR2, power[1]+=x);
  analogWrite (MOTOR3, power[2]+=x);
  analogWrite (MOTOR4, power[3]+=x);
}
void tankRight(){
  digitalWrite (DIRECTION1, 0); 
  digitalWrite (DIRECTION2, 1); 
  digitalWrite (DIRECTION3, 1); 
  digitalWrite (DIRECTION4, 0); 
}
void tankLeft(){
  digitalWrite (DIRECTION1, 1); 
  digitalWrite (DIRECTION2, 0); 
  digitalWrite (DIRECTION3, 0); 
  digitalWrite (DIRECTION4, 1);
}
void crapRight(){
  digitalWrite (DIRECTION1, 0); 
  digitalWrite (DIRECTION2, 1); 
  digitalWrite (DIRECTION3, 0); 
  digitalWrite (DIRECTION4, 1); 
}
void crapLeft(){
  digitalWrite (DIRECTION1, 1); 
  digitalWrite (DIRECTION2, 0); 
  digitalWrite (DIRECTION3, 1); 
  digitalWrite (DIRECTION4, 0); 
}
void moveForward(){
  digitalWrite (DIRECTION1, 1); 
  digitalWrite (DIRECTION2, 1); 
  digitalWrite (DIRECTION3, 0); 
  digitalWrite (DIRECTION4, 0); 
}
void moveBackward(){
  digitalWrite (DIRECTION1, 0); 
  digitalWrite (DIRECTION2, 0); 
  digitalWrite (DIRECTION3, 1); 
  digitalWrite (DIRECTION4, 1);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Test:");
  pinMode (MOTOR1, OUTPUT);
  pinMode (DIRECTION1, OUTPUT);
  pinMode (MOTOR2, OUTPUT);
  pinMode (DIRECTION2, OUTPUT);
  pinMode (MOTOR3, OUTPUT);
  pinMode (DIRECTION3, OUTPUT);
  pinMode (MOTOR4, OUTPUT);
  pinMode (DIRECTION4, OUTPUT);
  for(int i = 0;i<5;i++){
   power[i] = STARTPWM[0][i];
  }
  startTime = millis();
  startEngine();
  moveForward();
}

void loop() {
  long newOne = encOne.read();
  long newTwo = encTwo.read();
  long newThree = encThree.read();
  long newFour = encFour.read();
  
  if(isRPM){
    rpmPosOne = newOne;
    rpmPosTwo = newTwo;
    rpmPosThree = newThree;
    rpmPosFour = newFour;
    isRPM= false;
  }
  
  if (newOne != positionOne || newTwo != positionTwo || newThree != positionThree || newFour != positionFour ) {
    long currentTime = millis();
    long deltaTime = currentTime-startTime;
    //Serial.println(deltaTime);
    if(deltaTime>1000){
      long deltaPos[4];
      deltaPos[0] = newOne - rpmPosOne;  
      deltaPos[1] = newTwo - rpmPosTwo; 
      deltaPos[2] = newThree - rpmPosThree; 
      deltaPos[3] = newFour - rpmPosFour;
      // 1 volledige tour = 330 pulsen en 166.5 mm
      float rpmServo[4];
      for(int i = 0; i<5;i++){
              rpmServo[i] = (((float)abs(deltaPos[i])/deltaTime)*60000)/330;        
      }
/*
      float rpmServo[0] = (((float)abs(deltaPosOne)/deltaTime)*60000)/330;
      float rpmThree[2] = (((float)abs(deltaPosThree)/deltaTime)*60000)/330;
      float rpmFour[3] = (((float)abs(deltaPosFour)/deltaTime)*60000)/330;
      */
      for(int i=0;i<5;i++){
        
        if((rpmServo[i]+1)<servoSpeed){
          power[i]+=3;
          startEngine();
          Serial.println();
          Serial.print(i);
          Serial.print(" is omhoog gegaan en is nu: ");
          Serial.println(power[i]);
        }else if(rpmServo[i]>(servoSpeed+1)){
          power[i]-=3;
          startEngine();
          Serial.println();
          Serial.print(i);
          Serial.print(" is omlaag gegaan en is nu: ");
          Serial.println(power[i]);
        }
     }
   
      Serial.print("RPMOne = ");
      Serial.print(rpmServo[0]);
      Serial.print(" - RPMTwo = ");
      Serial.print(rpmServo[1]);
      Serial.print(" - RPMThree = ");
      Serial.print(rpmServo[2]);
      Serial.print(" - RPMFour = ");
      Serial.println(rpmServo[3]);
      
      Serial.print("PosOne = ");
      Serial.print(newOne);
      Serial.print(", PosTwo = ");
      Serial.print(newTwo);
      Serial.print(", PosThree = ");
      Serial.print(newThree);
      Serial.print(", PosFour = ");
      Serial.println(newFour);
      isRPM = true;
      startTime= millis();
    }
    positionOne = newOne;
    positionTwo = newTwo;
    positionThree = newThree;
    positionFour = newFour;
    
  }

  if (Serial.available()) {
    char signal = Serial.read();
    Serial.print("I received: ");
    Serial.print(signal);
     switch (signal) {
    case 'z':
      moveForward();      
      break;
    case 'q':
      crapLeft();
      break;
    case 'd':
      crapRight();
      break;
    case 's':
      moveBackward();
      break;
    case 'e':
      servoSpeed = SPEED_LOW;
      for(int i = 0;i<5;i++){
        power[i]=STARTPWM[0][i];
      }
      startEngine();
      Serial.println();
      Serial.print("LOW --> PWM is nu : ");
      Serial.println(power[3]);
      break;
      break;
    case 'a':
      servoSpeed = SPEED_HIGH;
      for(int i = 0;i<5;i++){
        power[i]=STARTPWM[2][i];
      }
      startEngine();
      Serial.println();
      Serial.print("HIGH --> PWM is nu : ");
      Serial.println(power[3]);
      break;
    case 'r':
      servoSpeed = SPEED_MED;
      for(int i = 0;i<5;i++){
        power[i]=STARTPWM[1][i];
      }
      startEngine();
      Serial.println();
      Serial.print("MED --> PWM is nu : ");
      Serial.println(power[3]);
      break;
    break;
    case 'x':
      stopEngine();
      break;
    case 'w':
      tankLeft();
      break;
    case 'c':
      tankRight();
      break;
    case 'm':
      startEngine();
      break;
    case '1':
      analogWrite (MOTOR1, power[0]++);
      break;
    case '2':
      analogWrite (MOTOR2, power[1]++);
      break;
    case '3':
      analogWrite (MOTOR3, power[2]++);
      break;
    case '4':
      analogWrite (MOTOR4, power[3]++);
      break;
    default:
      Serial.println("Reset both knobs to zero");
      encOne.write(0);
      encTwo.write(0);
      encThree.write(0);
      encFour.write(0);
  }
    
  }
}
