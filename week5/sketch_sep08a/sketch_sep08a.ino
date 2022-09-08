#define a 5
#define b 4
#define c 9
#define d 10
#define e 11
#define f 6
#define g 7
#define dp 8
#define SA 13
#define SB 12
int buttonState, i=0;
int lastButtonState= LOW; 
long lastDebounceTime= 0;
long debounceDelay= 50;
int buttonStateB;
int lastButtonStateB= LOW; 
long lastDebounceTimeB= 0;
int number[10] = {B01000000, B01111001, B00100100, B00110000, B00011001, B00010010, B00000010, B01111000, B00000000, B00010000};
const int segPin[8] = {a,b,c,d,e,f,g,dp};


void setup() {
  Serial.begin(9600);
  pinMode(SA, INPUT);
  pinMode(SB, INPUT);
  for(int i=0; i<8; i++){
    pinMode(segPin[i], OUTPUT);
  }
}

void loop() {
  boolean isBitSet;
  int reading = digitalRead(SA);
  if (reading != lastButtonState) {
    lastDebounceTime= millis();
  }
  if ((millis()   - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState= reading;  
      if(buttonState == HIGH){
        i++;
        i = i%10;
      }
    }
  }
  lastButtonState= reading;

  int readingB = digitalRead(SB);
  if (readingB != lastButtonStateB) {
    lastDebounceTimeB= millis();
  }
  if ((millis()   - lastDebounceTimeB) > debounceDelay) {
    if (readingB != buttonStateB) {
      buttonStateB= readingB;  
      if(buttonStateB == HIGH){
        i++;
        i = i%10;
      }
    }
  }
  lastButtonStateB= readingB;
  

  Serial.println(i);
  for (int segment = 0; segment < 8; segment++){  
    isBitSet= bitRead(number[i], segment);
    digitalWrite(segPin[segment], isBitSet);  
  } 
} 
