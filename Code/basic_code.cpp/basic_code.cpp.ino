#include "pneumaticslib.h"
void setup() {
  initializePins();
}

void loop() {
buttonRead();
pressureControl();
  Serial.println(pressure);
if (button1==0);
{
  digitalWrite(2,HIGH);
  analogWrite(3,200);
}
if (button1==1)
{
  digitalWrite(2,LOW);
  analogWrite(3,0);
}
    
}
