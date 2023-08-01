#include <LiquidCrystal.h>/
LiquidCrystal lcd(19,23,18,17,16,15);
int IRSensora = 34 ;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  pinMode(IRSensora, INPUT); // IR Sensor pin INPUT

}

void loop() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("real_time dist:");

  int sensorstatus2= analogRead(IRSensora);
  if(sensorstatus2<10||sensorstatus2>4000){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor disconnected");}
  int dist = map(sensorstatus2, 0, 4095, 0, 25);
  lcd.setCursor(2, 1);
  lcd.print(dist);
  Serial.println(dist);
  delay(10);
 
}


/* 
#
#  1 - Vss ground
#  2 - VDD - voltage
#  3 - VE (Contrast voltage) - potentiometer
#  4 - RS (Register Select) connect to G19 
#  5 - RW (Read/Write) - connect to ground
#  6 - EN (Enable) connect to G23 
#  7 - D0 - leave unconnected
#  8 - D1 - leave unconnected
#  9 - D2 - leave unconnected
# 10 - D3 - leave unconnected
# 11 - D4 - connect to G18 (as per call to GpioLcd)
# 12 - D5 - connect to G17 (as per call to GpioLcd)
# 13 - D6 - connect to G16 (as per call to GpioLcd)
# 14 - D7 - connect to G15 (as per call to GpioLcd)
# 15 - A (BackLight Anode) - Connect to VIN
# 16 - K (Backlight Cathode) - Connect to Ground
*/
