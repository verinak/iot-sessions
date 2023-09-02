#include <LiquidCrystal.h>
//#include <FirebaseJson.h>
#include <ArduinoJson.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//FirebaseJson received_json;
JsonObject obj;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  StaticJsonDocument<48> doc;
  
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    deserializeJson(doc, msg);
    Serial.println(msg);
    //serializeJsonPretty(doc, Serial);
    //Serial.println();
    //received_json.setJsonData(msg);
  }
  lcd.clear();
  
//  FirebaseJsonData result;
//
//  received_json.get(result, "pressure");
//  if (result.success) {
//    lcd.setCursor(0,0);
//    lcd.print("P: ");
//    lcd.print(result.to<String>());
//    lcd.print(" hPa");
//  }
//  received_json.get(result, "temperature");
//  if (result.success) {
//    lcd.setCursor(0,1);
//    lcd.print("T: ");
//    lcd.print(result.to<String>());
//    lcd.print(" *C");
//  }
  float pressure = doc["pressure"];
  float temperature = doc["temperature"];

  
  lcd.setCursor(0,0);
  lcd.print("P: ");
  lcd.print(pressure);
  lcd.print(" hPa");

  lcd.setCursor(0,1);
  lcd.print("T: ");
  lcd.print(temperature);
  lcd.print(" *C");
  
  delay(1000);
}
