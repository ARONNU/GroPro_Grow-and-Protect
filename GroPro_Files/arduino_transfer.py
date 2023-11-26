import serial
import time

# Open the serial port to the Arduino.
ser = serial.Serial("/dev/ttyACM0", 115200, timeout=1.0)
time.sleep(3)

# Read the int data from the text file and extract the first word.
with open("detect.txt", "r") as f:
    command = f.readline()

# Send the int data to the Arduino.
ser.write(str(command).encode())
ser.reset_input_buffer()

print("Sent to arduino successfully")

# Close the serial port.
ser.close()
