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
int irsensor;
String IR_path = "/irsensor";
//String humPath = "/humidity";
String timePath = "/timestamp";

// // Ds18B20 Temperature sensor
// // GPIO where the DS18B20 is connected to
// const int oneWireBus = 4;
// // Setup a oneWire instance to communicate with any OneWire devices
// OneWire oneWire(oneWireBus);

// // Pass our oneWire reference to Dallas Temperature sensor
// DallasTemperature sensors(&oneWire);

// Parent Node (to be updated in every loop)
String parentPath;

int timestamp;
FirebaseJson json;

// Network time Protocl Server
const char* ntpServer = "pool.ntp.org";

// Capacitive Soil Moisture Sensor Temperature sensor
// GPIO where the Capacitive Soil Moisture Sensor is connected to
int sensorPin = 34;

//float temperature;
//float humidity;

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
  databasePath = "/UsersData/" + uid + "/readings";
}

void loop() {

  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    //Get current timestamp
    timestamp = getTime();
    Serial.print("time: ");
    Serial.println(timestamp);
    // Serial.print("IR Value: ");
    // Serial.println(irsensor);

    parentPath = databasePath + "/" + String(timestamp);

    // humidity = analogRead(sensorPin);
    // humidity = (humidity/4095)*100;
    // temperature = sensors.getTempCByIndex(0);
    
    irsensor = 30;

    json.set(IR_path.c_str(), irsensor);
    // json.set(humPath.c_str(), String(humidity));
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    delay(5000);
    Serial.printf("Get int... %s\n", Firebase.RTDB.getInt(&fbdo, String(parentPath + "/irsensor")) ? "got new IR Value" : fbdo.errorReason().c_str());
    int get_IR = fbdo.to<int>();
    Serial.println(get_IR);
    Serial.println("-------------------------------------");

    String deletePath = databasePath + "/" + "1691877225";

    if (Firebase.RTDB.deleteNode(&fbdo, deletePath.c_str())) {
      Serial.println("Node deleted successfully");
    } else {
      Serial.println("Error deleting node"); 
      Serial.println(fbdo.errorReason());
    }

    String updatePath = databasePath + "/" + "1691877225";

    json.set(IR_path.c_str(), irsensor);
    // json.set(humPath.c_str(), String(humidity));
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, updatePath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    delay(5000);



    
  }
}
