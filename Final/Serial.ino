  void readInstructions(){
    if (Serial.available()) {
        char signal = Serial.read();
        Serial.print("I received: ");
        Serial.println(signal);
          rover.startEngine();
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
          case 'w':
            rover.tankLeft();
            break;
          case 'c':
            rover.tankRight();
            break;
          case 't':
            rover.leftForward();
            break;
          case 'u':
            rover.rightForward();
            break;
          case 'v':
            rover.leftBackward();
            break;
          case 'n':
            rover.rightBackward();
            break;     
          case 'x':
            rover.stopEngine();
            break;
          case 'm':
            rover.startEngine();
            break; 
          case '1':
            rover.stopEngine();
            rover.setEngineMode(MODE_LOW);
            break;
          case '2':
            rover.stopEngine();
            rover.setEngineMode(MODE_MED);
            break;
          case '3':
            rover.stopEngine();
            rover.setEngineMode(MODE_HIGH);
            break;    
          default:
            Serial.println("No predefined command found");
        }
    }
  }
