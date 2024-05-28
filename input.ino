#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

#define nss 7
#define rst 8
#define dio0 9

String incoming;

void setup() {
  Serial.begin(115200);

  Serial.println("LoRa Receiver");
  LoRa.setPins(nss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  //Serial.println("ping");
  if (packetSize) {
    byte destinationAddress = LoRa.read();
    byte senderAddress = LoRa.read();
    byte incomingMsgId = LoRa.read();
    byte incomingLength = LoRa.read();

    incoming = "";

    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    Serial.print("Received message from ");
    Serial.print(senderAddress, HEX);
    Serial.print(", message ID: ");
    Serial.print(incomingMsgId);
    Serial.print(", length: ");
    Serial.print(incomingLength);
    Serial.print(", message: ");
    Serial.println(incoming);

    // Add status prints for debugging
    Serial.print("Destination Address: ");
    Serial.println(destinationAddress, HEX);

    // Process the received message as needed
    
    tone(2, 50);
    delay(600);
    noTone(2);
    tone(2, 1);
    delay(600);
    noTone(2);
    tone(2, 50);
    delay(600);
    noTone(2);
    tone(2, 50);
    delay(600);
    noTone(2);
    tone(2, 100);
    delay(600);
    noTone(2);
    /*
    for(int i=0;i>5;i++){
      tone(2, 10*i+1);
      delay(60);  // Delay between receiving messages
      noTone(2);
    }
    */
  }
  delay(50);
}
