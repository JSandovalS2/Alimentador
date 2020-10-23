#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup() {

  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  /* The rest of the code is not necessary to set the time,
   * we're just making sure it was set correctly: */
  Serial.begin(9600);
  
  DateTime now = rtc.now();
  printDate(now);
  
}

void loop() {

}

void printDate(DateTime date) {
  
   Serial.print(date.year(), DEC);
   Serial.print('/');
   Serial.print(date.month(), DEC);
   Serial.print('/');
   Serial.print(date.day(), DEC);
   Serial.print(" ");
   Serial.print(date.hour(), DEC);
   Serial.print(':');
   Serial.print(date.minute(), DEC);
   Serial.print(':');
   Serial.print(date.second(), DEC);
   Serial.println();
   
}
