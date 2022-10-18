#include <Wire.h>
#define SLAVE_ADDR 9
#define MY_ADDR 1
#define MAX_MESSAGE_LENGTH 255

int analogPin= A3;
int rd;
int index = 0;

void setup() {
  // Initialize I2C communications as Master
  Serial.begin(9600);
  Wire.begin(MY_ADDR);
  Wire.onReceive(receiveEvent);
}

void receiveEvent() {
  rd= Wire.read();   
  Serial.println((char)rd);
}   


char* getChar(){
  static char message[MAX_MESSAGE_LENGTH];
  static unsigned int message_pos= 0;
  while (Serial.available() > 0){
    char inByte = Serial.read();
    if (inByte  != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1)){
      message[message_pos] = inByte;
      message_pos++;
    } else {
      message[message_pos] = '\0';
      message_pos= 0;
      return message;
   }
  }
  return "\0";
}

void loop() {
  delay(50);
  index = 0; 
  char* message = getChar();
  Serial.print(message);
  // Read pot value// Map to range of 1-255 for flash rate
  // Write a charatreto the Slave
  while(message[index] != '\0'){
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(message[index]);
    Wire.endTransmission();
    index++;
  }
  
  
}
