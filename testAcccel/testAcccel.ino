#include <TimerOne.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET-1
#define BUZZER_PIN 2
Adafruit_SSD1306 OLED(OLED_RESET);

int timeArr[3];
char timeToPrint[6];

int delayTime = 50;
unsigned long last=0;

int lastState = 0;
int inp = 0;
char messageR[20];
int mess=0;
int timerM[9];
int timerH[9];


void setup(){
  // Pin 13 has an LED connected on most Arduino boards  
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC,0x3C);
  while(!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  for(int i=0; i<3; i++){
    if(EEPROM.read(i)==255){
      timeArr[i] = 0;
    } else {
      timeArr[i] = EEPROM.read(i);
    }
  }
  for(int i=0; i<9; i++){
    if(EEPROM.read((2*i)+3)==255){
      timerM[i] = -1;
      timerH[i] = -1;
    } else {
      timerH[i] = EEPROM.read((2*i)+3);
      timerM[i] = EEPROM.read((2*i)+4);
    }
  }
  pinMode(BUZZER_PIN,OUTPUT);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(addTime);
}
void loop(){
  if(get_axis()>335){
    inp = 1;
  } else {
    inp = 0;
  }
  if(inp != lastState){
    lastState = inp;
    toOLED();
  }
  if(timeArr[2]>=60){
    timeArr[1] += timeArr[2]/60;
    timeArr[2] = timeArr[2]%60;
    formatter(&timeArr[1], &timeArr[0]);
    checkTimer();
    toOLED();
  }
  if(millis()-last >= delayTime){
    getChar();
    last = millis();
  }
}
void addTime(){
  timeArr[2]++;
}

void formatter(int* mi, int* ho){
  if(*mi>=60){
    *ho += *mi/60;
    *mi = *mi%60;
    
  }
  if(*ho>=24){
    *ho = *ho%24;
  }
}

void intToChar(){
  int hourTemp = timeArr[0];
  int minTemp = timeArr[1];
  if(lastState == 1){
    if(hourTemp>12){
      hourTemp-=12;
    }
    if(hourTemp==0){
      hourTemp=12;
    }
  }
  if(minTemp<10){
    timeToPrint[3] = '0';
    timeToPrint[4] = minTemp + 48;
  } else {
    timeToPrint[3] = minTemp/10 + 48;
    timeToPrint[4] = minTemp%10 + 48;
  }
  if(hourTemp<10){
    timeToPrint[0] = '0';
    timeToPrint[1] = hourTemp + 48;
  } else {
    timeToPrint[0] = hourTemp/10 + 48;
    timeToPrint[1] = hourTemp%10 + 48;
  }
  timeToPrint[2] = ':';
  timeToPrint[5] = '\0';
}

void toOLED(){
  intToChar();
  Serial.println(timeToPrint);
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);   
  if(lastState == 0){
    OLED.setTextSize(4); 
    OLED.setCursor(5,0);
    OLED.println(timeToPrint); 
  } else {
    OLED.setTextSize(3); 
    OLED.setCursor(0,7);
    OLED.println(timeToPrint); 
    OLED.setCursor(92,7);
    if(timeArr[0]<12){
      OLED.println("AM");
    } else {
      OLED.println("PM");
    }
  }
  
  
  OLED.display();
}

void getChar() {
  while (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte != '\n') {
      messageR[mess] = (char)inByte;
      mess++;
    } else {
      messageR[mess] = '\0';
      mess = 0;
    }
  }
  Serial.print(messageR);
  if(messageR[0] == 's'){
    setTime();
    saveData();
  }
  if(messageR[0] == 'a'){
    addToTimer();
  }
  messageR[0] = '\0';
}

void addToTimer(){
  int inp[3] = {-1,0,0}, i=2, digit=0;
  if(messageR[i]>57 || messageR[i]<49 || messageR[i+1]!= ' '){
    return;
  }
  inp[0] = messageR[i]-49;
  
  i+=2;
  while(messageR[i]!='.' && digit<3 && messageR[i]!='\0'){
    if(messageR[i]>57 || messageR[i]<48){
    return;
    }
    inp[1]+=messageR[i]-48;
    inp[1]*=10;
    digit++;
    i++;
  }
  inp[1]/=10;
  
  i++;
  digit = 0;
  while(messageR[i]!='\0' && digit<3 && messageR[i]!='\0'){
    if(messageR[i]>57 || messageR[i]<48){
    return;
    }
    inp[2]+=messageR[i]-48;
    inp[2]*=10;
    digit++;
    i++;
  }
  inp[2]/=10;
  if(inp[1]<24 && inp[2]<60){
    timerH[inp[0]] = inp[1];
    timerM[inp[0]] = inp[2];
    Serial.println("Add timer success");
  }
}

void setTime(){
  int inp[2] = {0,0}, i=2, digit=0;
  
  while(messageR[i]!='.' && digit<3 && messageR[i]!='\0'){
    if(messageR[i]>57 || messageR[i]<48){
    return;
    }
    inp[0]+=messageR[i]-48;
    inp[0]*=10;
    digit++;
    i++;
  }
  inp[0]/=10;
   
  i++;
  digit = 0;
  while(messageR[i]!='\0' && digit<3 && messageR[i]!='\0'){
    if(messageR[i]>57 || messageR[i]<48){
    return;
    }
    inp[1]+=messageR[i]-48;
    inp[1]*=10;
    digit++;
    i++;
  }
  
  inp[1]/=10;
  
  if(inp[0]<24 && inp[1]<60){
    timeArr[0] = inp[0];
    timeArr[1] = inp[1];
    timeArr[2] = 0;
    toOLED();
    Serial.println("Set time success");
  }
}

int checkTimer(){
  for(int i=0; i<9; i++){
    if(timeArr[1]==timerM[i] && timeArr[0]==timerH[i]){
      tone(BUZZER_PIN, 800, 100000);
      timerM[i] = -1;
      timerH[i] = -1;
    }
  }
}

void saveData(){
  for(int i=0; i<3; i++){
    EEPROM.write(i, timeArr[i]);
  }
  for(int i=0; i<9; i++){
    EEPROM.write((2*i)+3, timerH[i]);
    EEPROM.write((2*i)+4, timerM[i]);
  }
  Serial.println("Save data success");
}
int buffer[16];
int buffer_pos = 0; 
int get_axis() {
  delay(1); 
  buffer[buffer_pos] = analogRead(A3);
  buffer_pos = (buffer_pos+1) % 16;
  long sum = 0;
  for (unsigned int i = 0; i < 16; i++)
    sum += buffer[i];
  return round(sum / 16);
}
