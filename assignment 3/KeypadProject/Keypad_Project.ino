#include <ESP32Servo.h> 
#include <Keypad.h>

// Keypad pins
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {21,19,18,5}; 
byte colPins[COLS] = {12,13,14,15};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Servo pin 
#define SERVO_PIN 4

Servo servo; 

// Angle variables
int angle = 0;

void setup() {
  Serial.begin(115200);


  // Attach servo 
  servo.attach(SERVO_PIN);
}

void loop() {
  // Get key press
  char key = keypad.getKey();
  
  if (key =='1')
  {
    Serial.println(key);
    angle = 45;
      servo.write(angle);
    delay(10);
  } 
  
  else if (key == '2'){
        Serial.println(key);

    angle = 90;
      servo.write(angle);

    delay(10);
  } else if (key == '3'){
        Serial.println(key);

     angle = 60;
       servo.write(angle);

     delay(10);
  } else if (key == 'A'){
        Serial.println(key);

    angle = 30;
      servo.write(angle);

    delay(10);
  } else if (key == 'B'){
        Serial.println(key);

    angle = 120;
      servo.write(angle);

    delay(10);
  } else if (key == 'C'){
        Serial.println(key);

    angle = 180;
      servo.write(angle);

    delay(10);
  } else if (key == '#'){ //Reset the angle
        Serial.println(key);

    angle = 0;
      servo.write(angle);

    delay(10); // Reset
  } 
  else if (key == 'D'){
    Serial.print("Enter custom angle: ");
      while (!Serial.available()); // Wait for user input
      angle = Serial.parseInt(); // Read the custom angle from serial monitor
       Serial.println(key);
       if (angle >= 0 && angle <= 180) { // If the angle is valid
      Serial.print("Angle entered: ");
      Serial.println(angle); // Print the angle to serial monitor
      servo.write(angle); // Set the servo to the specified angle
       }
  }

  else if(key == '*')
  {
        Serial.println(key);
    // Stop
    angle = angle; 
    servo.write(angle); 
  }
  }
