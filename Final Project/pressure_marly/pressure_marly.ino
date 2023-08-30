/*
  Rui Santos
  Complete project details at our blog: https://RandomNerdTutorials.com/esp32-esp8266-firebase-bme280-rtdb/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Viki's Galaxy A321D06"
#define WIFI_PASSWORD "NeorangNaranhi_8"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCTpd8btoHtv7Qei9RKZj14KESSMI-co0I"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "verinamichelk@gmail.com"
#define USER_PASSWORD "123456"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://bagarab-fih-default-rtdb.firebaseio.com/"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Variables to save database paths
String databasePath;

String temperature_path = "/temperature";
String humidity_path = "/humidity";
String pressure_path = "/pressure";
String time_path = "/epoch_time";
/*
String humPath;
String presPath;
String tempPath;*/

//Updated in every loop
String parent_path;               //

int timestamp;                  //
FirebaseJson json;

// Define NTP Client to get time
// Network time Protocl Server
const char* ntpServer = "pool.ntp.org";   //

// BME280 sensor
Adafruit_BME280 bme; // I2C
float humidity;
float pressure;
float temperature;


// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 3000;


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



// Initialize BME280
void initBME(){
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}
/*
// Write float values to the database
void sendFloat(String path, float value){
  if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), value)){
    Serial.print("Writing value: ");
    Serial.print (value);
    Serial.print(" on the following path: ");
    Serial.println(path);
    Serial.println("PASSED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}
*/
void setup(){
  Serial.begin(115200);

  // Initialize BME280 sensor
  initBME();
  initWiFi();
  configTime(0, 0, ntpServer);     //
  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
 // databasePath = "/UsersData/" + uid;
  databasePath = "/Data/" + uid;    //

 // Update database path for sensor readings
 /*
  humPath = databasePath + "/humidity"; // --> UsersData/<user_uid>/humidity
  presPath = databasePath + "/pressure"; // --> UsersData/<user_uid>/pressure
  tempPath = databasePath + "/temperature"; // --> UsersData/<user_uid>/pressure*/
  
}

void loop(){
  // Send new readings to database
  Serial.println("Enter loop");
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
      Serial.println("Enter if");
/*
    // Get latest sensor readings
    temperature = bme.readTemperature();
    humidity = bme.readHumidity();
    pressure = bme.readPressure()/100.0F;

    // Send readings to database:
    sendFloat(tempPath, temperature);
    sendFloat(humPath, humidity);
    sendFloat(presPath, pressure);
*/
    timestamp =  getTime();
    Serial.print ("time: ");
    Serial.println (timestamp);

    parent_path= databasePath + "/" + String(timestamp);

    json.set(temperature_path.c_str(), String(bme.readTemperature()));
    json.set(humidity_path.c_str(), String(bme.readHumidity()));
    json.set(pressure_path.c_str(), String(bme.readPressure()/100.0F));
    json.set(time_path, String(timestamp));
    Serial.printf("Set json...%s\n",Firebase.RTDB.setJSON(&fbdo, parent_path.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    delay(2000);
  }
}
