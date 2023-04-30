#!/usr/bin/python
import RPi.GPIO as GPIO
import time

# GPIO SETUP
channel = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(channel, GPIO.IN)

count = 0

def callback(channel):
    global count
    if GPIO.input(channel):
        count += 1
        print("Sound Detected!")
    else:
        count += 1
        print("Sound Detected!")

GPIO.add_event_detect(channel, GPIO.BOTH, bouncetime=300)  # let us know when the pin goes HIGH or LOW
GPIO.add_event_callback(channel, callback)  # assign function to GPIO PIN, Run function on change

# infinite loop
while True:
    try:
        time.sleep(0.1)
        final_count = count / 2 * 0.28
        with open("sound_count.txt", "w") as f:
            f.write(str(final_count))
    except KeyboardInterrupt:
        print("\nProgram stopped by user")
        break

GPIO.cleanup()
