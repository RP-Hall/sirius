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
    Robot_Config myRobot;
    char preamble;
}botPacket;

#endif
