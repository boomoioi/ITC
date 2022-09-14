#define button1 12 // left
#define button2 11 // middle
#define button3 10 // right
#define LED3 4     // red
#define LED2 3     // yellow
#define LED1 2     // green
int startR = 0, startG = 0, startY = 0, subY = 0;
long debounceDelay= 50;

int buttonStateR;
int lastButtonStateR= LOW; 
long lastDebounceTimeR= 0;

int buttonStateG;
int lastButtonStateG= HIGH; 
long lastDebounceTimeG= 0;

int buttonStateY;
int lastButtonStateY= HIGH; 
long lastDebounceTimeY= 0;

void setup()
{
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT_PULLUP);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
}

void loop()
{
  int cur = millis();
  switchRed(cur);
  switchGreen(cur);
  switchYellow(cur);
}

void switchRed(int cur)
{
  if (cur - startR > 3000 && startR != 0)
  {
    digitalWrite(LED3, LOW);
    startR = 0;
  }
  int readingR = digitalRead(button1);
  if (readingR != lastButtonStateR) {
    lastDebounceTimeR= millis();
  }
  if ((millis()   - lastDebounceTimeR) > debounceDelay) {
    if (readingR != buttonStateR) {
      buttonStateR= readingR;  
      if(buttonStateR == HIGH){
        digitalWrite(LED3, !digitalRead(LED3));
        startR = millis();
      }
    }
  }
  lastButtonStateR= readingR;
}

void switchGreen(int cur)
{
  if (cur - startG > 3000 && startG != 0)
  {
    digitalWrite(LED1, LOW);
    startG = 0;
  }
  int readingG = digitalRead(button3);
  if (readingG != lastButtonStateG) {
    lastDebounceTimeG= millis();
  }
  if ((millis()   - lastDebounceTimeG) > debounceDelay) {
    if (readingG != buttonStateG){
      buttonStateG= readingG;  
      if(buttonStateG == LOW && digitalRead(LED3) != HIGH){
        digitalWrite(LED1, !digitalRead(LED1));
        startG = millis();
      }
    }
  }
  lastButtonStateG= readingG;
}

void switchYellow(int cur)
{
  if (cur - startY <= 2000 && startY != 0)
  {
    if ((cur - subY) > 500)
    {
      digitalWrite(LED2, !digitalRead(LED2));
      subY = millis();
    }
  }
  else if (cur - startY > 2000 && startY != 0)
  {
    digitalWrite(LED2, LOW);
    startY = 0;
  }

  int readingY = digitalRead(button2);
  if (readingY != lastButtonStateY) {
    lastDebounceTimeY= millis();
  }
  if ((millis()   - lastDebounceTimeY) > debounceDelay) {
    if (readingY != buttonStateY){
      buttonStateY= readingY;  
      if(buttonStateY == LOW && digitalRead(LED3) != HIGH && digitalRead(LED1) != HIGH){
        digitalWrite(LED2, HIGH);
        startY = millis();
        subY = millis();
      }
    }
  }
  lastButtonStateY= readingY;
  
}
