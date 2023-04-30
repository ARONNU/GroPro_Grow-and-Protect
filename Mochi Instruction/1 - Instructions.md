# Mochi Step by step guide 
Guide for Mochi after she downloaded the Mochi Instruction Folder.
Then execute the Pest_Detection.py and Audio_Detect.py, after doing so check if there are values in the counter.txt and sound_count.txt (update me)

## Raspberry pi executing a code on a specific time using cron

1. Type the code given below to the command prompt

```
chmod +x arduino_transfer.py
```

The arduino_transfer.py above is the code that will transfer the data from

5. Open the crontab file for editing:

```
crontab -e
```

6. Add the following line to the end of the file to schedule the script to run every day at 4:30 AM:

```
30 04 * * * /path/to/arduino_transfer.py
```

Replace `/path/to/arduino_transfer.py` with the actual path to the script.

7. Save the file and exit the editor.

Now the script will automatically run every day at 4:30 AM. You can modify the schedule by changing the numbers in the cron job line. For example, to run the script every hour, you can use the following line:

```
0 * * * * /path/to/hello_world.py
```

This will run the script at the start of every hour.

**side note: add the time for the Pest_Detection.py and Audio_Detect.py so that it will be opened automatically every said time. (Preferrable time is morning when pests and sounds are abundant)

##Setting up the arduino to receive the data from arduino_transfer.py
Upload the Arduino code: Write a program on the Arduino Mega 2560 to receive the data from the Raspberry Pi and take the appropriate action. Here is some sample code:

   ```
   void setup() {
     Serial.begin(9600); // initialize serial communication
   }

   void loop() {
     if (Serial.available()) { // if data is available on the serial port
       String message = Serial.readString(); // read the message
       Serial.println(message); // print the message to the Serial Monitor
     }
   }
   ```

   In the above code, the Arduino Mega 2560 waits for data to be received on the serial port, and when data is available, it reads the message and prints it to the Serial Monitor.
   
  Change the code so that it can get the values from arduino_transfer.py to the thresholds that will connect the presticide's thresholds:
Threshold 1 = 20 - 49
Threshold 2 = 50 - 100
Threshold 3 = 100+
