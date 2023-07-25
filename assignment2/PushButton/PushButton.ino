#define LED_PIN 2
#define BUTTON_PIN 13

// setup code, to run once:
void setup() {

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

}

// main code, to run repeatedly:
void loop() {

  int buttonvalue = digitalRead(BUTTON_PIN);
  
  if(buttonvalue == HIGH) {
    Serial.println("not pressed");
    Serial.println(buttonvalue);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    Serial.println("pressed");
    Serial.println(buttonvalue);
    digitalWrite(LED_PIN, HIGH);
  }
  

}
