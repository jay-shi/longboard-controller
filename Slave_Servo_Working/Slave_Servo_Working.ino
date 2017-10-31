#include <SoftwareSerial.h>
#include <Servo.h>
#define voltageSensor A0,
        ESCConteroller 9;

SoftwareSerial BTserial(11,10);
Servo ESC; 

int servoSpeed = 90; //rest position of motor
int curVal = 90; //current value of the potentiomter
int brakeSpeed = 1; 
int buttonTerminate = 0; 

/*
 * check and send battery level
 */
void function sendBatteryLevel(){
  int voltageSensorValue = analogRead(voltageSensor);
  float voltage = voltageSensorValue * (5.0/1023.0); 
  if(voltage > 4.25){
    BTserial.write(3); 
    return;
  }
  if(voltage > 4.05){
    BTserial.write(2); 
    return;
  }

  BTserial.write(1);
  return;
}

void function accelerate(){
  // implement functions that accelerate esc
}

void function deaccelerate(){
  // implement functions that deaccelerate esc
}

void function defaultBrake(){

}

void function cruiseMode(){

}

void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission
  BTserial.begin(38400); // Default communication rate of the Bluetooth module
  ESC.attach(ESCConteroller); 
}

void loop() {
  if(BTserial.available()>0){
    while(curVal < servoSpeed && buttonTerminate == 0){
      servoSpeed = BTserial.read();
      curVal = curVal+1;
      ESC.write(curVal); 
      delay(50);
//    Serial.println(curVal);
    }

    while(curVal > servoSpeed && servoSpeed < 81 && ttonTerminate == 0){
      
        servoSpeed = BTserial.read();
//          Serial.println(servoSpeed); 
//          Serial.println(curVal);
          if(servoSpeed > -1){
            brakeSpeed = -(9.0/79.0)*servoSpeed + 10.1139241;
          }else if(servoSpeed == -10){
              brakeSpeed = 5; 
              while(curVal > 82){
                  curVal = curVal - brakeSpeed;
                }
              buttonTerminate = 1; 
          }
          curVal = curVal - brakeSpeed;
          if (curVal < 82){ 
            curVal = 82;
          }
          ESC.write(curVal);
          delay(50); 
    }
//    Serial.println(curVal);
    servoSpeed = BTserial.read();

  }


  sendBatteryLevel();
  delay(50);
  
}

