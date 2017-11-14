#include <Servo.h>

#define ESCConteroller 9

Servo ESC; 

void setup(){
    ESC.attach(ESCConteroller);
    Serial.begin(9600);
}
void loop(){
    if(Serial.available()){
        ESC.write(Serial.read()); // argument ranges from 0-180
    }
}