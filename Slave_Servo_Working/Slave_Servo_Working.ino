#include <SoftwareSerial.h>
#include <Servo.h>
#include <SoftwareServo.h>

SoftwareSerial BTserial(11,10); 
SoftwareServo ESC; 

Servo myServo; 
int servoSpeed = 90, servoSpeedTemp, servoSpeedTemp2; //rest position of motor
int curVal = 90; //current value of the potentiomter
int voltageSensorValue; 
int brakeSpeed = 1; 
int buttonTerminate = 0; 


/*
 * check and send battery level
 */
function sendBatteryLevel(){
  
  int voltageSensorValue = analogRead(A0);
  float voltage = voltageSensorValue * (5.0/1023.0); 

  if(voltage > 4.25){
    BTserial.write(3); 
    return;
  }else if(voltage > 4.05){
    BTserial.write(2); 
    return;
  }else{
    BTserial.write(1);
    return;
  }
}

void setup() {
  
  Serial.begin(9600);
  BTserial.begin(38400); 
  myServo.attach(9); 
  
}

void loop() {
  
  if(BTserial.available()>0){
    
    while(curVal < servoSpeed && buttonTerminate == 0){
      servoSpeed = BTserial.read();
      curVal = curVal+1;
      myServo.write(curVal); 
      delay(50);
//      Serial.println(curVal);
    }

    while(curVal > servoSpeed && servoSpeed < 81 && ttonTerminate == 0){
      
        servoSpeed = BTserial.read();
//          Serial.println(servoSpeed); 
//          Serial.println(curVal);
          if(servoSpeed > -1){
            brakeSpeed = -(9.0/79.0)*servoSpeed + 10.1139241;
          }
          
          else if(servoSpeed == -10){
              brakeSpeed = 5; 
              while(curVal > 82){
                  curVal = curVal - brakeSpeed;
                }
              buttonTerminate = 1; 
            }
      
          curVal = curVal - brakeSpeed;

          if (curVal < 82)
          { 
            curVal = 82;
          }
      
          myServo.write(curVal);
          delay(50); 
    }
//    Serial.println(curVal);
    servoSpeed = BTserial.read();

  }
  sendBatteryLevel();
  delay(50);
  
}

