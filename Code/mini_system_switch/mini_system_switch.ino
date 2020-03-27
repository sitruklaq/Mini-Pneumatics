char incomingByte;
int safety = 0;
int safety2 = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode( 10, OUTPUT);
pinMode(12,INPUT_PULLUP);
int buttonValue = digitalRead(12);
 pinMode(12, INPUT_PULLUP);
 pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
   int sensorVal = digitalRead(12);
   Serial.println(sensorVal);
  
  if (Serial.available() > 0) {
    incomingByte = Serial.read();



    if (incomingByte == '1') {
     
    }

    if (incomingByte == '2') {

      digitalWrite(10, HIGH);
      delay(75);
      digitalWrite(10, LOW);
      
      safety = 0;

    }
    if (incomingByte =='3'){
      for (int i=0; i<200;i++){
        analogWrite(5, 200);
        analogWrite(6, 0);
        delay(100);
        digitalWrite(5, 0);
        analogWrite(6, 0);
        safety = 1;
        digitalWrite(10, HIGH);
      delay(75);
      digitalWrite(10, LOW);
      safety = 0;
      }
    }
    if (incomingByte == '4') {
      if (safety == 1) {
        Serial.print("Safety is on!");
        Serial.println();

      }
      else {
        analogWrite(5, 100);
        analogWrite(6, 0);
        delay(100);
        digitalWrite(5, 0);
        analogWrite(6, 0);
        safety = 1;
      }
    }


   

  }
  if (sensorVal == HIGH) {
  if (safety == 1){
    
    digitalWrite(10, HIGH);
      delay(100);
      digitalWrite(10, LOW);
     
      safety = 0;
  }
     else{
      
     }
  } else {
     if (safety == 1) {
        Serial.print("Safety is on!");
        Serial.println();

      }
      else {
        analogWrite(5, 255);
        analogWrite(6, 0);
        delay(300);
        digitalWrite(5, 0);
        analogWrite(6, 0);
        safety = 1;
      }
  }
}
