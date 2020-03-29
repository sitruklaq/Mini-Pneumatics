#define pneumaticslib.h
#include "Arduino.h"
#include <ezButton.h>
#define OPEN 1
#define CLOSE 0
#define DEBUG false // set this to true to output serial prints for debugging
#define DEBUG_SERIAL if(DEBUG)Serial
#define BUTTONS false //toggles the buttons
#define PPUMP 0
#define NPUMP 1
#define PVALVE 0
#define NVALVE 1
#define EVALVE 2
ezButton button1(9);  // create ezButton object that attach to pin 6;
ezButton button2(10);  // create ezButton object that attach to pin 7;
ezButton button3(11);  // create ezButton object that attach to pin 8;
ezButton button4(12);
int pressureInput;
float pressure;
const int Valve[3] = {2, 4, 5};
const int Pump[2] = {3, 6};


char valveRead[] = "V";
char pumpRead[] = "P";
char pressureRead[] = "PR";


const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;
boolean newData = false;


void initializePins() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13,OUTPUT);
 
   button1.setDebounceTime(25); // set debounce time to 50 milliseconds
  button2.setDebounceTime(25); // set debounce time to 50 milliseconds
  button3.setDebounceTime(25); // set debounce time to 50 milliseconds
 button4.setDebounceTime(25); // set debounce time to 50 milliseconds
 Serial.begin(9600);
  DEBUG_SERIAL.println("Initialized Pins");
}



  //---THIS FUNCTION TURNS ON/OFF A SPECIFIC VALVE
  void setValve(int number, int state) {
     DEBUG_SERIAL.println("valve function run");
    if (state == OPEN) {
      digitalWrite(Valve[number], HIGH);
      

    }

    if (state == CLOSE) {
      digitalWrite(Valve[number], LOW);
    }
  //  DEBUG_SERIAL.print("Valve:");
   // DEBUG_SERIAL.print(number);
   // DEBUG_SERIAL.print(" state");
   // DEBUG_SERIAL.println(state);
  }

  //---THIS FUNCTION TURNS ON/OFF A SPECIFIC PUMP
  void setPump(int number, int position) {
    DEBUG_SERIAL.println("pump function run");
    if (position == OPEN) {
      analogWrite(Pump[number], 200);
      //   Serial.println("pump turn on");

    }

    if (position == CLOSE) {
      analogWrite(Pump[number], 0);
      //  Serial.println("pump turn off");
    }
  }

  void pressureControl() {
    
    pressureInput = analogRead(A2);
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

  void inflate()
  {
    setValve(PVALVE,OPEN);
    setPump(PPUMP,OPEN);
    
  }


  void deflate() {
    setValve(NVALVE,OPEN);
    setPump(NPUMP,OPEN);
    
  }

  void exhaust() {
    setValve(EVALVE,OPEN);
  }
  void closeAll() {

  }

  void emergencyVent() {
    setValve(PVALVE, CLOSE);
    setValve(NVALVE, CLOSE);
    setValve(EVALVE, OPEN);
    setPump(PPUMP, CLOSE);
    setPump(NPUMP, CLOSE);
    digitalWrite(13, HIGH);
    delay(5000);
    digitalWrite(13, LOW);
    setValve(EVALVE, CLOSE);


  }
void buttonRead() {
  
   button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first
  button3.loop(); // MUST call the loop() function first
  button4.loop(); 


 //int btn1State = button1.getState();
 // int btn2State = button2.getState();
 // int btn3State = button3.getState();
 // int btn4State = button4.getState();
// Serial.print("button 1 state: ");
// Serial.println(btn1State);
//Serial.print("button 2 state: ");
// Serial.println(btn2State);
// Serial.print("button 3 state: ");
 //Serial.println(btn3State);
 // Serial.print("button 4 state: ");
 //Serial.println(btn4State);

  if(button1.isPressed()){
    DEBUG_SERIAL.println("The button 1 is pressed");
setValve(PVALVE,OPEN);
setPump(PPUMP,OPEN);
  }
  if(button1.isReleased()){
    DEBUG_SERIAL.println("The button 1 is released");
setValve(PVALVE,CLOSE);
setPump(PPUMP,CLOSE);
  }
  if(button2.isPressed()){
    DEBUG_SERIAL.println("The button 2 is pressed");
setValve(NVALVE,OPEN);
setPump(NPUMP,OPEN);
  }
  if(button2.isReleased()){
    DEBUG_SERIAL.println("The button 2 is released");
setValve(NVALVE,CLOSE);
setPump(NPUMP,CLOSE);
  }
  if(button3.isPressed()){
    DEBUG_SERIAL.println("The button 3 is pressed");
setValve(EVALVE,OPEN);
  }
  if(button3.isReleased()){
    DEBUG_SERIAL.println("The button 3 is released");
    setValve(EVALVE,CLOSE);
  }

}

