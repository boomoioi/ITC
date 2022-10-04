#define LEDSG
#define LEDSY
#define LEDSR
#define BUTTONS

#define LEDWG
#define LEDWY
#define LEDWR
#define BUTTONW

#define LEDKG
#define LEDKR
#define BUTTONK

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
}

void
setup()
{
}

void loop()
{
}
