#include "pneumaticslib.h"
#include <ezButton.h>

 
void setup() {
  initializePins();
 
  
  
  
}

void loop() {
  
buttonRead();
pressureControl();
if (pressure>100 || pressure<-80){
  emergencyVent();
}
recvWithStartEndMarkers();
if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        act_on_input();
        newData = false;    
}

}
