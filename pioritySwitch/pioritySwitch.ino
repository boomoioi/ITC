#define button1 12 //left
#define button2 11 //middle
#define button3 10 //right
#define LED3 4 // red
#define LED2 3 //yellow
#define LED1 2 //green
int startR = 0, startG = 0, startY = 0, subY = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
}

void loop()
{
  int cur = millis(); //12,000
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
  else if (digitalRead(button1) == HIGH)
  {
    digitalWrite(LED3, !digitalRead(LED3));
    startR = millis(); //10,000
    delay(300);
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
