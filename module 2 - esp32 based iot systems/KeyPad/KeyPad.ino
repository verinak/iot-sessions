#include <Keypad.h>

#define ROW_NUM 4 /* Define keypad Rows */
#define COLUMN_NUM 4 /* Define keypad Columns */

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {21, 19, 18, 5}; /* Initialized ESP32
Pins for Rows */
byte pin_column[COLUMN_NUM] = {12, 13, 14, 15}; /* Initialized
ESP32 Pins for Columns */

/* Function for keypad */
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column,
ROW_NUM, COLUMN_NUM);

void setup() {
  Serial.begin(115200); /* Baud Rate for Serial Communication */
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  char key = keypad.getKey(); /* Take input from
  keypad */
  if (key) {
    /* If Key is pressed
  display the output */
    Serial.println(key);

    switch(key) {

       case '1':
         digitalWrite(LED_BUILTIN, HIGH);
         break;

      case '2':
         digitalWrite(LED_BUILTIN, LOW);
         break;

      case '3':
         digitalWrite(LED_BUILTIN, HIGH);
         break;

      case '4':
         digitalWrite(LED_BUILTIN, LOW);
         break;

      case '5':
         digitalWrite(LED_BUILTIN, HIGH);
         break;

      case '6':
         digitalWrite(LED_BUILTIN, LOW);
         break;

      case '7':
         digitalWrite(LED_BUILTIN, HIGH);
         break;

      case '8':
         digitalWrite(LED_BUILTIN, LOW);
         break;

      case '9':
         digitalWrite(LED_BUILTIN, HIGH);
         break;

      case '0':
         digitalWrite(LED_BUILTIN, LOW);
         break;

    }
  }
}
