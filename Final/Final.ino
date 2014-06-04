#include <Rover.h>
#include <SingleEncoder.h>

#define ENC1 2
#define ENC2 3
#define ENC3 A3
#define ENC4 A4
#define DIR1 11
#define DIR2 8
#define DIR3 4
#define DIR4 7
#define MOTOR1 10 
#define MOTOR2 9
#define MOTOR3 5
#define MOTOR4 6

int motors[4] = {MOTOR1,MOTOR2,MOTOR3,MOTOR4};
int dirs[4] = {DIR1, DIR2,DIR3, DIR4};

SingleEncoder enc(ENC1,ENC2,ENC3,ENC4);
Rover rover(motors,dirs);

unsigned long currentTime;
unsigned long loopTime;

void setup(){
  Serial.begin(115200);
  Serial.println("Finale Test ");
  loopTime = currentTime;
  //rover.startEngine();
}

void loop(){
   currentTime = millis();
   if(currentTime >= (loopTime + 2000)){
     long* a= enc.readEnc();
     int* b = rover.getPower();
     unsigned int k[4] = {1,2,3,4};
     float* d = enc.readRPM();
     for(int i = 0; i<4;i++){
       // Enc : encPos - Power - RPM
       Serial.print("Enc");Serial.print(i+1);Serial.print(" : ");Serial.print(a[i]);Serial.print(" - ");Serial.print(b[i]);Serial.print(" - ");Serial.print(d[i]);Serial.print("|");
     }     
     Serial.println();
     loopTime = currentTime; 
  }
  readInstructions();
}
