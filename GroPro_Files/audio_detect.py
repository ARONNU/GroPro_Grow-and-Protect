#!/usr/bin/python
import RPi.GPIO as GPIO
import time

# GPIO SETUP
channel = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(channel, GPIO.IN)

def callback(channel):
    with open("/home/aronn/GroPro_Files/detect.txt", "w") as f:
        f.write("audio")

GPIO.add_event_detect(channel, GPIO.BOTH, bouncetime=300)  # let us know when the pin goes HIGH or LOW
GPIO.add_event_callback(channel, callback)  # assign function to GPIO PIN, Run function on change

# Start time counter
start_time = time.time()

# infinite loop
while True:
    try:
        # Check if 30 seconds have elapsed
        if time.time() - start_time >= 30:
            print("30 seconds have elapsed. Terminating program.")
            break

        time.sleep(0.1)
    except KeyboardInterrupt:
        print("\nProgram stopped by user")
        break

GPIO.cleanup()
