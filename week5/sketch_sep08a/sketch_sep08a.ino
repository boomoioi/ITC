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
int randomNo;
int number[10] = {B11000000, B11111001, B10100100, B10110000, B10011001, B10010010, B10000010, B11111000, B10000000, B10010000};
int WL[2] = {B11000010, B11110001};
const int segPin[8] = {a,b,c,d,e,f,g,dp};


void setup() {
  Serial.begin(9600);
  pinMode(SA, INPUT);
  pinMode(SB, INPUT);
  randomSeed(analogRead(A0));
  randomNo= random(0, 9);
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
        for (int segment = 0; segment < 8; segment++){  
          isBitSet= bitRead(number[i], segment);
          digitalWrite(segPin[segment], isBitSet);  
        } 
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
        if(i>randomNo){
          for (int segment = 0; segment < 8; segment++){  
            isBitSet= bitRead(WL[0], segment);
            digitalWrite(segPin[segment], isBitSet);  
          } 
        } else if(i<randomNo){
          for (int segment = 0; segment < 8; segment++){  
            isBitSet= bitRead(WL[1], segment);
            digitalWrite(segPin[segment], isBitSet);  
          } 
        } else {
          for (int segment = 0; segment < 8; segment++){  
            isBitSet= bitRead(number[0], segment);
            digitalWrite(segPin[segment], isBitSet);  
            randomNo= random(0, 9);
          } 
        }
      }
    }
  }
  lastButtonStateB= readingB;

} 
