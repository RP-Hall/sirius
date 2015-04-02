clear all
clc

l1 = 33;
l2 = 60;
l3 = 74;

x = 0;
y = -120;
phi = -60;

for phi = 0:-1:-180
    [theta,load] = inversekinematics(x,y,phi);
    if(load)
        continue;
    end
    theta_out = round(angle_conversion(theta))
end
