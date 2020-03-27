#include "pneumaticslib.h"
void setup() {
  initializePins();
}

void loop() {
buttonRead();
pressureControl();
 // Serial.println(pressure);
if (button1==0);
{
  digitalWrite(2,HIGH);
  analogWrite(3,125);
}
if (button1==1)
{
  digitalWrite(2,LOW);
  analogWrite(3,0);
}


  if (button2==0){
    digitalWrite(5,HIGH);
  }
  if (button2==1){
    digitalWrite(5,LOW);
  
  }

   if (button3==0){
    digitalWrite(4,HIGH);
    analogWrite(6,255);
  }
  if (button3==1){
    digitalWrite(4,LOW);
    analogWrite(6,0);
  
  }
}
