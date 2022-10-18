#include <Wire.h>
#define SLAVE_ADDR 9
#define MAX_MESSAGE_LENGTH 255
static char message[MAX_MESSAGE_LENGTH];
static unsigned int message_pos= 0;
int analogPin= A3;
int val= 0;
void setup() {
  // Initialize I2C communications as Master
  Wire.begin();
  Serial.begin(9600);
}

char* getChar(){
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
  return "";
}

void loop() {
  delay(50); 
  char* message = getChar();
  Serial.print(message);
  // Read pot value// Map to range of 1-255 for flash rate
  val= "Token#0#";
  // Write a charatreto the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(val);
  Wire.endTransmission();
}
