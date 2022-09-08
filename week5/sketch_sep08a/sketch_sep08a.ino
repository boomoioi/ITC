#define a
#define b
#define c
#define d
#define e
#define f
#define g
#define dp
const int segPin[8] = {a,b,c,d,e,f,g,dp};
void setup() {
  for(int i=0; i<8; i++){
    pinMode(segPin[i], OUTPUT);
  }
 }

 void loop() {
  sensorValue= analogRead(sensorPin);
  // read the value from the sensor:
  Serial.println(digitalRead(2));
  Serial.println(sensorValue);
  Serial.println("__________________________________________________");
  // turn the ledPinon
  
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);
  digitalWrite(ledPin, LOW);
  delay(sensorValue);
 }
