import binascii

f = open ("image_raw.txt","r")
nf = open("out_image.jpg","wb")
#tf = open("B1.txt","wb")

#Read whole file into data
while 1:
    c = f.readline()
    d = c.strip()
    if not c:
        break
    nf.write(binascii.a2b_hex(d))
#    tf.write(binascii.a2b_hex(d))


# Close the file
f.close()
nf.close()
