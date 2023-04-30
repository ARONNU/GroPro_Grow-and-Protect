# Mochi Step by step guide 
Guide for Mochi after she downloaded the > Mochi Instruction Folder

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

**side note: add the time for the Pest_Detection.py and Audio_Detection.py so that it will be opened automatically every said time.
