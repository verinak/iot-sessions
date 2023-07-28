#include <ESP32Servo.h> 
Servo myservo; 
 
int ledPin = 12;                 
int irPinDigital = 2; 
int irPinAnalog = 34; 
int irStat=0;                                    
int pos = 0; 
 
void setup() { 
 pinMode(ledPin, OUTPUT);      
 pinMode(irPinDigital, INPUT); 
 pinMode(irPinAnalog, INPUT); 
 myservo.write(0);  
 myservo.attach(13);  
 Serial.begin(115200); 
} 
 
void loop(){ 
  
   irStat = digitalRead(irPinAnalog); 

  if (irStat== 0){             
   digitalWrite(ledPin, HIGH);   
    
   Serial.println("Motion Detected"); 
   
   if(pos <= 0) {
     for (pos = 0; pos <= 180; pos++) {  
      myservo.write(pos);               
      delay(20);                        
     }
     delay(1000);
   }
   
 }
 if(irStat== 1 & pos >= 180) { 
 digitalWrite(ledPin, LOW); 
     for (pos = 180; pos >= 0; pos--) {  
        myservo.write(pos);               
        delay(20); 
     }
 }
}
