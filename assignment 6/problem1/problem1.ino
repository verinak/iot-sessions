#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"
#include <LiquidCrystal.h>
//#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

LiquidCrystal lcd(22, 23, 5, 18, 19, 21);


Servo servo;
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "nagui labib"
#define WIFI_PASSWORD "naguilabib#31"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB6gXcrJJTvQLTfifbLMIdo6F2Y6MvLKqs"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "verinamichelk@gmail.com"
//#define USER_PASSWORD "123456"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://session5-179dc-default-rtdb.firebaseio.com/"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
int irsensor;
String IR_path = "/irsensor";
String timePath = "/timestamp";

// Parent Node (to be updated in every loop)
String parentPath;

int timestamp;
FirebaseJson json;

// Network time Protocl Server
const char* ntpServer = "pool.ntp.org";

// Capacitive Soil Moisture Sensor Temperature sensor
// GPIO where the Capacitive Soil Moisture Sensor is connected to
int sensorPin = 34;


// Timer variables (send new readings every thirt seconds)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 5000;


// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("\nConnected Successfully\nIp is: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    // Serial.println("Failed to obtain time");
    return (0);
  }
  time(&now);
  return now;
}
unsigned long dataMillis = 0;
#define ROW_NUM 4 /* Define keypad Rows */
#define COLUMN_NUM 4 /* Define keypad Columns */

char keys[ROW_NUM][COLUMN_NUM] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUM] = {13, 12, 14, 27}; /* Initialized ESP32
Pins for Rows */
byte pin_column[COLUMN_NUM] = {26, 25, 33, 32}; /* Initialized
ESP32 Pins for Columns */
#include <Keypad.h> /* Included keypad library */
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  Serial.begin(115200);
  lcd.begin(16,2);
  servo.attach(4);
  pinMode(sensorPin, INPUT);

  //start Wifi
  initWiFi();

  //Configure times
  configTime(0, 0, ntpServer);

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  //auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

   Serial.print("Enter your password.");
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter pass: ");

}
void loop() {

  char keyPressed = keypad.getKey();
      char password[7];

  if (keyPressed != NO_KEY) {
//  Serial.print("*"); // Mask the entered password
  delay(100);
  int i = 0;
  while (i < 6) {
    if (keyPressed != NO_KEY && keyPressed != '#' && keyPressed != '*') {
      password[i] = keyPressed;
      i++;
      Serial.print("*");
    }
    keyPressed = keypad.getKey();
    delay(100);
  }

    password[i] = '\0';
    
    Serial.println(password);
    auth.user.password = password;
    Firebase.begin(&config, &auth);


    // Firebase.ready() should be called repeatedly to handle authentication tasks.

    if (millis() - dataMillis > 5000 && Firebase.ready())
    {
        dataMillis = millis();
        Serial.println(auth.token.uid.c_str());
        uid = auth.token.uid.c_str();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(uid);
        Serial.println("---------------------");
  
    }
    
  // Update database path
  databasePath = "/UsersData/" + uid + "/readings";
}

  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    //Get current timestamp
    timestamp = getTime();
//    Serial.print("time: ");
//    Serial.println(timestamp);
    // Serial.print("IR Value: ");
    // Serial.println(irsensor);

    parentPath = databasePath + "/" + String(timestamp);

    int idx = 1;
    
    irsensor = analogRead(sensorPin);
    int dist = map(irsensor, 0, 4095, 0, 25);
    IR_path = "/reading" + String(idx);
    
    json.set(IR_path.c_str(), dist);
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    idx++;
    delay(3000);
    Serial.printf("Get int... %s\n", Firebase.RTDB.getInt(&fbdo, String(parentPath + IR_path)) ? "got new IR Value" : fbdo.errorReason().c_str());
    //Serial.println(dist);
    int get_IR = fbdo.to<int>();
    Serial.println(get_IR);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Data Added: ");
    lcd.print(get_IR);
    lcd.setCursor(0,1);
    lcd.print("1-update, 2-append, 3-delete, #-skip");
    int servoValue = map(get_IR, 0, 25, 0, 180);
    servo.write(servoValue);

    Serial.println("Choose what to do next: (1-update, 2-append, 3-delete, #-skip");
    
    do {

    keyPressed = keypad.getKey();

    String new_path;
    switch(keyPressed) {

       case '1':
         irsensor = analogRead(sensorPin);
         dist = map(irsensor, 0, 4095, 0, 25);
         idx--;
         IR_path = "/reading" +  String(idx);
          json.set(IR_path.c_str(), dist);
          Serial.printf("update node... %s\n", Firebase.RTDB.updateNode(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
          Serial.println(dist);
          idx++;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Data Updated: ");
          lcd.print(dist);
          lcd.setCursor(0,1);
          lcd.print("1-update, 2-append, 3-delete, #-skip");
          servoValue = map(dist, 0, 25, 0, 180);
          servo.write(servoValue);
          delay(3000);
         
         break;

      case '2':

          irsensor = analogRead(sensorPin);
          dist = map(irsensor, 0, 4095, 0, 25);
          IR_path = "/reading" +  String(idx);
          json.set(IR_path, dist);
          Serial.printf("update node... %s\n", Firebase.RTDB.updateNode(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
          Serial.println(dist);
          idx++;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Data Appended: ");
          lcd.print(dist);
          lcd.setCursor(0,1);
          lcd.print("1-update, 2-append, 3-delete, #-skip");
          servoValue = map(dist, 0, 25, 0, 180);
          servo.write(servoValue);
          delay(3000);
         
         break;

      case '3':
          idx--;
          IR_path = "/reading" +  String(idx);
          new_path = databasePath + "/" + timestamp + IR_path;
         if (Firebase.RTDB.deleteNode(&fbdo, new_path.c_str())) {
          Serial.println("Node deleted successfully");
          json.clear();

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Data Deleted");
          lcd.setCursor(0,1);
          lcd.print("1-update, 2-append, 3-delete, #-skip");  
        } else {
          Serial.println("Error deleting node"); 
          Serial.println(fbdo.errorReason());
        }
         break;

    }
    }
    while(keyPressed != '#');
    json.clear();
    
    Serial.println("-------------------------------------");
  }
}
