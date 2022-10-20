#include <Wire.h>
#define MY_ADDR 8


char messageR[300];

void setup() {
  Serial.begin(9600);
  Wire.begin(MY_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void receiveEvent(int howMany) {
  if(Wire.available() > 0){
    int i=0;
    while (Wire.available() > 0){
      messageR[i] = Wire.read();
      i++;
    }
    messageR[i] = '\0';
  }
}

void requestEvent(){
  Wire.write(messageR);
}

void getChar(){
  if(Serial.available() > 0){
    int i=0;
    while (Serial.available() > 0){
      int inByte = Serial.read();
      messageR[i] = (char)inByte;
      i++;
    }
    messageR[i-1] = '\0';
  }
}


void loop() {
  getChar(); 
  Serial.print(messageR);
}
