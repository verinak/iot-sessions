#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"
#include "addons/TokenHelper.h" // Provide the token generation process info.
#include "addons/RTDBHelper.h" // Provide the RTDB payload printing info and other helper functions.


#define WIFI_SSID "nagui labib"
#define WIFI_PASSWORD "naguilabib#31"
#define DATABASE_URL "https://bagarab-fih-default-rtdb.firebaseio.com/"

#define API_KEY "AIzaSyCTpd8btoHtv7Qei9RKZj14KESSMI-co0I"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "verinamichelk@gmail.com"
#define USER_PASSWORD "123456"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int timestamp;
FirebaseJson json;
String uid;

// Network time Protocl Server
const char* ntpServer = "pool.ntp.org";


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

void setup() {
  Serial.begin(115200);

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

  // ba7awel azabat eno y7es lma redings gdida tewsal
  Firebase.RTDB.setStreamCallback(&fbdo, streamCallback, streamTimeoutCallback);

  if (!Firebase.RTDB.beginStream(&fbdo, "/inputs"))
  {
    // Could not begin stream connection, then print out the error detail
    Serial.println(fbdo.errorReason());
  }

}

// Global function that handles stream data
void streamCallback(FirebaseStream data)
{

  // Print out all information

//  Serial.println("Stream Data...");
//  Serial.println(data.streamPath());
//  Serial.println(data.dataPath());
//  Serial.println(data.dataType());

  // Print out the value
  // Stream data can be many types which can be determined from function dataType
  // kan fi if else if ktir 34an y3adi 3al data types kolaha bs ana 4eltaha
  
  if (data.dataTypeEnum() == fb_esp_rtdb_data_type_json)
  {
      FirebaseJson *json = data.to<FirebaseJson *>();
      //Serial.println(json->raw());
      
      FirebaseJsonData result;
      json -> get(result,"message");
      if(result.success)
      {
        Serial.print("Message: ");
        Serial.print(result.to<String>()); 
      }
      json -> get(result,"timestamp");
      if(result.success)
      {
        Serial.print("\nTimestamp: ");
        Serial.print(result.to<String>()); 
      }
      Serial.print("\n");
  }
  else if (data.dataTypeEnum() == fb_esp_rtdb_data_type_array)
  {
      FirebaseJsonArray *arr = data.to<FirebaseJsonArray *>();
      Serial.println(arr->raw());
  }
     

}

// Global function that notifies when stream connection lost
// The library will resume the stream connection automatically
void streamTimeoutCallback(bool timeout)
{
  if(timeout){
    // Stream timeout occurred
    Serial.println("Stream timeout, resume streaming...");
  }  
}



void loop() {

  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    
    sendDataPrevMillis = millis();

  }
}
