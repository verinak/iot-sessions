#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 5, 18, 19, 21);
// Custom character definition for heart symbol (❤)
byte heart[8] = {
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};


void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.createChar(0, heart);  // Load the heart symbol to custom character index 0
  lcd.clear();
  
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(" I ");
  lcd.write(byte(0)); // Write the custom character
  lcd.setCursor(0, 1);
  lcd.print("IOT Training");
}
