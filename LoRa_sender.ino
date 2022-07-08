#include <SPI.h>
#include <LoRa.h>

#include <OneWire.h>
#include <DallasTemperature.h>


// Chân nối với Arduino
#define ONE_WIRE_BUS 9
//Thiết đặt thư viện onewire
OneWire oneWire(ONE_WIRE_BUS);
//Mình dùng thư viện DallasTemperature để đọc cho nhanh
DallasTemperature sensors(&oneWire);

//#include "DHT.h"            
//const int DHTPIN = 9;      
//const int DHTTYPE = DHT11;  
//DHT dht(DHTPIN, DHTTYPE);

#define NSS 10
#define RST 3
#define DIO0 2
int counter = 0;

//#define NSS 10
//#define RST 9
//#define DIO0 8

void setup() {
//  dht.begin();     
  LoRa.setPins(NSS,RST,DIO0);
  Serial.begin(9600);  
  Serial.println("LoRa Sender");

//  if (!LoRa.begin(433E6)) {
//    Serial.println("Starting LoRa failed!");
//    while (1);
//  }
  
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
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  LoRa.beginPacket();
  LoRa.print("current temp: ");
  LoRa.print(temp);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
