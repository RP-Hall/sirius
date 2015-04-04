
#include "singleLeg.h"
#include <math.h>

extern int L1,L2,L3;


Leg_Config getSpiderGaitTheta(double x,double y,double z,int fix)
{
    Leg_Config leg;
    leg.theta[0] = int(180*(atan2(y,x))/PI);

    double s,c,s3,c3,k;
    s = sin(leg.theta[0]* PI/180);
    c = cos(leg.theta[0]*PI/180);
    if(y!=0 && s!=0)
	k = y/s;
    else k = x/c;

    c3 = ((z*z)+(k*k)-(L1*L1)-(L2*L2))/(2*L1*L2);
    leg.theta[2] = int(180*acos(c3)/PI);
    
    double k1,k2;
    k1 = L1 + (L2*cos(leg.theta[2]*PI/180));
    k2 = L2*sin(leg.theta[2]*PI/180);
    double at = atan2(z,k)-atan2(k2,k1);
    leg.theta[1] =  int(180*at/PI);

    leg.theta[3] = 0;
    
    return leg;
}

int phi = -60*PI/180;

Leg_Config getDogGaitTheta(double x,double y, int fix)
{
    printf("x = %f y = %f\n", x, y);
    Leg_Config leg;
    double x_prime = x - L3*cos(phi);
    double y_prime = y - L3*sin(phi);
    printf("x_prime = %f y_prime = %f sin(30) = %f\n", x_prime, y_prime, sin(phi));

    double c = ((x_prime*x_prime) + (y_prime*y_prime) - (L1*L1) - (L2*L2))/(2*L1*L2);
    double s1 = sqrt(1 - (c*c));
    double s2 = -s1;
    printf("s1 = %f s2 = %f\n", s1, s2);

    //leg.theta[1] = int(180*atan2(s1, c)/PI);
    
      if ((180*atan2(s1, c)/PI < 0 && 180*atan2(s1, c)/PI > -90))
      {
      	leg.theta[1] = int(180*atan2(s1, c)/PI);
      }
      else
        {
      	leg.theta[1] = int(180*atan2(s2, c)/PI);
        }

    double k1 = L1 + (L2*cos(leg.theta[1]*PI/180));
    double k2 = L2*sin(leg.theta[1]*PI/180);

    leg.theta[4] = 180*(atan2(y_prime, x_prime) - atan2(k2, k1))/PI;

    leg.theta[3] = 180*(atan2(y, x) - atan2(k2, k1))/PI;

    leg.theta[0] = -1;
    
    return leg;
}
