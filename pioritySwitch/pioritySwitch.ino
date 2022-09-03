#define button1 12 // left
#define button2 11 // middle
#define button3 10 // right
#define LED3 4     // red
#define LED2 3     // yellow
#define LED1 2     // green
int startR = 0, startG = 0, startY = 0, subY = 0;
int buttonState;
int lastButtonState = LOW; 
long lastDebounceTime = 0;
long debounceDelay = 50;
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
  //  Serial.println(digitalRead(button1));
  //  Serial.println(digitalRead(button2));
  //  Serial.println(digitalRead(button3));
  //  Serial.println("_______________________________________");
  //  delay(1000);
  switchRed(cur);
//  switchGreen(cur);
//  switchYellow(cur);
}

void switchRed(int cur)
{
  if (cur - startR > 3000 && startR != 0)
  {
    digitalWrite(LED3, LOW);
    startR = 0;
  }
  else if (debounce(button1) == 1)
  {
    digitalWrite(LED3, !digitalRead(LED3));
    startR = millis(); // 10,000
  }
}

void switchGreen(int cur)
{
  if (cur - startG > 3000 && startG != 0)
  {
    digitalWrite(LED1, LOW);
    startG = 0;
  }
  else if (digitalRead(button3) == LOW && digitalRead(LED3) != HIGH)
  {
    digitalWrite(LED1, !digitalRead(LED1));
    startG = millis();
    delay(300);
  }
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
  else if (digitalRead(button2) == LOW && digitalRead(LED3) != HIGH && digitalRead(LED1) != HIGH)
  {
    digitalWrite(LED2, HIGH);
    startY = millis();
    subY = millis();
    delay(300);
  }
}

int debounce(int buttonPin)
{
  int reading = digitalRead(buttonPin);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncingtimer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debouncedelay, so take it as the actual current state:
    if (reading != buttonState)
    {
      buttonState = reading;
    }
  }
  lastButtonState = reading;
  return buttonState;
}
