# define enA 14
# define in1 27
# define in2 26

// velocity in mm/ms
const double VELOCITY = 240.0/4100;
int bpm = 12;
int breath_ms;
int first_delay;

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

void setup() {
  Serial.begin(115200);
  Serial.println("setting up...");

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // turn motor off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // use maximum speed
  analogWrite(enA, 255);
}

void loop() {
  // haraga3o lw m4 rage3 ?
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(4100);

  // wait 2 seconds
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(2000);
  
  breath_ms = 60000/bpm;
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

  // azon lw fi firebase ba2a hagi fl listener da aw ayan kan w awel ma ygilo message y8ayar el bpm w ye7seb el 7aga tani..
  // ba3den yetfi w ne3mel method ba2a btraga3o w tma4ih 7etet el delay w keda..
  while(true) {
    breathOnce(breath_ms);
  }
}
