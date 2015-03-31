#include <stdio.h>
#include "serial.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "main.h"
#include "lut.h"

botPacket command;

Serial sPort;

Leg_Config makeLeg(int theta1,int theta2,int theta3,int theta4)
{
    Leg_Config leg;
    leg.theta[0] = theta1;
    leg.theta[1] = theta2;
    leg.theta[2] = theta3;
    leg.theta[3] = theta4;

    return leg;
}

Robot_Config makeRobot(Leg_Config leg1,Leg_Config leg2,Leg_Config leg3,Leg_Config leg4)
{
    Robot_Config myRobot;
    myRobot.leg[0] = leg1;
    myRobot.leg[1] = leg2;
    myRobot.leg[2] = leg3;
    myRobot.leg[3] = leg4;
    
    return myRobot;
}

void sendCommand(Robot_Config myRobot)
{
    command.preamble = 'n';
    command.myRobot = myRobot;

    sPort.Write(&command, sizeof(botPacket));
}


int main(int argc, char **argv)
{

/*	if(!sPort.Open("/dev/ttyACM0", 57600))
	{
		perror("Could not Open Serial Port s0 :");
		exit(0);
	}
	int angle[4];
	Leg_Config leg[4];
        for(int i=0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
	    {
		scanf("%d",&angle[j]);
	    }
	    leg[i] = makeLeg(angle[0],angle[1],angle[2],angle[3]);
	}
	Robot_Config myRobot = makeRobot(leg[0],leg[1],leg[2],leg[3]);

	sendCommand(myRobot);
*/
	printf("%d",getAngle(153));
	
	return 0;
}
