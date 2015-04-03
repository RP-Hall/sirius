clear all
clc

l1 = 33;
l2 = 60;
l3 = 74;

x = 0;
y = -120;
phi = -60;

fileID_angles = fopen('acceptable_angles.txt','w');
fprintf(fileID_angles,'%s \n','acceptable angles calculated from matlab');

% fclose(fileID);

num_packets = 0;
for phi = -127:-1:-130
    fprintf(fileID_angles,'%d \n',phi);
    for x= -12:6:12
        [theta,load] = inversekinematics(x,y,phi);
        if(load)
            continue;
        end
        
        for i = 1:4
            if(~mod(i,2))
                theta_out = round(angle_conversion_even(theta));
                fprintf(fileID_angles,'%d ',theta_out);
                fprintf(fileID_angles,'\n');
            else
                theta_out = round(angle_conversion_odd(theta));
                fprintf(fileID_angles,'%d ',theta_out);
                fprintf(fileID_angles,'\n');
            end
        end
        fprintf(fileID_angles,'\n');
        
        num_packets = num_packets+1;
    end
end
fclose(fileID_angles);
num_packets



