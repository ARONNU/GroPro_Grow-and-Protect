//Smart Automatic Plant Irrigation System : Grow and Protect (SAPLINS:GroPro)

//Include library
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo servoMotor;

//String to hold incoming data
String  command;

//Set whether the string is complete
bool stringComplete = false;

//Define the max and min value to consider soil whether 'wet' or 'dry'
// Type A: 21% - 40%
#define soilWetA 1023 * 0.21
#define soilDryA 1023 * 0.40
// Type B: 41% - 60%
#define soilWetB 1023 * 0.41
#define soilDryB 1023 * 0.60
// Type A: 61% - 80%
#define soilWetC 1023 * 0.61
#define soilDryC 1023 * 0.80

//Define motor pins
#define motorReservior 4
#define motorPesticide 5
#define motorSprinkler 6
#define mistHumidifier 7
#define FS 255
#define mSdc 0.75
#define mRdc 0.75
#define mPdc 0.50
#define mHdc 0.33

//Define sensor pins
#define sensorPinA A0
#define sensorPinB A1
#define sensorPinC A2
#define motionPin 14

//Define servo pin
#define servoPin 8

//Define soil moisture sensors as analog (varies with level)
#define soilMoistureA analogRead(sensorPinA)
#define soilMoistureB analogRead(sensorPinB)
#define soilMoistureC analogRead(sensorPinC)

//Define motion sensor as digital (1/0)
#define motionSensor digitalRead(motionPin)

LiquidCrystal_I2C lcd(0x27, 20, 4);  // I2C address 0x27, 20 column and 4 rows

//Define constant pin values for float sensors
const byte floatPinUP = 3;
const byte floatPinLOW = 2;

//Define boolean values
bool emptyState = false;
bool fullState = false;

void setup() {
  lcd.init();           // initialize lcd
  lcd.backlight();      // open lcd
  lcd.clear();          // clear display
  lcd.setCursor(0, 0);  // move cursor to   (0, 0)

  //Set motors as 'OUTPUT'
  pinMode(motorSprinkler, OUTPUT);
  pinMode(motorReservior, OUTPUT);
  pinMode(motorPesticide, OUTPUT);
  pinMode(mistHumidifier, OUTPUT);

  //Set sensors as 'INPUT'
  pinMode(sensorPinA, INPUT);
  pinMode(sensorPinB, INPUT);
  pinMode(sensorPinC, INPUT);
  pinMode(motionPin, INPUT);

  //Set switches as 'INPUT_PULLUP'
  pinMode(floatPinUP, INPUT_PULLUP);
  pinMode(floatPinLOW, INPUT_PULLUP);

  //Attach servo to pin
  servoMotor.attach(servoPin);

  //Interrupt command for float switch
  attachInterrupt(digitalPinToInterrupt(floatPinUP), fullTank, RISING);
  attachInterrupt(digitalPinToInterrupt(floatPinLOW), emptyTank, FALLING);

  // Serial Initialization
  Serial.begin(115200);
  command.reserve(20);  // reserve 20 bytes for the command

  //For LCD Display - Initial Display
  lcd.print(" SOIL  MOTOR  PEST");  // LCD Display - Header
  lcd.setCursor(0, 1);
  lcd.print("A:GOOD");
  lcd.setCursor(0, 2);
  lcd.print("B:GOOD");
  lcd.setCursor(0, 3);
  lcd.print("C:GOOD");

  lcd.setCursor(7, 1);
  lcd.print("S:OFF");
  lcd.setCursor(7, 2);
  lcd.print("R:OFF");
  lcd.setCursor(7, 3);
  lcd.print("P:OFF");

  lcd.setCursor(13, 1);
  lcd.print("A:NONE ");
  lcd.setCursor(13, 2);
  lcd.print("V:NONE ");
  lcd.setCursor(13, 3);
  lcd.print("M:NONE ");
}

void loop() {
  lcd.setCursor(0, 0);              // move cursor to   (0, 0)
  lcd.print(" SOIL  MOTOR  PEST");  // LCD Display - Header

  // for soil moisture sensor Type: A
  if (soilMoistureA < soilWetA) {
    Serial.println(String(soilMoistureA) + " Status Type A: Soil is wet");
    lcd.setCursor(0, 1);
    lcd.print("A:WET!");
    // OFF sprinkler
    digitalWrite(motorSprinkler, LOW);
    lcd.setCursor(7, 1);
    lcd.print("S:OFF");
  } else if ((soilMoistureA > soilWetA) && (soilMoistureA <= soilDryA)) {
    Serial.println(String(soilMoistureA) + " Status Type A: Soil moisture is perfect");
    // LCD display - perfect
    lcd.setCursor(0, 1);
    lcd.print("A:GOOD");
  } else {
    Serial.println(String(soilMoistureA) + " Status Type A: Soil is dry - time to water!");
    lcd.setCursor(0, 1);
    lcd.print("A:DRY!");
    // Servo to 30 degree3
    servoMotor.write(30);
    // ON sprinkler
    analogWrite(motorSprinkler, FS * mSdc);
    lcd.setCursor(7, 1);
    lcd.print("S:ON ");
    delay(3000);
  }

  // for soil moisture sensor B
  if (soilMoistureB < soilWetB) {
    Serial.println(String(soilMoistureB) + " Status Type B: Soil is wet");
    lcd.setCursor(0, 2);
    lcd.print("B:WET!");
    // OFF sprinkler
    digitalWrite(motorSprinkler, LOW);
    lcd.setCursor(7, 1);
    lcd.print("S:OFF");
  } else if ((soilMoistureB > soilWetB) && (soilMoistureB <= soilDryB)) {
    Serial.println(String(soilMoistureB) + " Status Type B: Soil moisture is perfect");
    // LCD display - perfect
    lcd.setCursor(0, 2);
    lcd.print("B:GOOD");
  } else {
    Serial.println(String(soilMoistureB) + " Status Type B: Soil is dry - time to water!");
    lcd.setCursor(0, 2);
    lcd.print("B:DRY!");
    // Servo to 90 degrees
    servoMotor.write(90);
    // ON sprinkler
    analogWrite(motorSprinkler, FS * mSdc);
    lcd.setCursor(7, 1);
    lcd.print("S:ON ");
    delay(3000);
  }

  // for soil moisture sensor C
  if (soilMoistureC < soilWetC) {
    Serial.println(String(soilMoistureC) + " Status Type C: Soil is wet");
    lcd.setCursor(0, 3);
    lcd.print("C:WET!");
    // OFF sprinkler
    digitalWrite(motorSprinkler, LOW);
    lcd.setCursor(7, 1);
    lcd.print("S:OFF");
  } else if ((soilMoistureC > soilWetC) && (soilMoistureC <= soilDryC)) {
    Serial.println(String(soilMoistureC) + " Status Type C: Soil moisture is perfect");
    // LCD display - perfect
    lcd.setCursor(0, 3);
    lcd.print("C:GOOD");
  } else {
    Serial.println(String(soilMoistureC) + " Status Type C: Soil is dry - time to water!");
    lcd.setCursor(0, 3);
    lcd.print("C:DRY!");
    // Servo to 150 degrees
    servoMotor.write(150);
    // ON sprinkler
    analogWrite(motorSprinkler, FS * mSdc);
    lcd.setCursor(7, 1);
    lcd.print("S:ON ");
    delay(3000);
  }

  // Motion Sensor - LCD
  //if (motionSensor == HIGH) {
   // Serial.println(String(motionSensor) + " Pest detected!");
    //lcd.setCursor(13, 3);
    //lcd.print("M:PEST!");
    //pestDetectedMotion();
  //} else {
    //Serial.println(String(motionSensor) + " No Pest detected!");
    //lcd.setCursor(13, 3);
    //lcd.print("M:NONE ");
  //}

  

  //Reservior
  if (emptyState == true) {
    lcd.setCursor(7, 2);
    lcd.print("R:ON ");
    emptyState = false;
  }
  if (fullState == true) {
    lcd.setCursor(7, 2);
    lcd.print("R:OFF");
    fullState = false;
  }
  delay(100);
}

//Motion Sensor - Pesticide
//void pestDetectedMotion(void) {
  // ON Mist Humidifier and Pesticides Motor for 5 seconds
  //lcd.setCursor(7, 3);
  //lcd.print("P:ON ");
  //analogWrite(mistHumidifier, FS * mHdc);
  //analogWrite(motorPesticide, FS * mPdc);
  //delay(5000);  // 5 seconds

  // OFF mist Humidifier and Pesticide
  //lcd.setCursor(7, 3);
  //lcd.print("P:OFF");
  //digitalWrite(mistHumidifier, LOW);
  //digitalWrite(motorPesticide, LOW);
//}

//Audio Sensor
void pestDetectedAudio(void) {
  // ON Mist Humidifier and Pesticides Motor for 5 seconds
  lcd.setCursor(7, 3);
  lcd.print("P:ON ");
  analogWrite(mistHumidifier, FS * mHdc);
  analogWrite(motorPesticide, FS * mPdc);
  delay(5000);  // 5 seconds

  // OFF mist Humidifier and Pesticide
  lcd.setCursor(7, 3);
  lcd.print("P:OFF");
  digitalWrite(mistHumidifier, LOW);
  digitalWrite(motorPesticide, LOW);
  lcd.setCursor(13, 1);
  lcd.print("A:NONE ");
}

//Visual Sensor
void pestDetectedVideo(void) {
  // ON Mist Humidifier and Pesticides Motor for 5 seconds
  lcd.setCursor(7, 3);
  lcd.print("P:ON ");
  analogWrite(mistHumidifier, FS * mHdc);
  analogWrite(motorPesticide, FS * mPdc);
  delay(5000);  // 5 seconds

  // OFF mist Humidifier and Pesticide
  lcd.setCursor(7, 3);
  lcd.print("P:OFF");
  digitalWrite(mistHumidifier, LOW);
  digitalWrite(motorPesticide, LOW);
  lcd.setCursor(13, 2);
  lcd.print("V:NONE ");
}

// Float Switch
void emptyTank() {
  // ON motor water reserved
  Serial.println("LOWER");
  analogWrite(motorReservior, FS * mRdc);
  emptyState = true;
}
void fullTank() {
  // ON motor water reserved
  Serial.println("UPPER");
  digitalWrite(motorReservior, LOW);
  fullState = true;
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char data = (char)Serial.read();
    // add it to the inputString:
    command += data;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (data == '\n') {
      stringComplete = true;
    }
   
  }
  // serial - commands from rasp pi
  if (stringComplete) {
    command.trim();
    Serial.println(command);

    //Audio Sensor
    if (command == "audio") {
      lcd.setCursor(13, 1);
      lcd.print("A:PEST!");
      pestDetectedAudio();
    }

    //Visual Sensor
    if (command == "visual") {
      lcd.setCursor(13, 2);
      lcd.print("V:PEST!");
      pestDetectedVideo();
    }

    // clear the string:
    command = "";
    stringComplete = false;
  } else {
    lcd.setCursor(13, 1);
    lcd.print("A:NONE ");
    lcd.setCursor(13, 2);
    lcd.print("V:NONE ");
  } 
}
