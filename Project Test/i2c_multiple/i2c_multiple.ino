#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
Adafruit_BME280 bme;

#define SEALEVELPRESSURE_HPA (1013.25)


void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  if (!aht.begin(&Wire, 0, 0x38)) {
    Serial.println("Could not find a valid AHT21B sensor, check wiring!");
    while (1);
  }
}

void loop() {


  Serial.print("BME Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");

  sensors_event_t temp_event, humidity_event;
  aht.getEvent(&humidity_event, &temp_event);
  Serial.print("AHT Temperature: ");
  Serial.print(temp_event.temperature);
  Serial.println(" °C");


  Serial.println("---------------------------------------------");
  delay(1000);
}
