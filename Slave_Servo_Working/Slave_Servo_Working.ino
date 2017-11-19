#include <SoftwareSerial.h>
#include <Servo.h>

#define VoltageSensor A0
#define ESCConteroller 9

SoftwareSerial BTserial(10,11); // enter the correct number
Servo ESC; 

int servoSpeed = 90, //rest position of motor
    curVal = 90, //current value of the potentiomter
    brakeSpeed = 1,
    currentSpeed=0,
    receivedValue;

/*
 * check and send battery level to the master arduino
 */
void sendBatteryLevel(){
  int voltageSensorValue = analogRead(VoltageSensor);
  float voltage = map(voltageSensorValue, 0, 1023.0, 0.0, 5.0); 
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

/**
 * send mappedSpeedValue to ESC
*/
void accelerate(int mappedSpeedValue){
  while(currentSpeed < mappedSpeedValue){
    currentSpeed += 1;
    ESC.write(currentSpeed);
    delay(1000);
  }
  return; 
}

/**
 * send mappedSpeedValue to ESC
*/
void deaccelerate(int mappedSpeedValue){
  while(currentSpeed > mappedSpeedValue){
    currentSpeed -= 1;
    ESC.write(currentSpeed);
    delay(1000);
  }
  return; 
}

/**
 * stop the longboard. brake at a constant deacceleration value
*/
void stop(){
  while(currentSpeed >= 0){
    currentSpeed -= 1;
    ESC.write(currentSpeed);
    delay(1000);
  }
  return; 
}

void setup() {
  Serial.begin(9600);
  BTserial.begin(38400); // Default communication rate of the Bluetooth module
  ESC.attach(ESCConteroller); // connect to ESC
}

void loop() {

  if(BTserial.available()>0){
      receivedValue = BTserial.read();
      Serial.println(receivedValue);
  }

  if(receivedValue>currentSpeed){
    accelerate(receivedValue);
    return;
  }

  if(receivedValue< currentSpeed && receivedValue> 0 ){
    deaccelerate(receivedValue);
    return;
  }

  if(receivedValue == 0){
    stop();
    return;
  }
  sendBatteryLevel();
}

