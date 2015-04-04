#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>
#define PI 3.1416

#define MAX_PACKETS 10
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

typedef struct Gait
{
	int num_packets;
	Robot_Config[MAX_PACKETS];
}Gait;



#endif
