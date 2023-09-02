int IRSensord = 2; 
int IRSensora = 34 ;
void setup(){
  Serial.begin(115200); // Init Serial at 115200 Baud Rate.
  Serial.println("Serial Working"); // Test to check if serial is working or not
  pinMode(IRSensord, INPUT); // IR Sensor pin INPUT
}

void loop(){
  int sensorStatus = digitalRead(IRSensord); // Set the GPIO as Input
  int sensorstatus2= analogRead(IRSensora);
  int dist = map(sensorstatus2, 0, 4095, 0, 25);
  Serial.println(dist);
  
  if (sensorStatus == 1) // Check if the pin high or not
  {
   
    Serial.println("Motion Detected!"); // print Motion Detected! on the serial monitor window
    delay(40);
  }
  else  {
    
    Serial.println("Motion Ended!"); // print Motion Ended! on the serial monitor window
    delay(40);
  }
}
