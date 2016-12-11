/*
Board            int.0   int.1   int.2   int.3   int.4   int.5
Uno, Ethernet    2   3
Mega2560   2   3   21    20    19    18
Leonardo   3   2   0   1
Due            (any pin, more info http://arduino.cc/en/Reference/AttachInterrupt)

This example, as difference to the other, make use of the new method acquireAndWait()
*/


#include <idDHT11.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 7 on the Arduino
#define ONE_WIRE_BUS 7

// Setup a oneWire instance to communicate with ANY OneWire devices 
OneWire oneWire(ONE_WIRE_BUS);

// Set oneWire reference to Dallas Temperature sensor. 
DallasTemperature sensors(&oneWire);

//Digital pin for comunications
int idDHT11pin = 2;

//interrupt number (must be the one that use the previus defined pin (see table above)
int idDHT11intNumber = 0;

//declaration
void dht11_wrapper(); // must be declared before the lib initialization

					  // Lib instantiate
idDHT11 DHT11(idDHT11pin, idDHT11intNumber, dht11_wrapper);

void setup()
{
	Serial.begin(9600);
	sensors.begin();
}
void dht11_wrapper() {
	DHT11.isrCallback();
}
void loop()
{
	DHT11.acquireAndWait();
	sensors.requestTemperatures();

	Serial.print("Humidity (%)            : ");
	Serial.println(DHT11.getHumidity(), 3);

	Serial.print("Temperature (oC)        : ");
	Serial.println(DHT11.getCelsius(), 3);

	Serial.print("Dew Point (oC)          : ");
	Serial.println(DHT11.getDewPoint());


	Serial.print("DS18B20                 : ");
	Serial.println(sensors.getTempCByIndex(0), 3);

	Serial.println();

	delay(3000);
}