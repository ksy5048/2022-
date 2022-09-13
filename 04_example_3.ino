#define PIN_LED 13
unsigned int count, toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  Serial.println("Hello World!");
  count = toggle = 0;
  digitalWrite(PIN_LED, toggle); //
}

void loop() {
  Serial.println(++count);
  toggle = toggle_state(toggle);//toggle LED value.
  digitalWrite(PIN_LED, toggle); // toggle 0이면 꺼짐, 1이면 켜짐
  delay(1000); // 1초마다 깜빡임

}
int toggle_state(int toggle){
  if(count%2==0){
    return 0;
  }else{
    return 1;
  }
}
