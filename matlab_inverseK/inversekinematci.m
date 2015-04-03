clear all
clc

l1 = 33;
l2 = 60;
l3 = 74;

x = 0;
y = -120;
phi = -60;

fileID = fopen('acceptable_angles.txt','w');
fprintf(fileID,'%s \n','acceptable angles calculated from matlab');
% fclose(fileID);

counter = 0;
for phi = 0:-1:-180
    [theta,load] = inversekinematics(x,y,phi);
    if(load)
        continue;
    end
    theta_out = round(angle_conversion(theta));
    %     fileID = fopen('acceptable_angles.txt','a');
    for i = 1:4
        fprintf(fileID,'%d ',theta_out);
        fprintf(fileID,'\n');
    end
    fprintf(fileID,'\n');
    
    counter = counter+1;
    
    %     fclose(fileID);
end
counter



