#include <Servo.h>

#define ESCConteroller 9

Servo ESC; 

void setup(){
    ESC.attach(ESCConteroller);
    Serial.begin(9600);
}
void loop(){
//    if(Serial.available()>0){
//        char input = Serial.read();
//        if(input == 'a'){
//          ESC.write(105);
//        }else if(input == 'b'){
//          ESC.write(110); 
//        }else if(input == 'c'){
//          ESC.write(120);  
//        }else if(input == 'd'){
//          ESC.write(150);
//        }else if(input=='e'){
//          ESC.write(180);
//        }else if(input == 's'){
//          ESC.write(160);
//        }else{
//          ESC.write(0);  
//        }
//        Serial.println(input);
//    }

      if(Serial.available()>0){
        char input = Serial.read();
        if(input == 's'){
           for(int i= 90; i< 180; i++){
            Serial.println("now runnning at");
            Serial.println(i);
            ESC.write(i);
            delay(4000);
           }
        }else{
          ESC.write(0);
        }
      }
}
