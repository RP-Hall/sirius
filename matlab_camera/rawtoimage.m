function image = rawtoimage(filename)
fileID_raw = fopen('image_raw.txt','r');
fileID_jpg = fopen('final_image.jpg','w');


end


systemCommand = ['imageConvert.py']
[status, result] = system(systemCommand);