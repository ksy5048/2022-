#include <Servo.h>

#define PIN_LED 9
#define PIN_SERVO 10
#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)
#define LOOP_INTERVAL 20   // Loop Interval (unit: msec)
#define _EMA_ALPHA 0.4
#define DIST_MIN 100     // minimum distance to be measured (unit: mm)
#define DIST_MAX 250     // maximum distance to be measured (unit: mm)

Servo myservo;
unsigned long last_loop_time;
float dist; 
float dist_prev = DIST_MAX;    // Distance last-measured
float dist_ema;
float a_value;
float a_value_ema;

void setup() {
  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(_DUTY_NEU);
  Serial.begin(57600); 
  pinMode(PIN_LED, OUTPUT);
}


void loop() {

  unsigned long time_curr = millis();
  int a_value, duty;
  
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  a_value = analogRead(A0);
  a_value_ema = (_EMA_ALPHA) * (a_value) + (1 -_EMA_ALPHA) * a_value_ema;
  
  dist = (6762.0 / (a_value-9) - 4.0) * 10.0;
  
  if(dist < DIST_MIN || dist > DIST_MAX ){
    dist = dist_prev;
    digitalWrite(PIN_LED, LOW);
    }
  else{
    dist_prev = dist;
    digitalWrite(PIN_LED, HIGH);
    }
  
   dist_ema = (_EMA_ALPHA) * (dist) + (1 -_EMA_ALPHA) * dist_ema;

   if(dist_ema < DIST_MIN){
    myservo.writeMicroseconds(_DUTY_MIN);
  }
  else if(dist_ema > DIST_MAX){
    myservo.writeMicroseconds(_DUTY_MAX);
  }
  else{
    duty = (_DUTY_MAX - _DUTY_MIN)/1023.0 * a_value_ema + _DUTY_MIN;
    myservo.writeMicroseconds(duty);
  }


  Serial.print("MIN:" ); Serial.print(DIST_MIN);
  Serial.print(", IR:" ); Serial.print(a_value_ema);
  Serial.print(", dist:" ); Serial.print(dist);
  Serial.print(", ema:" ); Serial.print(dist_ema);
  Serial.print(", servo:" ); Serial.print(duty);
  Serial.print(", MAX:" ); Serial.print(DIST_MAX);
  Serial.println("");

}
