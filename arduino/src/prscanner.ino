#include <Servo.h>

Servo servo;
int running = 0;
int sensorValue = 0;
int angle = 0;
int delta = 1;
int switchState = 0;
int lastSwitchState = 0;

void reset() {
   angle = 0;
   delta = 1;
   servo.write(0);
   running = 0;
   delay(100);
}

void setup() {
   Serial.begin(9600);
   servo.attach(9);
   pinMode(8, INPUT);
   reset();
}


void printValue(char *tag,int value) {
   Serial.print("\"");
   Serial.print(tag);
   Serial.print("\":\"");
   Serial.print(value);
   Serial.print("\"");
}

void loop() {

   switchState = digitalRead(8);

   if(switchState ^ lastSwitchState) {
      if(running && switchState) {
         reset();
      } else if(!running && switchState ) {
         running = 1;
      }
   }
   lastSwitchState = switchState;


   if(running) {
      sensorValue = analogRead(A1);

      Serial.print("{");
      printValue("angle",angle);
      Serial.print(",");
      printValue("value",sensorValue);
      Serial.println("}");

      if(angle+delta>=180-1 || angle+delta<=0)
         delta *= -1;
      angle += delta;

      servo.write(angle);
   }

   delay(20);
}
