#include <SoftwareSerial.h>

SoftwareSerial BTserial(11,10); 

void setup() {
  Serial.begin(9600);
  BTserial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
  if(BTserial.available()>0){
      int receivedValue = BTserial.read();
      Serial.println(receivedValue);
  }
}

