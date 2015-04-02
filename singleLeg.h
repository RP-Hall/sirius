#ifndef _singleLeg_h
#define _singleLeg_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"

#define PI 3.14159265


Leg_Config getSpiderGaitTheta(double x,double y,double z,int fix);

Leg_Config getDogGaitTheta(double x,double y,int fix);

#endif
