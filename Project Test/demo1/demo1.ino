#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"
#include "addons/TokenHelper.h" // Provide the token generation process info.
#include "addons/RTDBHelper.h" // Provide the RTDB payload printing info and other helper functions.


#define WIFI_SSID "Big mac"
#define WIFI_PASSWORD "amany2004&"
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

// motor driver pins
# define enA 14
# define in1 27
# define in2 26

// velocity in mm/ms
const double VELOCITY = 240.0/4100;
int bpm_input = -1;
int breath_ms;
int first_delay;
boolean flag = false;

int getFirstDelay() {
 double breath_dist = (VELOCITY*breath_ms)/2.0;
 double remaining_dist = 240 - breath_dist;
 int delay_time = remaining_dist/VELOCITY;
 Serial.print("First Delay: ");
 Serial.print(delay_time);
 Serial.print("\n");
 return delay_time;
}

void breathOnce(int breath_time) {
  // go forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  delay(breath_time/2);
  
  // go backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  delay(breath_time/2);
  
}

void setupVent() {
  // haraga3o lw m4 rage3 ?
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(4100);

  // wait 2 seconds
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(2000);
  
  breath_ms = 60000/bpm_input;
  Serial.print("Breath Time: ");
  Serial.print(breath_ms);
  Serial.print("\n");
  
  first_delay = getFirstDelay();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(first_delay);

  // wait 2 seconds
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(2000);
}

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

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // turn motor off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // use maximum speed
  analogWrite(enA, 255);

}

// Global function that handles stream data
void streamCallback(FirebaseStream data)
{
  flag = false;
  if (data.dataTypeEnum() == fb_esp_rtdb_data_type_json)
  {
      FirebaseJson *json = data.to<FirebaseJson *>();
      //Serial.println(json->raw());
      
      FirebaseJsonData result;
      json -> get(result,"timestamp");
      if(result.success)
      {
        Serial.print("Timestamp: ");
        Serial.print(result.to<String>()); 
        Serial.print("\n");
      }
      json -> get(result,"bpm");
      if(result.success)
      {
        bpm_input = result.to<int>();
        Serial.print("BPM: ");
        Serial.print(bpm_input);
        Serial.print("\n");
        setupVent();
        flag = true;
      }
      
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

  if (Firebase.ready()) {
     if(millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0) {
          sendDataPrevMillis = millis();
     }
  }
  if(flag == true) {
    breathOnce(breath_ms);
  }
}
