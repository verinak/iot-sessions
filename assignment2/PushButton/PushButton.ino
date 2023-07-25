#define LED_PIN 2
#define BUTTON_PIN 13
// Define the pins used for the LED and button

// setup code, to run once:
void setup() {

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

}

// main code, to run repeatedly:
void loop() {

  int buttonvalue = digitalRead(BUTTON_PIN);
  // Read the value of the button
  
  if(buttonvalue == HIGH) {
    // If it is not pressed, turn off the LED and print a message to the serial console
    Serial.println("not pressed");
    Serial.println(buttonvalue);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    // If it is pressed, turn on the LED and print a message to the serial console
    Serial.println("pressed");
    Serial.println(buttonvalue);
    digitalWrite(LED_PIN, HIGH);
  }
  

}
