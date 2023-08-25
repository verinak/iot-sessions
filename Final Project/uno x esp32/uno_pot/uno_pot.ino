// for mango uno


# define potPin A0

void setup() {
  
  Serial.begin(9600);
  
  pinMode(potPin, INPUT);


}

void loop() {

  int sensorReading = analogRead(potPin);
  Serial.println(sensorReading);
  delay(500);

}
