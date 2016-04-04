

int mostureSensor = 5;

#include "DHT.h"

#define DHTPIN 7     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

#define DELAY 30000   

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);


void setup() { 
  Serial.begin(9600);
	dht.begin();
}
// the loop routine runs over and over again forever: 

void loop() { 
        for (int i=0;i<mostureSensor;i++) {
   	  int sensorValue = analogRead(i);
	  String line="M";
          line=line +  + i + "|" + sensorValue;
	  Serial.println(line);
          delay(DELAY);
        }

	float h = dht.readHumidity();
	float t = dht.readTemperature();

	Serial.print("H|");
        Serial.println(h);
	Serial.print("T|");
        Serial.println(t);



	delay(1000); // delay 1 second between reads 
        delay(DELAY);
}
