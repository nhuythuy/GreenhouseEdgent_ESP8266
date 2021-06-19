#include <DHT.h>

// sensors
float humidity = 0.0;
float temp = 0.0;

int sensorErrorCounter = 0;
 
#define PIN_SS_DHT                  D5 // DHT sensor pin

DHT dht(PIN_SS_DHT, DHT11, 15);

void setupSensors(){
  dht.begin();
}

float hm = 0.0;
float tmp = 0.0;

bool updateHumidTemp(){
  hm = dht.readHumidity();
  tmp = dht.readTemperature();

  if (isnan(hm) || isnan(tmp)) {
    Serial.println("Failed to read from DHT sensor!");

//    humidity = -100;
//    temp = -100;
    sensorErrorCounter++;
    
    return false;
  }
  else{
    sensorErrorCounter = 0;
    humidity = hm;
    temp = tmp;
  }
  
  return true;
}
