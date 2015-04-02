
#include "singleLeg.h"

extern int L1,L2,L3;

int getSpiderGaitTheta1(double x,double y,double z)
{
    theta1 = int(180*(atan2(y,x))/PI);
    return theta1;
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
    theta3 = int(180*acos(c3)/PI);
    
    return theta3;
}

int getSpiderGaitTheta2(double x,double y,double z)
{
    double k1,k2;
    k1 = L1 + (L2*cos(theta3*PI/180));
    k2 = L2*sin(theta3*PI/180);
    double at = atan2(z,k)-atan2(k2,k1);
    theta2 =  int(180*at/PI);

    return theta2;
}

int phi = 90;

int getDogGaitTheta2(double x,double y)
{
    double x_prime = x - (L3*cos(phi*PI/180));
    double y_prime = y - (L3*sin(phi*PI/180));
    double costheta2 = ((x_prime*x_prime)+(y_prime*y_prime)-(L1*L1)-(L2*L2))/(2*L1*L2);
    theta2 = int(180*acos(theta2)/PI);

    return theta2;
}

int getDogGaitTheta1(double x,double y)
{
    double k1 = L1 + (L2*cos(theta2*PI/180));
    double k2 = L2*sin(theta2*PI/180);
    theta1 = int((180*atan2(y,x)/PI)-(180*atan2(k2,k1)));

    return theta1;
}

int getDogGaitTheta3(double x,double y)
{
    return (phi-theta1-theta2);
}
