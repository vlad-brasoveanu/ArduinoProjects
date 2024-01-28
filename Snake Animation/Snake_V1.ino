
#include <LedControl.h>

int DIN = 12;
int CS = 11;
int CLK = 10;

LedControl lc=LedControl(DIN, CLK, CS, 1);

void setup()   {

  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
}

void loop() {
  lc.clearDisplay(0);
  lc.setLed(0, 0, 4, 1);
  delay(50);
  lc.setLed(0, 1, 3, 1);
  delay(50);
  lc.setLed(0, 2, 4, 1);
  delay(50);
  lc.setLed(0, 3, 3, 1);
  lc.setLed(0, 0, 4, 0);
  delay(50);
  lc.setLed(0, 4, 4, 1);
  lc.setLed(0, 1, 3, 0);
  delay(50);
  lc.setLed(0, 5, 3, 1);
  lc.setLed(0, 2, 4, 0);
  delay(50);
  lc.setLed(0, 6, 4, 1);
  lc.setLed(0, 3, 3, 0);
  delay(50);
  lc.setLed(0, 7, 3, 1);
  lc.setLed(0, 4, 4, 0);
  delay(50);
  lc.setLed(0, 0, 4, 1);
  lc.setLed(0, 5, 3, 0);
  delay(50);
  lc.setLed(0, 1, 3, 1);
  lc.setLed(0, 6, 4, 0);
  delay(50);
  lc.setLed(0, 2, 4, 1);
  lc.setLed(0, 7, 3, 0);
}

