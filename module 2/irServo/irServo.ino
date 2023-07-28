#include <ESP32Servo.h>
int IRSensord = 2; 
int IRSensora = 34 ;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(4); // attaches the servo on pin 35 to the servo object
  pinMode(IRSensord, INPUT); // IR Sensor pin INPUT
  pinMode(IRSensora, INPUT); // IR Sensor pin INPUT
  Serial.begin(115200);
}

void loop() {

  int sensorstatus= analogRead(IRSensora);
  int dist = map(sensorstatus, 0, 4095, 0, 25);

  if (dist <= 3) // Check if the pin high or not
  {
    for (pos = 0; pos <= 180; pos ++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    delay(40);
  }
  }
  else  {
    for (pos = 180; pos >= 0; pos --) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    delay(40);
  }        
  }
              
  }
