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

bool buttonState;
bool pushButtonState = 0;
bool buttonPressed = 0;
bool defaultBrakeState = 0; // brake state for brake mode
bool slowdownFlag = false;
bool cruiseMode = false; 


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
 * sends acceleration to Bluetooth
 */
void function sendSpeedValue(){
  int speed = getSpeedFromPotentiometer();
  BTserial.write(speed);
  return;
}

/*
 * sends acceleration to Bluetooth
 */
void function sendDeaccelerationValue(){

}

/**
 * get how long the longboard should deaccelerates/brake
 */
int function getBrakingTime(){

}

void function sendStop(){

  // implement function that sends stop signal to the BT
}

bool function getButtonSignal(){
  bool buttonPushed = analogRead(PushButton);
  return buttonPushed;
}

bool function checkIfCruiseMode(){
  return getButtonSignal();
}

/**
 * implement functions that reads off the wanted speed from controller
*/
int function getSpeedFromPotentiometer(){
  int potValue = analogRead(Potentiometer); // reads potentiometer value
  int mappedSpeed = map(potValue, 0, 1023, 0, 179); // map potentiometer value to 0-180 for ESC
  pushButtonState = digitalRead(pushButtonPin); 
  return mappedSpeed;
}

/*
 * check if potentiometer is pressed down
 * if yes, brake
 */
void function defaultBrake(int mappedPotValue){
      digitalWrite(LED1, LOW); 
      defaultBrakeState = true;
      for(int i=0; i<40; i++){
        BTserial.write(-10); 
        delay(50);
      }
      defaultBrakeState = false;
  }
  return;
}
/**
 * implement functions that does adjust to 
 * how much the potentiometer change here
 */
void function brake(int mappedPotValue){
    if(defaultBrakeState) return;
    /*
     * implement braking deaccelation value
     */
}

/*
 * check battery level
 */
void function displayBatteryLevel(int mappedPotValue){
  // wont check battery if the controller is in use
  if (mappedPotValue < naturalStateMin || potValueMapped > naturalStateMax){
      return;
  }
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

void function stopBraking(){

}

void loop() {

  checkBatteryLevel(potValueMapped);

  //implement functions that decide which type of brake to use here
  if(mappedPotValue < naturalStateMin) {
    defaultBrake();
    brake(mappedPotValue);
  };
  
  if(!buttonPressed){
    potValue = analogRead(potentiometer); 
    potValueMapped = map(potValue, 0, 1023, 0, 179); //still not sure why these values. 47 seems to be starting value for motor 
    BTserial.write(potValueMapped); 
//    Serial.println(potValueMapped); 
  }


  if(pushButtonState == 1){
    if(buttonPressed == 0){
      digitalWrite(LED1, LOW); 
      for(int i=0; i<40; i++){
        BTserial.write(-10); 
      }
      buttonPressed = 1; 
      delay(50); 
    } 
  }

  /*
   * if cruise button is pressed, check potentiometer value
   * if cruise button is pressed, it should keep constant speed
   * if cruise button is released, it should slow down
   */
  if(pushButtonState){
    slowdownFlag = false; 
  }
  

  // later get rid of if, since it complements the first scenerio
  if(!pushButtonState){
    slowdownFlag = true;
  }

  /*
   * send out slow down signal
   */
  if(slowdownFlag){

  }
  
} // loop ends here 


