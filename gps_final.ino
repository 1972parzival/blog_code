#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <GyverOLED.h>






SoftwareSerial gpsSerial(3, 4);  // RX, TX
TinyGPSPlus gps;

GyverOLED<SSH1106_128x64> oled;
int x = 1;
int y = 5;

const uint8_t bitmap_32x32[] PROGMEM = {
  // Your bitmap data here
};

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  oled.init();
  oled.clear();
  oled.update();
  
  
}

void loop() {
  // GPS Code
  if(x==1){
  for(int i = 0; i < 15; i++){
    int randomNumber2 = random(128);
    int randomNumber1 = random(64);
    oled.dot(randomNumber2,randomNumber1);
    oled.update();
    delay(50);
  }
  oled.clear();

  }
  while (gpsSerial.available() > 0) {
    
    gps.encode(gpsSerial.read());
    
    if (gps.location.isUpdated()) {
      // Clear previous data on 
      if(x==1){
        oled.clear();

        oled.home();
        oled.setScale(3);
        oled.println("SIGNAL");
        oled.print("FOUND..");
        oled.update();
        delay(500);
        oled.clear();




        while(y<200){          
          oled.circle(64, 32, y/15);

          oled.update();
          oled.line(64, 32, 64,40+(y/5));
          oled.line(64, 32, 64-(y/2.5),32-(y/5));  
          oled.line(64, 32, 64+(y/2.5),32-(y/5));  
          y = y +5;



        }
        
        oled.line(0, 0, 64,64); 
        oled.line(128, 0, 64,64); 
        oled.line(0, 0, 128,0); 
        oled.update();
        delay(500);
        

  
        oled.clear();
        oled.setScale(4.5);
        oled.home();
        oled.println("BLACK");
        oled.print(" OUT");
        oled.update();
        delay(300);
        oled.clear();
        oled.home();
        oled.print(" GPS");
        oled.update();
        delay(200);
        oled.clear();
        oled.home();
        oled.setScale(3.75);
        oled.print("DEVICE");
        oled.update();
        delay(200);
        oled.clear();
        x=0;
      }
      
      // Print Latitude and Longitude on OLED
      oled.home();
      oled.setScale(1);
      oled.println("Latitude:|Longitude: ");
      oled.print(gps.location.lat(), 6);
      
      oled.print("|");
      oled.println(gps.location.lng(), 6);
      oled.println("---------------------");
      oled.println(" ");
      oled.setScale(4.5);
      oled.print(" GPS");
      // Update the OLED display
      oled.update();
      
      // Print Latitude and Longitude on Serial Monitor
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
    }
    
  }

  // Add your other code here if needed
}