/**
 * Author: @Jay Shi @Steven Kim @Josh Lee
 * this code is designed to control the controller of the longboard project.
 * the controller sends out desired speed value to the slave arduino.
 * the slave arduino will then send throttle value to the ESC to control the value of RPM of motor.
 * When potentiometer is pulled up, it will control the speed.
 * When the potentiometer is pulled down, it will cound how long the longboard should deaccelerates.
*/

#include <SoftwareSerial.h>

#define LED1 7
#define LED2 8
#define LED3 9
#define PushButton 5 // cruise button
#define Potentiometer A0 // potentiometer
#define NaturalStateMin 80 // min degree of natural state of potentiometer
#define NaturalStateMax 100

SoftwareSerial BTserial(10, 11);

bool pushButtonState = 0;
bool stopModeOn = false;
int currentSpeed;


void setup() {

  Serial.begin(9600); //Sets the data rate in bits per second (baud) for serial data transmission
  BTserial.begin(38400);

  pinMode(LED1, OUTPUT); 
  pinMode(pushButtonPin, INPUT); 

  digitalWrite(LED1, HIGH); 
  digitalWrite(LED2, HIGH); 
  digitalWrite(LED3, HIGH); 
}

/*
 * sends value to Slave arduino via Bluetooth
 */
void function sendToSlave(int speed){
  BTserial.write(speed);
  return;
}

/**
 * check if button is being pressed
 */
bool function checkButtonState(){
  return  analogRead(PushButton);
}

/**
 * functions that reads off the wanted speed from controller
 */
int function mapPotentiometerToSpeed(){
  int potValue = analogRead(Potentiometer); // reads potentiometer value
  int mappedSpeed = map(potValue, 570 , 1023, 0, 179); // map potentiometer value to 0-180 for ESC
  return mappedSpeed;
}

/**
 * functions that reads off the wanted speed from controller
 */
int function mapPotentiometerToSpeed(){
  int potValue = analogRead(Potentiometer); // reads potentiometer value
  int mappedSpeed = map(potValue, 570 , 1023, 0, 179); // map potentiometer value to 0-180 for ESC
  return mappedSpeed;
}

/*
 * stop the motor completely
 */
void function stopMotor(){
  digitalWrite(LED1, LOW); 
  sendToSlave(0);
  stopModeOn = true;
  return;
}

/*
 * check battery level
 */
void function displayBatteryLevel(int mappedPotValue){
  int batteryLevel = BTserial.read();
  if(batteryLevel == 2){
      digitalWrite(LED1, LOW); 
      return;
  }    
  if(batteryLevel == 1){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW); 
      return;
  }
}

void loop() {

  checkBatteryLevel(potValueMapped);
  bool buttonPressed = checkButtonState();
  int mappedValue = mapPotentiometer();
  if( mappedValue > NaturalStateMax){
    bool accelerationModeOn = true;
  }else if(mappedValue < NaturalStateMin){
    bool brakeModeOn = true;
  }else{
    //
  }
  while(buttonPressedOn && accelerationModeOn){

    currentSpeed = mappedValue();
    buttonPressed = checkButtonState();
  }

} // loop ends here 


