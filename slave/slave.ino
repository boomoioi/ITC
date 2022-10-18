#include <Wire.h>
#define SLAVE_ADDR 9

#define MAX_MESSAGE_LENGTH 255
static char message[MAX_MESSAGE_LENGTH];
static unsigned int message_pos= 0;
int LED = 13;
int rd;   // Variable for received data
int br;   // Variable for blink rate

void setup() {
  pinMode(LED, OUTPUT);
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void receiveEvent() {
  rd= Wire.read();   
  Serial.println(char(rd));
}

void loop() {
  delay(50);
  br= map(rd, 1, 255, 100, 2000);    
  digitalWrite(LED, HIGH);
  delay(br);
  digitalWrite(LED, LOW);    
  delay(br);
}
