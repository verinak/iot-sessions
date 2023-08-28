#define LDR_PIN 35
#define BUZZER_PIN 4
int irPinDigital = 2;  
int irPinAnalog = 34;  
int irStat=0; 
int ledPin = 12; 
int light_threshold = 4000;

const int Password_Length = 5; // Length of the password
char Master[Password_Length + 1] = "1234"; // Master password
int count = 0;


Servo myservo;
int pos = 0;  

bool door = true; // 1 - Closed, 0 - Open
char Data[Password_Length];
int data_count = 0;

LiquidCrystal lcd(22, 23, 16, 17, 27, 26);
// Keypad pins
const byte ROWS = 4; const byte COLS = 4;
char keys[ROWS][COLS] = {  {'1','2','3','A'},
  {'4','5','6','B'},  {'7','8','9','C'},
  {'*','0','#','D'}};
byte rowPins[ROWS] = {21,19,18,5}; byte colPins[COLS] = {12,13,14,15};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup() 
{  Serial.begin(115200); 
  myservo.write(0);    
  myservo.attach(4);
  lcd.begin(16, 2);
  lcd.clear();   
  pinMode(ledPin, OUTPUT);  
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
  pinMode(irPinDigital, INPUT);  
  pinMode(irPinAnalog, INPUT);    
  pinMode(BUZZER_PIN, OUTPUT);
}
void loop() {  
  lcd.setCursor(0, 0);
  lcd.print("Choose 1 or 2 or 3 or 4");  // Get key press
  char key = keypad.getKey();  
  if (key =='1')  {
     //ir sensor part    irStat = analogRead(irPinAnalog);  
    int dist = map(irStat, 0, 4095, 0, 25);    
    Serial.println(dist);  
    lcd.setCursor(0, 0);     
    lcd.print(" Distance is "); 
    lcd.setCursor(0, 1);     
    lcd.print(dist);
    //ldr sensor part
    int ldr_value = analogRead(LDR_PIN);    
    Serial.println(ldr_value);
    if(ldr_value < light_threshold) {       // If it is not pressed
      Serial.println("light off");       
      digitalWrite(ledPin, HIGH);
      tone(BUZZER_PIN, 1000);       
      lcd.setCursor(2, 1);
      lcd.print("Light OFF");    } 
    else {       // If it is pressed 
      Serial.println("light on");       
      Serial.println(buttonvalue); 
      digitalWrite(ledPin, LOW);       
      noTone(BUZZER_PIN);
      lcd.setCursor(2, 1);       
      lcd.print(ldr_value);
      }  } 
             
             
    else if (key == '2'){
         for (pos = 0; pos <= 180; pos++) {         
           myservo.write(pos);
           Serial.println(pos);      
           delay(20); }                         
          for (pos = 180; pos >= 0; pos--) {   
              myservo.write(pos);  
              Serial.println(pos);                       
           delay(20);  }}
             
    else if (key == '4'){
      irStat = analogRead(irPinAnalog);    
      int dist = map(irStat, 0, 4095, 0, 25); 
      if (dist <= 20){                
       Serial.println("Motion Detected");    
       Serial.println(dist); 
       if(pos <= 0) {
        for (pos = 0; pos <= 180; pos++) {        
         myservo.write(pos);               
         delay(20);                            
     }
     delay(1000);   }
      }}
  if(dist > 20 & pos >= 180) {     
    for (pos = 180; pos >= 0; pos--) {  
      myservo.write(pos);                      
      delay(20); 
     } }
       
  else if (key == '3'){  
    Serial.println("Please enter the password");
    char customKey = keypad.getKey();
    if (customKey) {
      Data[data_count] = customKey;
      Serial.print("*");
      data_count++;
    }

    if (data_count == Password_Length - 1) {
      Data[data_count] = '\0';

      if (!strcmp(Data, Master)) {
        for (pos = 0; pos <= 180; pos ++) {
    myservo.write(pos);
    delay(15);
  }
    delay(500);
      }
   }

  }
 }
