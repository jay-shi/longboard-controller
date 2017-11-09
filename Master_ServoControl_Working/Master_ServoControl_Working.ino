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
#define CompletelyStopValue 5

SoftwareSerial BTserial(10, 11);
bool pushButtonState = 0;
int currentSpeed;
void setup() {

  Serial.begin(9600); //Sets the data rate in bits per second (baud) for serial data transmission
  BTserial.begin(38400);

  pinMode(LED1, OUTPUT); 
  pinMode(PushButton, INPUT); 

  digitalWrite(LED1, HIGH); 
  digitalWrite(LED2, HIGH); 
  digitalWrite(LED3, HIGH); 
}

/*
 * sends value to Slave arduino via Bluetooth
 */
void sendToSlave(int speed){
  BTserial.write(speed);
  return;
}

/**
 * check if button is being pressed
 */
bool checkButtonState(){
  return  analogRead(PushButton);
}

/**
 * check if longboard needs accleration
*/
bool checkAccelerationState(int mappedValue){
  return mappedValue >= NaturalStateMax;
}

/**
 * check if longboard needs brake
*/
bool checkBrakeState(int mappedValue){
  return (mappedValue <= NaturalStateMin)&&(mappedValue >= CompletelyStopValue);
}


/**
 * check if longboard needs completely stop
*/
bool checkStopState(int mappedValue){
  return mappedValue < CompletelyStopValue ;
}


/**
 * functions that reads off the wanted speed from controller
 */
int mappedValuetoSpeed(int mappedValue){
  int mappedSpeed = map(mappedValue, 100, 180 , 0, 180); // map potentiometer value to 0-180 for ESC
  return mappedSpeed;
}

/**
 * functions that get mappedValue from controller
 */
int getMappedPotentiometerValue(){
  int potValue = analogRead(Potentiometer); // reads potentiometer value
  int mappedValue = map(potValue, 0 , 1023, 0, 180); // map potentiometer value to 0-180 for ESC
  return mappedValue;
}

/*
 * check battery level
 */
void displayBatteryLevel(){
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

  int mappedValue = getMappedPotentiometerValue();
  bool buttonPressed = checkButtonState();
  bool accelerationModeOn= checkAccelerationState(mappedValue);
  bool brakeModeOn = checkBrakeState(mappedValue);
  bool stopModeOn = checkStopState(mappedValue);

  // accelerates
  while(buttonPressed && accelerationModeOn){
    mappedValue = getMappedPotentiometerValue();
    int mappedSpeed = mappedValuetoSpeed(mappedValue);
    sendToSlave(mappedSpeed);
    buttonPressed = checkButtonState();
    displayBatteryLevel();
    stopModeOn = false;
    delay(500);
  }

  // brake
  while(brakeModeOn){
    sendToSlave(-10);
    brakeModeOn = checkBrakeState(mappedValue);
    delay(500);
  }

  // stop
  if(stopModeOn || !buttonPressed){
    sendToSlave(0);
  }  

} // loop ends here 
