#include <WiFiUdp.h>
#include <NTPClient.h>


#ifndef DATE_TIME
#define DATE_TIME

int currentHour = -1;
int currentDay = -1;
int currentMin = -1;
float systemHourMinute = 0.0;


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov");
char* DayOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setupDateTime(){
  timeClient.begin(); // Initialize a NTPClient to get time
// Set offset time in seconds to adjust for your timezone, ex.: GMT +1 = 3600, GMT +8 = 28800, GMT -1 = -3600, GMT 0 = 0
  timeClient.setTimeOffset(3600); // Norway GMT + 1
}


void getServerTime(){
  Serial.println();
  timeClient.update();
  currentDay = timeClient.getDay();
  currentHour = timeClient.getHours();
  currentMin = timeClient.getMinutes();

  systemHourMinute = (float)currentHour + currentMin / 100.0;
  Serial.println("Today:  " + String(DayOfWeek[currentDay]) + " (" + String(currentDay) + ") - " + timeClient.getFormattedTime());  
}

#endif
