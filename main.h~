#ifndef _main_h
#define _main_h

//Struct Declaration
typedef struct Leg_Config
{
  char theta[4];
} Leg_Config;

typedef struct Robot_Config
{
  Leg_Config leg[4];
} Robot_Config;

typedef struct botPacket
{
    char preamble;
    char info_byte;
    Robot_Config myRobot;
}botPacket;

int L1 = 60;
int L2 = 72;

#endif
