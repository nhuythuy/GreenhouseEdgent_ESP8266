
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLwAoPpSkL"
#define BLYNK_DEVICE_NAME "Greenhouse"


#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD

#include "BlynkEdgent.h"
#include "sensors.h"
#include "datetime.h"

long runtimeMinutes = 0;
float battVolt = 24.48;

#define VP_LR_RUNTIME                       V0
#define VP_SYSTEM_TIME                      V1
#define VP_BATT_VOLT                        V2

#define VP_LR_TEMPERATURE                   V3
#define VP_LR_HUMIDITY                      V4
#define VP_ERROR_COUNTER                    V5


#define MESSAGE_DELAY 50
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void blynkTimerEvent()
{  
  runtimeMinutes++;
  getServerTime();
  updateHumidTemp();
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  yield();
  Serial.println("Blynk timer triggered...");
  // for all signals to be sent at once
  Serial.println("Counter: " + String(runtimeMinutes));
  Serial.println("Clock: " + String(systemHourMinute));
  Serial.println("Batt. Volt.: " + String(battVolt));
  Serial.println("Temperature: " + String(temp));
  Serial.println("Humidity: " + String(humidity));
  Serial.println("Error Counter: " + String(sensorErrorCounter));


  Blynk.virtualWrite(VP_LR_RUNTIME, runtimeMinutes);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_SYSTEM_TIME, systemHourMinute);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_BATT_VOLT, battVolt);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_LR_TEMPERATURE, temp);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_LR_HUMIDITY, humidity);
  delay(MESSAGE_DELAY);

  Blynk.virtualWrite(VP_ERROR_COUNTER, sensorErrorCounter);
  delay(MESSAGE_DELAY);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  setupSensors();
  delay(100);


  BlynkEdgent.begin();

  timer.setInterval(2000L, blynkTimerEvent);

  setupDateTime();
}

void loop() {
  BlynkEdgent.run();

}
