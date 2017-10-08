#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);

#define LED1 7 
#define LED2 8
#define LED3 9 
#define BUTTON 6 // potentiometer
#define pushButtonPin 5 // cruise button

int potValue =0; // potentiometer value
int potValueMapped = 0;
bool buttonState;
bool pushButtonState = 0;
bool buttonPressed = 0;
int batteryLevel = 3; 
float voltage; 
bool slowdownFlag = false;

void setup() {

  Serial.begin(9600);
  BTserial.begin(38400);

  pinMode(LED1, OUTPUT); 
  pinMode(BUTTON, INPUT); 
  pinMode(pushButtonPin, INPUT); 

  digitalWrite(LED1, HIGH); 
  digitalWrite(LED2, HIGH); 
  digitalWrite(LED3, HIGH); 
}


/*
 * sends out bluetooth signal to slave
 * params: potentiometer input value
 */
function sendSignalToSlave(int potentiometerValue){
  // mapping potentiometer value to degrees
  int potValueMapped = map(potentiometerValue, 0, 1023, 0, 179);
  BTserial.write(potValueMapped);
}

/*
 * controls acceleration
 */
function acceleration(){

}

/*
 * controls deacceleration
 */
function deacceleration(){

}

/*
 * 
 */
function checkBrake(int potentiometerValue){
  // check if potentiometer is pressed down
  // if yes, brake
  if(potentiometerValue < 80/180*1023 ) {
    sendSignalToSlave( potentiometerValue)
  }
}

void loop() {

  if(!buttonPressed){
    potValue = analogRead(A0); 
    potValueMapped = map(potValue, 0, 1023, 0, 180); //still not sure why these values. 47 seems to be starting value for motor 
 
    BTserial.write(potValueMapped); 
//    Serial.println(potValueMapped); 
  }
  
  pushButtonState = digitalRead(pushButtonPin); 
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

  // the potentiometer natural state is around 80 to 90 degrees

  if (potValueMapped > 80 && potValueMapped < 90)
  {
    batteryLevel = BTserial.read();
    if(batteryLevel == 2){
      digitalWrite(LED1, LOW); 
    }    
    if(batteryLevel == 1){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW); 
    }
    
  } 
    delay(50); //changed from 50 to 10, might fix jerking issue 

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


