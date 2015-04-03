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

for phi = 0:-1:-180
    [theta,load] = inversekinematics(x,y,phi);
    if(load)
        continue;
    end
    
    fprintf(fileID_angles,'%d   :',phi);
    for x=-12:6:12
        [theta,load] = inversekinematics(x,y,phi);
        if(load)
            continue;
        else
            fprintf(fileID_angles,'%0.1f ',x);
        end
    end
    fprintf(fileID_angles,'\n');
    
end
fclose(fileID_angles);


