
#include "singleLeg.h"

int getSpiderGaitTheta1(double x,double y,double z)
{
    return int(180*(atan2(y,x))/PI);
}

int getSpiderGaitTheta3(double x,double y,double z)
{
    double s,c,s3,c3;
    s = sin(theta1* PI/180);
    c = cos(theta1*PI/180);
    if(y!=0 && s!=0)
	k = y/s;
    else k = x/c;

    c3 = ((z*z)+(k*k)-(L1*L1)-(L2*L2))/(2*L1*L2);

    return int(180*acos(c3)/PI);
		    
}

int getSpiderGaitTheta2(double x,double y,double z)
{
    double k1,k2;
    k1 = L1 + (L2*cos(theta3*PI/180));
    k2 = L2*sin(theta3*PI/180);
    double at = atan2(z,k)-atan2(k2,k1);
    return int(180*at/PI);
}

