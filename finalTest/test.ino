#define SW1 13
#define SW2 12
#define SW3 11
#define SW4 10
#define LED1 6
#define LED2 5
#define LED3 4
#define LED4 3

int buttonState1;
int lastButtonState1 = HIGH;
long debounceTime1 = 0;

int buttonState2;
int lastButtonState2 = HIGH;
long debounceTime2 = 0;

int buttonState3;
int lastButtonState3 = HIGH;
long debounceTime3 = 0;

int buttonState4;
int lastButtonState4 = HIGH;
long debounceTime4 = 0;

long debounceDelay = 50;

int check = -1;

int arrRead[4] = {1, 1, 1, 1};
int arrLED[4] = {LED1, LED2, LED3, LED4};
int res[4] = {0,0,0,0};
int newRes[4] = {0,0,0,0};
int count = 0;


void setup(){
  Serial.begin(9600);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop(){  
  butt1();
  butt2();
  butt3();
  butt4();
}

void butt1(){
  int reading = digitalRead(SW1);

  if(lastButtonState1 != reading){
    debounceTime1 = millis();
  }

  if(millis() - debounceTime1 > debounceDelay){
    if(reading != buttonState1){
      buttonState1 = reading;
      arrRead[1] = buttonState1;
//      Serial.println(buttonState1);
    }
  }
  lastButtonState1 = reading;
}

void butt2(){
  int reading = digitalRead(SW2);

  if(lastButtonState2 != reading){
    debounceTime2 = millis();
  }

  if(millis() - debounceTime2> debounceDelay){
    if(reading != buttonState2){
      buttonState2 = reading;
      arrRead[2] = buttonState2;
//      Serial.println(buttonState2);
    }
  }
  lastButtonState2 = reading;
}

void butt3(){
  int reading = digitalRead(SW3);

  if(lastButtonState3 != reading){
    debounceTime3 = millis();
  }

  if(millis() - debounceTime3 > debounceDelay){
    if(reading != buttonState3){
      buttonState3 = reading;
      arrRead[3] = buttonState3;
//      Serial.println(buttonState3);
    }
  }
  lastButtonState3 = reading;
}

void butt4(){
  int reading = digitalRead(SW4);

  if(lastButtonState4 != reading){
    debounceTime4 = millis();
  }

  if(millis() - debounceTime4 > debounceDelay){
    if(reading != buttonState4){
      buttonState4 = reading;
      if(buttonState4 == LOW){
        check++;
        firstTime();
        secondTime();
        thirdTime();
      }
    }
  }
  lastButtonState4 = reading;
  if(check == 2){
    for(int i=0; i<4; i++){
      Serial.println(newRes[i]);
      digitalWrite(arrLED[i], newRes[i]);
    }
  
  }
  
}

void firstTime(){
  if(check == 0){
    for(int i=0; i<4; i++){
      res[i] = !arrRead[i];
      digitalWrite(arrLED[i], res[i]);
    }
  }
}

void secondTime(){
  if(check == 1){
    for(int i=0; i<4; i++){
      count *= 2;
      count += !arrRead[i];
      digitalWrite(arrLED[i], !arrRead[i]);
    }
  }
}

void thirdTime(){
  if(check == 2){
    for(int j=0; j<4; j++){
      int tempMod = (j-count)%4;
      newRes[(4+tempMod)%4] = res[j];
    }
  }
  if(check >= 3){
    check = -1;
    for(int i=0; i<4; i++){
      digitalWrite(arrLED[i], LOW);
      newRes[i] = 0;
    }
  }
}
