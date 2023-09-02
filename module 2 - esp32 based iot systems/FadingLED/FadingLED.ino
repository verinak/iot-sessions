#include <Preferences.h>

// 25 26 27 23 .. azon ay 7aga pmw tenfa3 ll analogwrite?
# define ledPin 2
# define potPin 34 

void setup() {
  // put your setup code here, to run once:
  
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int potValue = analogRead(potPin);
  int ledBrightness= map(potValue, 0, 4095, 0, 255);
  Serial.println(potValue);
  Serial.println(ledBrightness);
  analogWrite(ledPin, ledBrightness);
  delay(10);
  
}
