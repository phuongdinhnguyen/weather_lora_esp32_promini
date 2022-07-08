#include <SPI.h>
#include <LoRa.h>

//OLED I2C screen
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

// reset pin not used on 4-pin OLED module
Adafruit_SSD1306 display(-1);  // -1 = no reset pin

// 128 x 64 pixel display
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//this is for esp32
#define NSS 15
#define RST 3
#define DIO0 2

int t_update = 0;
void setup() {
  /*----Start OLED display-------*/
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,30);
  display.print("Hello, people!");

  display.display();

  /*----------------------------*/
  
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("LoRa Receiver");
  LoRa.setPins(NSS, RST, DIO0);
  
  while (!LoRa.begin(433E6)) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // try to parse packet

  String text = "";

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      //Serial.print((char)LoRa.read());
      text += (char)LoRa.read();
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    display.setCursor(10,5);
    display.print("temp sensor");
    
    display.setCursor(10,20);
    display.print(text);
    
    display.setCursor(10,35);
    if (t_update == 60) t_update = 0;
    display.print("times updated: ");
    display.print(t_update++);

    display.setCursor(10,50);
    display.print("RSSI: "); display.print(LoRa.packetRssi());
    
    display.display();
  
    Serial.print(text);
    
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
