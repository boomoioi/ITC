#include <Wire.h>
#define SLAVE_ADDR1 8
char messageR[300];

void setup() {
  // Initialize I2C communications as Master
  Serial.begin(9600);
  Wire.begin();
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
  } else {
    char* normal = "Token#0#";
    for(int i=0; i<8; i++){
      messageR[i] = normal[i];
    }
    messageR[8]='\0';
  }
}

void request(){
  if(Wire.available() > 0){
    int i=0;
    while (Wire.available() > 0){
      int x = Wire.read();
      messageR[i] = (char)x;
      if(messageR[i] == '\0' || x==255){
        messageR[i] = '\0';
        break;
      }
      i++;
    }
  }
//  Serial.println(messageR);
  messageR[0] = '\0';
}


void loop() {
  
  getChar();
//  if(messageR[0] != '\0'){
//    Wire.beginTransmission(SLAVE_ADDR1);
//    Wire.write(messageR);
//    Wire.endTransmission();
//    messageR[0] = '\0';
//  }
//  delay(100);
//  Wire.requestFrom(8, 100);    // request 6 bytes from slave device #8
//  request();
//  delay(100);
  
}
