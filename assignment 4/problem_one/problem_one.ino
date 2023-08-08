#include <Keypad.h> /* Included keypad library */
#include <ESP32Servo.h>

#define ROW_NUM 4 /* Define keypad Rows */
#define COLUMN_NUM 4 /* Define keypad Columns */
#define SERVO_PIN 4
#define LDR_PIN 35
int IRSensora = 34 ;
float lux=0.00,ADC_value=0.0048828125,LDR_value;
int light_threshold = 500;

char keys[ROW_NUM][COLUMN_NUM] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUM] = {21, 19, 18, 5}; // ESP32GPIO pins for Rows
byte pin_column[COLUMN_NUM] = {12, 13, 14, 15}; //ESP32 GPIO pins for Columns

Keypad keypad = Keypad(makeKeymap(keys), pin_rows,
pin_column, ROW_NUM, COLUMN_NUM);
const int embeddedLedPin = 2; // ESP32 embedded LED pin (GPIO 2)


Servo doorLock; 
int pos =0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // Initialize the Serial Monitor
pinMode(IRSensora, INPUT); // IR Sensor pin INPUT
doorLock.attach(4); // attaches the servo on pin 4 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  float ldr_value = analogRead(LDR_PIN);
  int sensorstatus2= analogRead(IRSensora);
  int dist = map(sensorstatus2, 0, 4095, 0, 25);
  char keyPressed = keypad.getKey();
  if (keyPressed != NO_KEY) {
//  Serial.print("*"); // Mask the entered password
  delay(100);
  char password[5];
  int i = 0;
  while (i < 4) {
    if (keyPressed != NO_KEY && keyPressed != '#' && keyPressed != '*') {
      password[i] = keyPressed;
      i++;
      Serial.print("*");
    }
    keyPressed = keypad.getKey();
    delay(100);
  }

    password[i] = '\0';
    if (strcmp(password, "1234") == 0) { // Pre-defined correct password
      Serial.println("\nPassword Correct");
     // doorLock.write(180);
     // delay(5000);
     // doorLock.write(0);
     for (pos = 0; pos <= 180; pos ++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    doorLock.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos --) { // goes from 180 degrees to 0 degrees
    doorLock.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
      Serial.print("Light Intensity: ");
      lux=(250.000000/(ADC_value*ldr_value))-50.000000;
      Serial.print(lux);
      Serial.println(" Lux");
      Serial.print("Proximity: ");
      Serial.print(dist);
    } else {
      Serial.println("\nPassword Incorrect");
    }
  }
  
}
