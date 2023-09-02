#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_AHTX0.h>
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Viki's Galaxy A321D06"
#define WIFI_PASSWORD "NeorangNaranhi_8"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://session5-179dc-default-rtdb.firebaseio.com/" 

// Insert Firebase project API Key
#define API_KEY "AIzaSyB6gXcrJJTvQLTfifbLMIdo6F2Y6MvLKqs"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "verinamichelk@gmail.com"
#define USER_PASSWORD "123456"


// Define Firebase objects
// .... fi 2 firebasedata ??
FirebaseData stream;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Variables to save database paths
String databasePath;

int timestamp;

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

                  //
FirebaseJson json;

// Define NTP Client to get time
// Network time Protocl Server
const char* ntpServer = "pool.ntp.org";   //

// BME280 sensor
Adafruit_BME280 bme; // I2C
float humidity;
float pressure;
float temperature;


//AHTX0 sensor
Adafruit_AHTX0 aht;

// motor driver pins
# define enA 14
# define in1 27
# define in2 26

#define SEALEVELPRESSURE_HPA (1013.25)

#define RXp2 16
#define TXp2 17

  // velocity in mm/ms
  const double VELOCITY = 240.0/4100;
  int bpm_input = -1;
  int breath_ms;
  int first_delay;
  boolean flag = false;

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
  else {
        Serial.println("BME280 iniialized");
  }
}

// Initialize BME280
void initAHT(){
  if (!aht.begin(&Wire, 0, 0x38)) {
    Serial.println("Could not find a valid AHT21B sensor, check wiring!");
    while (1);
  }
  else {
        Serial.println("AHT21B iniialized");
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

void streamCallback(FirebaseStream data)
{
  
  if (data.dataTypeEnum() == fb_esp_rtdb_data_type_json)
  {
      FirebaseJson *json = data.to<FirebaseJson *>();
      //Serial.println(json->raw());
      
      FirebaseJsonData result;
//      json -> get(result,"timestamp");
//      if(result.success)
//      {
//        Serial.print("Timestamp: ");
//        Serial.print(result.to<String>()); 
//        Serial.print("\n");
//      }
      json -> get(result,"breathRate");
      if(result.success)
      {
        flag = false;
        bpm_input = (result.to<String>()).toInt();
        Serial.print("BPM: ");
        Serial.print(bpm_input);
        Serial.print("\n");
        setupVent();
        flag = true;
      }
      
  }
     
}

void streamTimeoutCallback(bool timeout)
{
  if(timeout){
    // Stream timeout occurred
    Serial.println("timeout: Stream timeout, resume streaming...");
  }  
}


// create to tasks to run in parallel....
TaskHandle_t ReadSensors;

void setup() {

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  // Initialize BME280 sensor
  initBME();
  initAHT();
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
  databasePath = "/SensorData/";

 // Update database path for sensor readings
 /*
  humPath = databasePath + "/humidity"; // --> UsersData/<user_uid>/humidity
  presPath = databasePath + "/pressure"; // --> UsersData/<user_uid>/pressure
  tempPath = databasePath + "/temperature"; // --> UsersData/<user_uid>/pressure*/
    
  Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);

  if (!Firebase.RTDB.beginStream(&stream, "/bmp"))
  {
    // Could not begin stream connection, then print out the error detail
    Serial.println("begin stream: ");
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
  
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    SensorsCode,   /* Task function. */
                    "ReadSensors",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &ReadSensors,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

}

//Task1: get sensors reading and write then to database..
void SensorsCode( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  // Timer variables (send new readings every three minutes)
  // el 2 dol lw tala3tohom fo2 el setup() el time byeb2a dyman b 0 ??????
  unsigned long sendDataPrevMillis = 0;
  unsigned long timerDelay = 5000;
  for(;;){
    
    if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    timestamp =  getTime();
    Serial.print ("time: ");
    Serial.println (timestamp);

    parent_path= databasePath + "/" + String(timestamp);

    sensors_event_t temp_event, humidity_event;
     aht.getEvent(&humidity_event, &temp_event);
     float temp_c = temp_event.temperature;
     
    json.set(temperature_path.c_str(), String(temp_event.temperature));
    json.set(humidity_path.c_str(), String(humidity_event.relative_humidity));
    json.set(pressure_path.c_str(), String(bme.readPressure()/100.0F));
    json.set(time_path, String(timestamp));
    Serial.printf("Set json...%s\n",Firebase.RTDB.setJSON(&fbdo, parent_path.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());

     
//     //put at json message
//     json.add("pressure",pressure_hpa);
//    // json.add("temperature",temp_c);
//     //n7wlo lstring 
     json.toString(Serial2,false);
     Serial2.print("\n");
     json.clear();
   }
  } 
}

void loop() {
  
  if(flag == true) {
      Serial.println(flag);
      breathOnce(breath_ms);
    }
}
