close all
clear all
clc
priorPorts = instrfind % finds any existing Serial Ports in MATLAB
delete(priorPorts) % and deletes the
s = serial('COM4');
set(s,'BaudRate',19200);
fopen(s);
out = fscanf(s);
end_event = 'End of pic  ';
fprintf(s,'s');

fileID = fopen('image_raw.txt','w');
% fprintf(fileID,'%s \n','raw data obtained from uno');

while(1)
    out = fscanf(s);
    fprintf(fileID,'%s ',out);
    str = out(~isspace(out));
    if(strcmp(str(end-3:end),'FFD9'))
        break;
    end
    
end
fclose(fileID);

systemCommand = 'imageConvert.py';
[status, result] = system(systemCommand);
img = imread('out_image.jpg');
imshow(img)