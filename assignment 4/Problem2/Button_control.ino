#include <LiquidCrystal.h> 
#include <ESP32Servo.h>
#define BUTTON_PIN 13 
#define LDR_PIN 35
#define BUZZER_PIN 4  // Define the pins used for the LED, buzzer, and LDR
int light_threshold = 4000;
Servo myservo;
int pos = 0;  
LiquidCrystal lcd(22, 23, 5, 18, 19, 21); 
int irPinDigital = 2;  
int irPinAnalog = 34;  
int irStat=0; 
int ledPin = 12;  
 
void setup() { 
  Serial.begin(115200); 
  myservo.write(0);   
  myservo.attach(4);
  pinMode(ledPin, OUTPUT);  
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  lcd.begin(16, 2);
  lcd.clear(); 
  pinMode(irPinDigital, INPUT);  
  pinMode(irPinAnalog, INPUT);  
  pinMode(BUZZER_PIN, OUTPUT);
} 
 
void loop() { 

  int buttonvalue = digitalRead(BUTTON_PIN);
  if(buttonvalue == LOW) { 
    // If it is not pressed
    Serial.println("not pressed"); 
    Serial.println(buttonvalue); 
    digitalWrite(ledPin, LOW); 
    noTone(BUZZER_PIN);
    lcd.setCursor(0, 0);
    lcd.print("Angle = ");
    
     for (pos = 0; pos <= 180; pos++) {   
      myservo.write(pos);
      //Serial.println(pos);
      lcd.setCursor(0, 1); 
      lcd.print(pos); 
      delay(20);                         
     }
     for (pos = 180; pos >= 0; pos--) {   
       myservo.write(pos);  
       //Serial.println(pos);
       lcd.setCursor(0, 1); 
       lcd.print(pos);                
       delay(20);  
     }
    
  } 
  else { 
    // If it is pressed
    Serial.println("pressed"); 
    Serial.println(buttonvalue); 

    //ir sensor part
    irStat = analogRead(irPinAnalog);  
    int dist = map(irStat, 0, 4095, 0, 25);
    Serial.println(dist);  
    lcd.setCursor(0, 0); 
    lcd.print(" Distance is "); 
    lcd.setCursor(0, 1); 
    lcd.print(dist);

    //ldr sensor part
    int ldr_value = analogRead(LDR_PIN);
    Serial.println(ldr_value);
    if(ldr_value < light_threshold) { 
      // If it is not pressed
      Serial.println("light off"); 
      digitalWrite(ledPin, HIGH);
      tone(BUZZER_PIN, 1000); 
      lcd.setCursor(2, 1);
      lcd.print("Light OFF");
    } 
    else { 
      // If it is pressed 
      Serial.println("light on"); 
      Serial.println(buttonvalue); 
      digitalWrite(ledPin, LOW); 
      noTone(BUZZER_PIN);
      lcd.setCursor(2, 1); 
      lcd.print(ldr_value);
      }
      
    }
    delay(100);
    


  }
