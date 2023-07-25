// define led and push button pins
#define LED_PIN 2
#define BUTTON_PIN 13

// setup code, to run once:
void setup() {

  // set baud rate
  Serial.begin(9600);
  // initialize led as output and button as pullup input
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

}

// main code, to run repeatedly:
void loop() {

  // read button input
  // high == button is not peressed, low == button is pressed
  int buttonvalue = digitalRead(BUTTON_PIN);

  if(buttonvalue == HIGH) {
    Serial.println("not pressed");
    Serial.println(buttonvalue);
    digitalWrite(LED_PIN, LOW); // turn off led if button is not pressed
  }
  else {
    Serial.println("pressed");
    Serial.println(buttonvalue);
    digitalWrite(LED_PIN, HIGH);  // turn on led if button is pressed
  }
  

}
