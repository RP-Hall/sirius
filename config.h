#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>

//Struct Declaration
typedef struct Leg_Config
{
  int8_t theta[4];
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
