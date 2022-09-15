#include "LedControl.h"
#include "pitches.h"
LedControl lc=LedControl(11,13,10,4);  // DIN,CLK,CS,Number of LED Module

#define SLIDE A0
#define OHM A3
#define sAudioPin 8

int lastPlayer2=0;
int p2m=1, p2r=2,p2l=0;
int lastX=0;
int playerPo = 1, right=2, left=0;
int x=8, y=4, a=0, b=1;
int lastPong=0, rerate=250;
void setup() {
  Serial.begin(9600);
  for(int i=0; i<4; i++){
    lc.shutdown(i,false);     // go to normal mode
    lc.setIntensity(i,8);     // brightness
    lc.clearDisplay(i);       // clear display
  }
  lc.setColumn(3,7,byte(255));
  lc.setColumn(0,0,byte(255));
  pinMode(SLIDE, INPUT );
}

void loop() {
  int playerRead = player();
  int playerDiff = playerRead-lastX;
  lastX = playerRead;    
  playerPo += playerDiff;
  left += playerDiff;
  right += playerDiff;

  int player2Read = player2();
  int player2Diff = player2Read - lastPlayer2;
  lastPlayer2 = player2Read;
  p2m += player2Diff;
  p2l += player2Diff;
  p2r += player2Diff;

  pong();

  if(y == 6){
    if(x == playerPo){
      b=-1;
      sound();
    } else if(x == right){
      b=-1;
      a=1;
      sound();
    } else if(x == left){
      b=-1;
      a=-1;
      sound();
    }
  }
  
  if(y == 1){
    if(x == p2m){
      b=1;
      sound();
    } else if(x == p2r){
      b=1;
      a=1;
      sound();
    } else if(x == p2l){
      b=1;
      a=-1;
      sound();
    }
  }

  if(x==0 && a==-1){
    a=1;
    sound();
  }
  if(x==15 && a==1){
    a=-1;
    sound();
  }

  for(int i=0; i<8; i++){
    lc.setRow(2,i,byte(0));
    lc.setRow(1,i,byte(0));
  }
  show(7, playerPo);
  show(7, left);
  show(7, right);
  show(0, p2m);
  show(0, p2l);
  show(0, p2r);
  show(y,x);
  if(y==0 || y==7){
    win();
  }
}

int player(){
  int read = analogRead(OHM);
  int playerX = map(read, 0, 1023, 0, 14);
  return playerX;
}

int player2(){
  int read = analogRead(SLIDE);
  Serial.println(read);
  int player2p = map(read, 0, 1023, 0, 14);
  return player2p;
}

void show(int y, int x){
  if(x>7){
    x = x%8;
    lc.setLed(1, y, x, 1);
  } else {
    lc.setLed(2, y, x, 1);
  }
  
}

void pong(){
  if(millis()-lastPong>rerate){
    x += a;
    y += b;
    lastPong = millis();
  }
  
}

void sound(){
  tone(sAudioPin, 494, 10);      
}

void win(){
  for(uint8_t nLoop = 0;nLoop < 2;nLoop ++)
         {
          int NOTE_SUSTAIN = 30;
           tone(sAudioPin,NOTE_A5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_B5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_C5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_B5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_C5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_D5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_C5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_D5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_E5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_D5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_E5);
           delay(NOTE_SUSTAIN);
           tone(sAudioPin,NOTE_E5);
           delay(NOTE_SUSTAIN);
         }
         noTone(sAudioPin);
}
