#include<LiquidCrystal.h>
#include <ESP32Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h> 
#define trigPin 12
#define echoPin 14
#define buzzerPin 27
#define ledPin 25
#define ONE_WIRE_BUS 13

LiquidCrystal lcd(19,23,18,17,16,15);
 // RS, EN, D4, D5, D6, D7
Servo myservo;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  myservo.attach(26);
  sensors.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
}

void loop() {
  long duration, distance;
  float temperature;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.print(" cm");
 
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  lcd.setCursor(6, 1);
  lcd.print(temperature);
  lcd.print(" C  ");
  
  if (distance < 10 || temperature > 30) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
    lcd.setCursor(0, 1);
    lcd.print("WARNING: Obstacle");
    if (temperature > 30) {
      lcd.setCursor(0, 1);
      lcd.print("/High Temp");
    }
    myservo.write(0);
    delay(500);
    myservo.write(90);
    delay(500);
    myservo.write(180);
    delay(500);
    myservo.write(90);
    delay(500);
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    lcd.setCursor(0, 1);
    lcd.print("                    ");
  }
}
