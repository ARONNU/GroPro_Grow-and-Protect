import serial
import time

with open('counter.txt', 'r') as file:
    value1 = int(file.read().strip())

with open('sound_count.txt', 'r') as file:
    value2 = int(file.read().strip())

value_send = value1 + value2

# configure serial port
ser = serial.Serial('/dev/ttyUSB0', 9600) # replace '/dev/ttyUSB0' with the appropriate serial port

# send data to Arduino
send_count = 0
while True:
    ser.write(str(value_send).encode()) # send data via serial port
    send_count += 1
    time.sleep(1) # wait for 1 second before sending next message
