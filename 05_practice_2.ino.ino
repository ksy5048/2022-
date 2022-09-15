#define PIN_LED 7
unsigned int on, off;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  on = 0;
  off = 1;
  digitalWrite(PIN_LED, on);
  delay(1000);
}

void loop() {
  digitalWrite(PIN_LED, off);
  delay(300);
  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_LED, on);
    delay(300);
    digitalWrite(PIN_LED, off);
    delay(300);
  }
  while(1) {
    digitalWrite(PIN_LED, off);
  }
}
