clear all
clc

l1 = 33;
l2 = 60;
l3 = 74;

x = 0;
y = -120;
phi = -60;

fileID = fopen('acceptable_angles.txt','w');
fprintf(fileID,'%c \n','a');
% fclose(fileID);


for phi = 0:-1:-180
    [theta,load] = inversekinematics(x,y,phi);
    if(load)
        continue;
    end
    theta_out = [-1,round(angle_conversion(theta))];
%     fileID = fopen('acceptable_angles.txt','a');
    
    fprintf(fileID,'%d ',theta_out);
    fprintf(fileID,'\n');

%     fclose(fileID);
end



