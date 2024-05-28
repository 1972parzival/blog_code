#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

#define nss 7
#define rst 8
#define dio0 9

String outgoing;
byte msgCount = 0;
byte localAddress = 0xBB;
byte destination = 0xFF;
long lastSendTime = 0;
int interval = 50;
String basemessage = " HELLO WORLD: ";



void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Serial.println("LoRa Two Way Communication");
  LoRa.setPins(nss, rst, dio0);

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();
  LoRa.write(destination);
  LoRa.write(localAddress);
  LoRa.write(msgCount);
  LoRa.write(outgoing.length());
  LoRa.print(outgoing);
  LoRa.endPacket();
  
  // Increment and wrap msgCount
  msgCount++;
  if (msgCount > 255) {
    msgCount = 0;
  }
}


void loop()
{  
  int randomNumber = random(101);  // Generates a random number between 0 and 100
  int randomNumber2 = random(101);
  String randomString = String(randomNumber*randomNumber2);
  String message = basemessage + randomString;
  sendMessage(message);

  Serial.print("Sending message: ");
  Serial.println(message);

  
  delay(3000);
  Serial.println("_");

  tone(2, 10);
  delay(100);
  noTone(2);

  delay(50);
}
