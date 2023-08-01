#define LED_PIN 2
#define BUZZER_PIN 18  // Define the pins used for the LED, buzzer, and LDR
#define LDR_PIN 35
#include <ESP32Servo.h>
#include <Preferences.h>

// define potentiometer as pin 34
# define potPin 34 

int light_threshold = 500;
int pos = 0;    // variable to store the servo position
Servo myservo;  // create servo object to control a servo
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(potPin, INPUT);
  // Initialize the serial port and configure the LED and buzzer pins
   myservo.attach(4); // attaches the servo on pin 35 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:

  int ldr_value = analogRead(LDR_PIN);

   // Check if the light level is above the threshold
  if(ldr_value > light_threshold){
    
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    
  }
  else {
     // If it is not, turn off the LED and buzzer
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
   for (pos = 0; pos <= 180; pos ++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);
    }                       // waits 15ms for the servo to reach the position
  

    
  }
  delay(100);
  int potValue = analogRead(potPin);
  int servoAngle = map(potValue, 0, 1023, 0, 180);
  myservo.write(servoAngle);
  delay(15);

}
