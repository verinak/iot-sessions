#define LED_PIN 2
#define BUZZER_PIN 18  // Define the pins used for the LED, buzzer, and LDR
#define LDR_PIN 35

int light_threshold = 500;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Initialize the serial port and configure the LED and buzzer pins


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
    
  }

  delay(100);

}
