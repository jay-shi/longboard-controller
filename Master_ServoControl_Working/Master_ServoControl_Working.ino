#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);

#define LED1 7 
#define LED2 8
#define LED3 9 
#define BUTTON 6 
#define pushButtonPin 5

int potValue =0; // potentismeter value
int potValueMapped = 0;
bool buttonState;
bool pushButtonState = 0, buttonPressed = 0;
int batteryLevel = 3; 
float voltage; 

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
  
}


