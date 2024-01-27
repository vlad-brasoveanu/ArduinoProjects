
#include <LiquidCrystal.h>
#include "RTClib.h"


LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
RTC_DS1307 RTC;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Current hour:");
  if (! RTC.isrunning())
    RTC.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(RTC.now().hour(), DEC);
  lcd.print(':');
  if (RTC.now().minute()<10)
    lcd.print('0');
  lcd.print(RTC.now().minute(), DEC);
  lcd.print(':');
  if (RTC.now().second()<10)
    lcd.print('0');
  lcd.print(RTC.now().second(), DEC);
  delay(1000);
}

