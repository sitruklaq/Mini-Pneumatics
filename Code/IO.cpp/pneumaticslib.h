#define pneumaticslib.h
#include "Arduino.h"
#define OPEN 1
#define CLOSE 0
int pressureInput;
float pressure;
const int Valve[3]={2,4,5};
const int Pump[2]={3,6};
int button1;
int button2;
int button3;
int button4;

char valveRead[]= "V";
char pumpRead[] = "P";
char pressureRead[]= "PR";


const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;
boolean newData = false;


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

//---THIS FUNCTION TURNS ON/OFF A SPECIFIC VALVE
void setValve(int number, int position) {
//  Serial.println("valve function run");
  if (position == OPEN) {
    digitalWrite(Valve[number], HIGH);

  }

  if (position == CLOSE) {
    digitalWrite(Valve[number], LOW);
  }
}

//---THIS FUNCTION TURNS ON/OFF A SPECIFIC PUMP
void setPump(int number, int position) {
//  Serial.println("pump function run");
  if (position == OPEN) {
    analogWrite(Pump[number], 200);
 //   Serial.println("pump turn on");

  }

  if (position == CLOSE) {
    analogWrite(Pump[number], 0);
  //  Serial.println("pump turn off");
  }
}

void pressureControl(){
pressureInput=analogRead(A2);
  float voltage = map(pressureInput, 0, 1023, 0, 5000);
  pressure = 50 * (voltage / 1000) - 125.6;
}

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  integerFromPC = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  floatFromPC = atof(strtokIndx);     // convert this part to a float

}

// This section is looking for new serial inputs and parsing them
void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}
//============ This section acts 
void act_on_input() {
  if (strcmp(messageFromPC, valveRead) == 0) {
    setValve(integerFromPC, floatFromPC);
  //  Serial.println("data read");
  }
  if (strcmp(messageFromPC, pumpRead) == 0) {
    setPump(integerFromPC, floatFromPC);
  //  Serial.println("pump data read");
  }
  if (strcmp(messageFromPC, pressureRead) == 0) {
    Serial.println(pressure);
  }
  
}

