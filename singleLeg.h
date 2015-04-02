#ifndef _singleLeg_h
#define _singleLeg_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"

#define PI 3.14159265

double k;

int theta1,theta2,theta3,theta4;

int getSpiderGaitTheta1(double x,double y,double z);
    
int getSpiderGaitTheta2(double x,double y,double z);;

int getSpiderGaitTheta3(double x,double y,double z);

int getDogGaitTheta1(double x,double y);

int getDogGaitTheta2(double x,double y);

int getDogGaitTheta3(double x,double y);

#endif
