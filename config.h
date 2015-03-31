#ifndef _CONFIG_H
#define _CONFIG_H

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



#endif
