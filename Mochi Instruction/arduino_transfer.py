import serial
import time

with open('counter.txt', 'r') as file:
    vis_count = int(file.read().strip())

with open('sound_count.txt', 'r') as file:
    aud_count = int(file.read().strip())

if vis_count >= 25 & <= 40:



# configure serial port
ser = serial.Serial("/dev/ttyACM0", 115200, timeout=1) # or '/dev/ttyUSB0' with the appropriate serial port, The Current USB Port is for the USB 3 Upper port (Blue)

# send data to Arduino
send_count = 0
while True:
    ser.write(str(visual).command()) # send data via serial port
    send_count += 1
    time.sleep(1) # wait for 1 second before sending next message


#edit code from https://rimstar.org/science_electronics_projects/raspberry_pi_to_arduino_serial_usb_communication.htm
