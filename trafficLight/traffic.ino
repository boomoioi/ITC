#define LEDSG 10
#define LEDSY 11
#define LEDSR 12
#define BUTTONS 4

#define LEDWG 7
#define LEDWY 8
#define LEDWR 9
#define BUTTONW 3

#define LEDKG 6
#define LEDKR 5
#define BUTTONK 2

#define goS 0
#define waitS 1
#define goW 2
#define waitW 3
#define goK 4
#define redKF 5
#define blackKF 6
#define redKS 7
#define blackKS 8
#define redKT 9

#define greenTime 3000
#define yellowTime 1000
#define blinkTime 300

int lights[8] = {LEDSG, LEDSY, LEDSR, LEDWG, LEDWY, LEDWR, LEDKG, LEDKR};
int state = 0, isBitSet;
int inp1, inp2, inp3, temp;

structState
{
    unsigned long ST_Out;
    unsigned long Time;
    unsigned long Next[10];
};
typedef const structState SType;
SType FSM[4] = {
    {B10100001, greenTime, {goS, waitS, waitS, waitS, goS, waitS, waitS, waitS}},
    {B10100010, yellowTime, {goW, goK, goW, goW, goW, goK, goW, goW}},
    {B10001100, greenTime, {goW, waitW, goW, waitW, waitW, waitW, waitW, waitW, waitW}},
    {B10010100, yellowTime, {goK, goK, goK, goK, goS, goK, goS, goK}},
    {B01100100, greenTime, {goK, goK, redKF, redKF, redKF, redKF, redKF, redKF}},
    {B10100100, blinkTime, {blackKF, blackKF, blackKF, blackKF, blackKF, blackKF, blackKF, blackKF}},
    {B00100100, blinkTime, {redKS, redKS, redKS, redKS, redKS, redKS, redKS, redKS}},
    {B10100100, blinkTime, {blackKS, blackKS, blackKS, blackKS, blackKS, blackKS, blackKS, blackKS}},
    {B00100100, blinkTime, {redKT, redKT, redKT, redKT, redKT, redKT, redKT, redKT}} {B10100100, blinkTime, {goS, goS, goW, goW, goS, goS, goS, goS}},
};

void setup()
{
    pinMode(LEDSG, OUTPUT);
    pinMode(LEDSY, OUTPUT);
    pinMode(LEDSR, OUTPUT);
    pinMode(LEDWG, OUTPUT);
    pinMode(LEDWY, OUTPUT);
    pinMode(LEDWR, OUTPUT);
    pinMode(LEDKG, OUTPUT);
    pinMode(LEDKR, OUTPUT);
    pinMode(BUTTONS, INPUT);
    pinMode(BUTTONW, INPUT);
    pinMode(BUTTONK, INPUT);
}

void loop()
{
    for (int i = 0; i < 8; i++)
    {
        isBitSet = bitRead(FSM[state].ST_Out, i);
        digitalWrite(lights[i], isBitSet);
    }
    delay(FSM[state].Time);
    inp1 = digitalRead(BUTTONS);
    inp2 = digitalRead(BUTTONW);
    inp3 = digitalRead(BUTTONK);
    temp = inp1*4 + inp2*2 + inp3;
    state = FSM[state].Next[temp];
}
