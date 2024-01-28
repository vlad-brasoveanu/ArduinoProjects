#include <hcsr04.h>

#define TRIG_PIN 11
#define ECHO_PIN 12
#define GREEN_LED 4
#define YELLOW_LED 3
#define RED_LED 2
#define BUZZ 7

HCSR04 sensor(TRIG_PIN, ECHO_PIN, 20, 4000);

void setup(){
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZ, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  int dist = sensor.distanceInMillimeters();
  if(dist <= 100)
  {
    dist = sensor.distanceInMillimeters();
    digitalWrite(BUZZ, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(1000);
  }
  else if(dist > 100 && dist <= 200)
  {
    dist = sensor.distanceInMillimeters();
    digitalWrite(BUZZ, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(250);
    digitalWrite(BUZZ, LOW);
    digitalWrite(RED_LED, LOW);
    delay(250);
  }
  else if(dist > 200 && dist <= 300)
  {
    dist = sensor.distanceInMillimeters();
    digitalWrite(BUZZ, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    delay(500);
    digitalWrite(BUZZ, LOW);
    digitalWrite(YELLOW_LED, LOW);
    delay(500);
  }
   else if(dist > 300 && dist <= 400)
  {
    dist = sensor.distanceInMillimeters();
    digitalWrite(BUZZ, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(750);
    digitalWrite(BUZZ, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(750);
  }
    digitalWrite(BUZZ, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
}


