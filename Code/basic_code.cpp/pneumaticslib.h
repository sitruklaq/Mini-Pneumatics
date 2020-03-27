#define pneumaticslib.h
#include "Arduino.h"

int pressureInput;
float pressure;
const int valves[3]={2,4,5};
const int pumps [2]={3,6};
int button1;
int button2;
int button3;
int button4;

void initializePins(){
  pinMode(2, OUTPUT); 
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(9,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP); 
pinMode(11,INPUT_PULLUP); 
pinMode(12,INPUT_PULLUP);
Serial.begin(9600);
}

void buttonRead(){
 button1= digitalRead(9);
button2= digitalRead(10);
button3= digitalRead(11);
button4= digitalRead(12);
  
}
void pressureControl(){
pressureInput=analogRead(A2);
  float voltage = map(pressureInput, 0, 1023, 0, 5000);
  pressure = 50 * (voltage / 1000) - 125.6;
}
