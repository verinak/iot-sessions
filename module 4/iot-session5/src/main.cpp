/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 *
 * Copyright (c) 2023 mobizt
 *
 */

/** This example will show how to authenticate as a user with Email and password.
 *
 * You need to enable Email/Password provider.
 * In Firebase console, select Authentication, select Sign-in method tab,
 * under the Sign-in providers list, enable Email/Password provider.
 *
 * From this example, the user will be granted to access the specific location that matches
 * the user uid.
 *
 * This example will modify the database rules to set up the security rule which need to
 * guard the unauthorized access with the user Email.
 */
#include <Arduino.h>
#include <Keypad.h> /* Included keypad library */

#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Mirna"
#define WIFI_PASSWORD "yoxw0136"

/** 2. Define the API key
 *
 * The API key (required) can be obtained since you created the project and set up
 * the Authentication in Firebase console. Then you will get the API key from
 * Firebase project Web API key in Project settings, on General tab should show the
 * Web API Key.
 *
 * You may need to enable the Identity provider at https://console.cloud.google.com/customer-identity/providers
 * Select your project, click at ENABLE IDENTITY PLATFORM button.
 * The API key also available by click at the link APPLICATION SETUP DETAILS.
 *
 */
#define API_KEY "AIzaSyB6gXcrJJTvQLTfifbLMIdo6F2Y6MvLKqs"

/* 3. Define the user Email and password that already registerd or added in your project */
#define USER_EMAIL "mirnatarek111@gmail.com"
//#define USER_PASSWORD "123456"

/* 4. If work with RTDB, define the RTDB URL */
// #define DATABASE_URL "URL" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/** 5. Define the database secret (optional)
 *
 * This database secret needed only for this example to modify the database rules
 *
 * If you edit the database rules yourself, this is not required.
 */

/* 6. Define the Firebase Data object */
FirebaseData fbdo;

/* 7. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 8. Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

// keypad

#define ROW_NUM 4 /* Define keypad Rows */
#define COLUMN_NUM 4 /* Define keypad Columns */

char keys[ROW_NUM][COLUMN_NUM] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUM] = {5, 18, 19, 21}; // ESP32GPIO pins for Rows
byte pin_column[COLUMN_NUM] = {12, 13, 14, 15}; //ESP32 GPIO pins for Columns

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup()
{

    Serial.begin(115200);

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    multi.addAP(WIFI_SSID, WIFI_PASSWORD);
    multi.run();
#else
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

    Serial.print("Connecting to Wi-Fi");
    unsigned long ms = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
        if (millis() - ms > 10000)
            break;
#endif
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    //auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL */
    // config.database_url = DATABASE_URL;

    // The WiFi credentials are required for Pico W
    // due to it does not have reconnect feature.
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    config.wifi.clearAP();
    config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);

  /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);

    Serial.print("Enter your password.");
    


}

void loop()
{

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
        Serial.println("---------------------");
  
    }

  }

  
}