#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);

static const LED1 7,
        LED2 8,
        LED3 9,
        pushButtonPin 5, // cruise button
        potentiometer A0, // potentiometer
        naturalStateMin = 80, // min degree of natural state of potentiometer
        naturalStateMax = 100;

int potValue =0; // potentiometer value
int potValueMapped = 0;
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
 * controls acceleration
 */
void function acceleration(){

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
void function checkBatteryLevel(int mappedPotValue){
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

  potValue = analogRead(A0); 
  potValueMapped = map(potValue, 0, 1023, 0, 179);
  pushButtonState = digitalRead(pushButtonPin); 

  checkBatteryLevel(potValueMapped);

  /**
   * implement functions that decide which type of brake to use here
  */
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


