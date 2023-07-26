#include <Preferences.h>

// define potentiometer as pin 34
# define potPin 34 

// define led count and an array for led pins
const int ledCount = 3;
int ledPins[] = {21,22,23};

// set up code, to run once
void setup() {

  // initialize each led as output
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }

  // initalize potentiometer as input
  pinMode(potPin, INPUT);

  //set baud rate
  Serial.begin(115200);

}

// main code, to run repeatedly
void loop() {

  // read potentiometer value and map it to a led value (from 0 to 3)
  int sensorReading = analogRead(potPin);
  int ledLevel = map(sensorReading, 0, 4095, 0, ledCount);

  // light all leds below the mapped led value
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }
    else {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }
  
}
