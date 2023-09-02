#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

void setup() {
  Serial.println(":(!");
  Serial.begin(115200);
  Wire.begin();

  if (!aht.begin()) {
    Serial.println("Could not find a valid AHT21B sensor, check wiring!");
    while (1);
  }
}

void loop() {
  sensors_event_t temp_event, humidity_event;
  aht.getEvent(&humidity_event, &temp_event);

  if (isnan(temp_event.temperature) || isnan(humidity_event.relative_humidity)) {
    Serial.println("Failed to read from AHT21B sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp_event.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity_event.relative_humidity);
  Serial.println(" %");

  delay(2000); // Wait for 2 seconds before taking the next reading
}
