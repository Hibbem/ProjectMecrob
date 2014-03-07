  void readInstructions(){
    if (Serial.available()) {
    char signal = Serial.read();
    Serial.print("I received: ");
    Serial.print(signal);
     switch (signal) {
    case 'z':
      rover.moveForward();      
      break;
    case 'q':
      rover.crapLeft();
      break;
    case 'd':
      rover.crapRight();
      break;
    case 's':
      rover.moveBackward();
      break;
    case 'e':
      /*servoSpeed = SPEED_LOW;
      for(int i = 0;i<5;i++){
        power[i]=STARTPWM[0][i];
      }
      startEngine();
      Serial.println();
      Serial.print("LOW --> PWM is nu : ");
      Serial.println(power[3]);
      break;*/
      break;
    case 'a':
      /*servoSpeed = SPEED_HIGH;
      for(int i = 0;i<5;i++){
        power[i]=STARTPWM[2][i];
      }
      startEngine();
      Serial.println();
      Serial.print("HIGH --> PWM is nu : ");
      Serial.println(power[3]);*/
      break;
    case 'r':/*
      servoSpeed = SPEED_MED;
      for(int i = 0;i<5;i++){
        power[i]=STARTPWM[1][i];
      }
      startEngine();
      Serial.println();
      Serial.print("MED --> PWM is nu : ");
      Serial.println(power[3]);*/
      break;
    case 'x':
      rover.stopEngine();
      break;
    case 'w':
      rover.tankLeft();
      break;
    case 'c':
      rover.tankRight();
      break;
    case 'm':
      rover.startEngine(SPEED_MED);
      break;
    /*case '1':
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
    default:*/
      Serial.println("Reset both knobs to zero");
      /*encOne.write(0);
      encTwo.write(0);
      encThree.write(0);
      encFour.write(0*/
  }
    }
  }
