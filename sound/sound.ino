int speakerPin= 8;
int numTones= 10;
int tones[] = {261,277,294,311,330,349,370,392,415,440};
//  mid C  C#   D    D#   E    F    F#   G    G#   A
void setup(){
  pinMode(speakerPin, OUTPUT);
//  for (int i=0; i< numTones; i++){
//    tone(speakerPin, tones[i]);
//    delay(500);
//  }
//  noTone(speakerPin);
}
void loop(){
  digitalWrite(speakerPin, HIGH);
  delay(600);
  digitalWrite(speakerPin, LOW);
  delay(600);
}
