#include <FirebaseJson.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
Adafruit_BME280 bme;
#define SEALEVELPRESSURE_HPA (1013.25)

#define RXp2 16
#define TXp2 17

// anan 3yza ab3at el message json m3raf4 leh gat f dma8i
FirebaseJson json_msg;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  else {
    Serial.println("BME280 initialized");
  }

  if (!aht.begin(&Wire, 0, 0x38)) {
    Serial.println("Could not find a valid AHT21B sensor, check wiring!");
    while (1);
  }
  else {
    Serial.println("AHT12B initialized");
  }
}

void loop() {
  float pressure_hpa = bme.readPressure() / 100.0F;

  sensors_event_t temp_event, humidity_event;
  aht.getEvent(&humidity_event, &temp_event);
  float temp_c = temp_event.temperature;

  json_msg.add("pressure",pressure_hpa);
  json_msg.add("temperature",temp_c);
  
  json_msg.toString(Serial2,false);
  Serial2.print("\n");
  json_msg.clear();
  delay(1000);
}
