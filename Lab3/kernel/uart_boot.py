#!/usr/bin/python3

from serial import Serial


with open('kernel8.img','rb') as fd:
    with Serial('/dev/ttys001', 115200) as ser:
    #with Serial('/dev/tty.usbserial-0001', 115200) as ser:
        raw = fd.read()
        length = len(raw) 
        
        print("Image size: ", length)
        ser.write(str(length).encode()+b'\n')
        ser.flush()

        print("Start to transfer...")
        for i in range(length):
            ser.write(raw[i: i+1])
            ser.flush()
            if i%100==0:
                print("{:>6}/{:>6} bytes\n".format(i, length))
        print("{:>6}/{:>6} bytes\n".format(length, length))
        print("Transfer finished!")

        
