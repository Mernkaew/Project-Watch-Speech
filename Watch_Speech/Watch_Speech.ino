#include <I2C_RTC.h>
#include <Wire.h> 
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
SoftwareSerial DFPlayerSerial(0, 2); // D3 RX, D4 TX
DFRobotDFPlayerMini DFPlayer;

static DS1307 RTC;

void setup() {
  Serial.begin(9600);
  DFPlayerSerial.begin(9600);

  pinMode(14, INPUT_PULLUP);

  RTC.begin();
  RTC.setHourMode(CLOCK_H24);

  /*RTC.setWeek(3);
  RTC.setDate(12,03,24);
  RTC.setTime(15,20,00);*/

  if (!DFPlayer.begin(DFPlayerSerial)) {
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
  } else {
    Serial.println("DFPlayer Mini online.");
  }
  DFPlayer.volume(30);
}

void loop() {
  RTC_Clock();
  Check_Time();
}

void Check_Time() {
  if (!digitalRead(14)){
    int check_hours = RTC.getHours();
    int check_minutes = RTC.getMinutes();
    test(check_hours, check_minutes);
  }
}

void test (int hours, int minutes) {
  DFPlayer.play(61);
  delay(3000);
  if (hours == 0) {
    DFPlayer.play(60);
    delay(1000);
  } else {
    DFPlayer.play(hours);
    delay(1000);
  }
  DFPlayer.play(63);
  delay(2000);
  if (minutes == 0) {
    DFPlayer.play(60);
    delay(1000);
  } else {
    DFPlayer.play(minutes);
    delay(1000);
  }
  DFPlayer.play(62);
  delay(1000);
}

void RTC_Clock() {
  switch (RTC.getWeek())
  {
    case 1:
      Serial.print("SUN");
      break;
    case 2:
      Serial.print("MON");
      break;
    case 3:
      Serial.print("TUE");
      break;
    case 4:
      Serial.print("WED");
      break;
    case 5:
      Serial.print("THU");
      break;
    case 6:
      Serial.print("FRI");
      break;
    case 7:
      Serial.print("SAT");
      break;
  }

  Serial.print(" ");
  Serial.print(RTC.getDay());
  Serial.print("-");
  Serial.print(RTC.getMonth());
  Serial.print("-");
  Serial.print(RTC.getYear());

  Serial.print(" ");

  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  Serial.println(" ");
}