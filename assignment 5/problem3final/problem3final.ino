#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"


// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "nagui labib"
#define WIFI_PASSWORD "naguilabib#31"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBVfZVc5leaSlyXwdL8zllqHENwKBKHF1o"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "verinamichelk@gmail.com"
#define USER_PASSWORD "123456"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://assignment-5-problem-3-default-rtdb.firebaseio.com/"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String message_path = "/message";
String time_path = "/timestamp";

// Parent Node (to be updated in every loop)
String parentPath;

int timestamp;
String message;
FirebaseJson json;

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

  // Start the DS18B20 sensor
  // sensors.begin();

  //start Wifi
  initWiFi();

  //Configure times
  configTime(0, 0, ntpServer);

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
  // Serial.println(String(Firebase.getToken()));
  // Update database path
  databasePath = "/UsersData/" + uid + "/input";
}

void loop() {

  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    //Get current timestamp
    timestamp = getTime();
    Serial.print("time: ");
    Serial.println(timestamp);

    parentPath = databasePath + "/" + String(timestamp);

    // write to database
    
    message = ":(";

    json.set(message_path.c_str(), message);
    json.set(time_path, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    delay(5000);


    // read from database
    
    Serial.printf("Get string... %s\n", Firebase.RTDB.getString(&fbdo, String(parentPath + "/message")) ? "read new message" : fbdo.errorReason().c_str());
    String get_msg = fbdo.to<String>();
    Serial.println(get_msg);
    Serial.println("-------------------------------------");
    delay(3000);


    // update in database
    message = ":)";

    json.set(message_path.c_str(), message);
    json.set(time_path, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    delay(3000);

    // read from database
    
    Serial.printf("Get string... %s\n", Firebase.RTDB.getString(&fbdo, String(parentPath + "/message")) ? "read new message" : fbdo.errorReason().c_str());
    get_msg = fbdo.to<String>();
    Serial.println(get_msg);
    Serial.println("-------------------------------------");
    delay(3000);


    // delete from database
    
    if (Firebase.RTDB.deleteNode(&fbdo, parentPath.c_str())) {
      Serial.println("Node deleted successfully");
    } else {
      Serial.println("Error deleting node"); 
      Serial.println(fbdo.errorReason());
    }
    delay(3000);

    



    
  }
}
