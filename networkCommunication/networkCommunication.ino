#include <Wire.h>
#define SLAVE_ADDR1 8
char messageR[300];
char empty[10] = "Token#0#";
int mess = 0;

void setup() {
  // Initialize I2C communications as Master
  Serial.begin(9600);
  Wire.begin();
  setNormal();
}

void getChar(){
  while (Serial.available() > 0){
    char inByte = Serial.read();
    if(inByte != '\n'){
      messageR[mess] = (char)inByte;
      mess++;
    } else {
      messageR[mess] = '\0';
      mess = 0;
    }
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
  Serial.println(messageR);
  messageR[0] = '\0';
}

void setNormal(){
  for(int i=0; i<8; i++){
    messageR[i] = empty[i];
  }
  messageR[8] = '\0';
  
}


void loop() {
  
  getChar();
  delay(1000);
  if(messageR[0] != '\0'){
    Wire.beginTransmission(SLAVE_ADDR1);
    Wire.write(messageR);
    Wire.endTransmission();
    messageR[0] = '\0';
  }
  delay(1000);
  Wire.requestFrom(8, 100);    // request 6 bytes from slave device #8
  request();
  
}
