// Library for LoRa communication
#include <SPI.h>
#include <LoRa.h>

// Library for temp sensor
#include <OneWire.h>
#include <DallasTemperature.h>

// Define pin for temp sensor
#define ONE_WIRE_BUS 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Define pins for LoRa
#define NSS 10
#define RST 3
#define DIO0 2
int counter = 0;

void setup() { 
  LoRa.setPins(NSS,RST,DIO0);
  Serial.begin(9600);  
  Serial.println("LoRa Sender");

  while (!LoRa.begin(433E6)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  sensors.requestTemperatures(); // get temperature
  float temp = sensors.getTempCByIndex(0);
  LoRa.beginPacket();
  LoRa.print("current temp: ");
  LoRa.print(temp);
  LoRa.endPacket();

  counter++;
  delay(5000);
}
