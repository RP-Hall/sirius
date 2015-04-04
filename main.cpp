#include <stdio.h>
#include "serial.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "config.h"
#include "lut.h"
#include "singleLeg.h"

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
    command.preamble = 0xaa;
    command.info_byte = 0b00000000;
    command.myRobot = myRobot;

    sPort.Write(&command, sizeof(botPacket));
}

void sendBrokenPacket(Robot_Config myRobot)
{
    Robot_Config newRobot;
    int angle[4];
    Leg_Config leg[4];
    
    newRobot.leg[0].theta[0] =72;
    newRobot.leg[1].theta[0] =75;
    newRobot.leg[2].theta[0] =75;
    newRobot.leg[3].theta[0] =80;
	
    for(int i=0;i<4;i++)
    {	
	for(int j=1;j<4;j++)
	{
		newRobot.leg[i].theta[j] =0;
	}
	leg[i] = makeLeg(newRobot.leg[i].theta[0],newRobot.leg[i].theta[1],newRobot.leg[i].theta[2],newRobot.leg[i].theta[3]);
    }
    newRobot = makeRobot(leg[0],leg[1],leg[2],leg[3]);
    for(int i=0;i<10;i++)
    {
	for(int i=0;i<4;i++)
	{
	    for(int j=1;j<4;j++)
	    {
		newRobot.leg[i].theta[j] += (myRobot.leg[i].theta[j]/10);
	    }
	    leg[i] = makeLeg(newRobot.leg[i].theta[0],newRobot.leg[i].theta[1],newRobot.leg[i].theta[2],newRobot.leg[i].theta[3]);
	}
	Robot_Config sendRobot = makeRobot(leg[0],leg[1],leg[2],leg[3]);
	sendCommand(sendRobot);
	//usleep(1500000);
    }
    for(int i=0;i<4;i++)
    {
	for(int j=0;j<4;j++)
	{
	    newRobot.leg[i].theta[j] += (myRobot.leg[i].theta[j]%10);
	}
	leg[i] = makeLeg(newRobot.leg[i].theta[0],newRobot.leg[i].theta[1],newRobot.leg[i].theta[2],newRobot.leg[i].theta[3]);
    }
    Robot_Config sendRobot = makeRobot(leg[0],leg[1],leg[2],leg[3]);
    sendCommand(sendRobot);

}

int mat[4][5] = { { 111,89,71,51,31 }, {69,89,109,129,149}, {112,92,72,52,32}, {69,89,109,129,149}};

int main(int argc, char **argv)
{

  if(!sPort.Open("/dev/ttyUSB0", 57600))
    {
      perror("Could not Open Serial Port s0 :");
      exit(0);
    }
  int angle[4];
  Leg_Config leg[4];
  int num_packets,t;
  scanf("%d",&num_packets);
  for (int k = 0; k < num_packets; k++)
    {
      for(int i=0;i<4;i++)
	{
	  for(int j=0;j<4;j++)
	    {
	      if(j==0)
		{
		  scanf("%d",&t);
		  angle[j] = mat[i][t+2];
		}
	      else scanf("%d",&angle[j]);
	    }
	  leg[i] = makeLeg(angle[0],angle[1],angle[2],angle[3]);
	}
      Robot_Config myRobot = makeRobot(leg[0],leg[1],leg[2],leg[3]);
      
      sendCommand(myRobot);
      
      usleep(1000000);
    } 
  //Leg_Config leg1 = getDogGaitTheta(113.9725, -113.9398, 0);
  //printf("%d %d %d %d\n",leg1.theta[0],leg1.theta[1],leg1.theta[2], leg1.theta[3]);
  
  return 0;
}
