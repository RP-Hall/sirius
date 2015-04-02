
#include "singleLeg.h"

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

int phi = 90;

Leg_Config getDogGaitTheta(double x,double y,int fix)
{
    Leg_Config leg;
    
    double x_prime = x - (L3*cos(phi*PI/180));
    double y_prime = y - (L3*sin(phi*PI/180));
    double costheta2 = ((x_prime*x_prime)+(y_prime*y_prime)-(L1*L1)-(L2*L2))/(2*L1*L2);
    leg.theta[1] = int(180*acos(costheta2)/PI);

    double k1 = L1 + (L2*cos(leg.theta[1]*PI/180));
    double k2 = L2*sin(leg.theta[1]*PI/180);
    leg.theta[0] = int((180*atan2(y,x)/PI)-(180*atan2(k2,k1)));

    leg.theta[2] = phi-leg.theta[0]-leg.theta[1];

    leg.theta[3] = 0;
    
    return leg;
}
