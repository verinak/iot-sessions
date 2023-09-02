// for esp32

#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "nagui labib"
#define WIFI_PASSWORD "naguilabib#31"

#define API_KEY "AIzaSyCTpd8btoHtv7Qei9RKZj14KESSMI-co0I"
#define DATABASE_URL "https://bagarab-fih-default-rtdb.firebaseio.com/"

#define USER_EMAIL "verinamichelk@gmail.com"
#define USER_PASSWORD "123456"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

// Variable to save USER UID
String uid;

String databasePath;
String ldrPath = "/ldrreading";
String ledPath = "/ledstatus";
String potPath = "/potreading";
String timePath = "/timestamp";
String parentPath;

// Network time Protocl Server
const char* ntpServer = "pool.ntp.org";

unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 5000;
unsigned long dataMillis = 0;


#define LED_PIN 2
#define LDR_PIN 34
#define RXp2 16
#define TXp2 17

const int light_threshold = 1000;

void initWiFi();
unsigned long getTime();
void sendSensorReadings();

void setup() {

  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  initWiFi();
  configTime(0, 0, ntpServer);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;


  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h
  config.max_token_generation_retry = 5;

  Firebase.begin(&config, &auth);
  uid = auth.token.uid.c_str();
  Serial.print("Authentication Done: ");
  Serial.print(uid);
  Serial.print("\n-------------------------------------\n");

  databasePath = "/readings/" + uid;
}

void loop() {

  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {

    sendSensorReadings();
    
  }
}

// Function to initialize WiFi
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

// Function to get sensor readings and send them to firebase
void sendSensorReadings(){

  Serial.println("Getting sensor readings..");
    int timestamp = getTime();
    // 7asa en eli bye7sal hena da habal bs m4 3arfa azabatha 8er keda..
    // 34an el arduino bykoun ba3a 100 pot value 3obal mana a7ot awel wa7da fl firebase
    Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
    String pot_value = Serial2.readStringUntil('\n');
    Serial2.end();
    int ldr_value = analogRead(LDR_PIN);
    int led_status;
    
    if(ldr_value > light_threshold){
      led_status = HIGH;
    }
    else {
      led_status = LOW;
    }
    digitalWrite(LED_PIN, led_status);

    parentPath = databasePath + "/" + String(timestamp);

    json.set(ldrPath, ldr_value);
    json.set(ledPath, led_status);
    json.set(potPath, pot_value);
    json.set(timePath, String(timestamp));

    Serial.println("Sending to Firebase...");
    if (Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json)) {
      Serial.println("Readings sent");
    } else {
      Serial.println("Error sending readings"); 
      Serial.println(fbdo.errorReason().c_str());
    }
    Serial.println("-------------------------------------");
    delay(10000);
  
}
