%%should be used after determining the possible values of x,y and phi grom the gait.m
%%the value of x,y and phi
clear all
clc

l1 = 33;
l2 = 60;
l3 = 74;


fileID_angles = fopen('packet_angles.txt','w');
fprintf(fileID_angles,'%s \n','acceptable packets to be sent to sirius');

num_packets = 0;
for phi = 0:-1:-180
    fprintf(fileID_angles,'********************PHI= %d******************* \n',phi);
    for y = -110:-1:-130;
        fprintf(fileID_angles,'<<<<<<<Y=%d>>>>>>> \n',y);
        for x= -2:1:2
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
end
fclose(fileID_angles);
num_packets



