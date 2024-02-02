#include <IRLibAll.h>
#include <SoftwareSerial.h>
#include <GyverOLED.h>


GyverOLED<SSH1106_128x64> oled;
int ircode[10];  // Creates an array of 10 integers

//ir code sets arrays are defined
int defaultcodes[10] = { 16738455, 16724175, 16718055, 16743045, 16716015, 16726215, 16734885, 16728765, 16730805, 16732845 };  //0
int irsoftcode[10];                                                                                                             //1
int codeswitch = 0;                                                                                                             //0 is default 1 is custom

boolean programIR = false;

int repeat_code = 4294967295;

boolean device_bootup = true;
boolean motor_test= true;
int y = 5;


const int buttonPin = 11;
const int buttonPin2 = 12;

int x = 1;
String dupe = ".";
int power = 0;
String ir = "?";
IRrecvPCI myReceiver(2);  // create receiver and pass pin number
IRdecode myDecoder;       // create decoder
unsigned long last_cmd = 0;



void bootup() {
  if (device_bootup) {
    
    while (y < 200) {
      oled.circle(64, 32, y / 15);

      oled.update();
      oled.line(64, 32, 64, 40 + (y / 5));
      oled.line(64, 32, 64 - (y / 2.5), 32 - (y / 5));
      oled.line(64, 32, 64 + (y / 2.5), 32 - (y / 5));
      y = y + 5;
      delay(20);
    }

    oled.line(0, 0, 64, 64);
    oled.line(128, 0, 64, 64);
    oled.line(0, 0, 128, 0);
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
    oled.print(" IR");
    oled.update();
    delay(200);
    oled.clear();
    oled.home();
    oled.setScale(3.75);
    oled.print("DEVICE");
    oled.update();
    delay(200);
    oled.clear();

    oled.setScale(1.5);
    oled.home();
    oled.println("WAITING FOR IR");
    oled.println("SIGNAL...");
    oled.update();
  }
}



bool hasDuplicates() {
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (irsoftcode[i] == irsoftcode[j]) {
        return true;  // Found a duplicate
      }
    }
  }
  return false;  // No duplicates found
}

void performAction(int index, const char* message, unsigned long lastValue) {
  ir = String(index);
  Serial.println(message);
  MotorCommand(index);
  last_cmd = lastValue;
}


void printArray(int arr[], int size) {
  oled.clear();
  oled.home();
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    oled.println(arr[i]);
    if (i < size - 1) {
      Serial.print(", ");  // Print a comma and space after each element (except the last one)
    }
  }
  Serial.println();  // Print a newline character at the end
  oled.clear();
  oled.home();
}


void setup() {
  
  Serial.begin(9600);
  //predefined motor OUTPUTS
  #define motor1back 4  
  #define motor2back 3
  #define motor1forward 6
  #define motor2forward 5

  pinMode(motor1back, OUTPUT);
  pinMode(motor2back, OUTPUT);
  pinMode(motor1forward, OUTPUT);
  pinMode(motor2forward, OUTPUT);


  bootup();
  MotorTest();
  //IR DEFAULT CODES
  for (int i = 0; i < 10; ++i) {
    ircode[i] = defaultcodes[i];
  }

  

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  
  delay(2000);
  while (!Serial)
    ;                       // delay for Leonardo
  myReceiver.enableIRIn();  // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  oled.init();
  oled.update();
  Serial.println(F("Ready to receive display signals"));
}

void MotorTest(){

    if(motor_test){
    oled.clear();
    oled.setScale(4.5);
    oled.home();
    oled.println("MOTOR");
    oled.print(" TEST");
    oled.update();

    // put your main code here, to run repeatedly:

    //---------------------
    //--bootup motor test--
    //---------------------
    
    //quick switch test
    for (int i = 0; i < 5; i++) { 
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, HIGH);
    delay(200);
    digitalWrite(motor2back, HIGH);
    digitalWrite(motor2forward, LOW);
    delay(200);
    digitalWrite(motor1back, HIGH);
    digitalWrite(motor1forward, LOW);
    delay(200);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, HIGH);
    }
    delay(5000);


    //rollover bootup test
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, HIGH);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, LOW);
    delay(2000);
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, LOW);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, HIGH);
    delay(500);
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, HIGH);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, HIGH);
    delay(5000);
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, LOW);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, LOW);
    delay(3000);

    oled.clear();
   }
}

void MotorCommand(int IR){
  
  /*
  remote keypad ref:
  -----
  0-*-*
  1-2-3
  4-5-6
  7-8-9
  -----

  2 is forward
  4 is turn left
  6 is turn right
  8 is backwards
  */
  switch (IR){
    case 2:
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, HIGH);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, HIGH);
    break;

    case 4:
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, HIGH);
    digitalWrite(motor2back, HIGH);
    digitalWrite(motor2forward, LOW);
    break;

    case 6:
    digitalWrite(motor1back, HIGH);
    digitalWrite(motor1forward, LOW);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, HIGH);
    break;

    case 8:
    digitalWrite(motor1back, HIGH);
    digitalWrite(motor1forward, LOW);
    digitalWrite(motor2back, HIGH);
    digitalWrite(motor2forward, LOW);
    break;

    case 0:
    digitalWrite(motor1back, LOW);
    digitalWrite(motor1forward, LOW);
    digitalWrite(motor2back, LOW);
    digitalWrite(motor2forward, LOW);
    break;
  }
}


void loop() {
  // Continue looping until you get a complete signal received
  oled.clear();


  int buttonState = digitalRead(buttonPin);  // Read the button state

  if (buttonState == LOW) {  // Button is pressed (remember we're using INPUT_PULLUP, so LOW means pressed)
    Serial.println("BUTTON 1 PRESSED");
    programIR = true;
    while (programIR == true) {
      int receivedValueint = 0;
      oled.clear();
      oled.home();
      oled.update();
      oled.setScale(1.5);

      Serial.println("PROGRAM IR MODE");
      oled.println("PROGRAM IR MODE:");
      oled.update();
      delay(100);

      int valid = 0;
      if (myReceiver.getResults()) {
        myDecoder.decode();  // Decode it
        unsigned long receivedValue = myDecoder.value;
        receivedValueint = int(receivedValue);

        Serial.println(receivedValueint);


        if ((receivedValueint != repeat_code) && (receivedValueint != 0)) {
          oled.setScale(1.5);
          irsoftcode[valid] = receivedValueint;
          oled.println("received and stored:");
          oled.println(receivedValueint);
          oled.update();
          delay(100);
          valid = valid + 1;
          if (valid = 10) {
            oled.clear();
            oled.home();
            oled.println("10 values received and stored");
            delay(50);
            if (hasDuplicates() == false) {
              printArray(irsoftcode, 10);
              programIR = false;

            } else {
              Serial.println("||repeat values ERROR");
              programIR = false;
            }
          }
        }
      }


      /*
      for (int i = 0; i < 10; i) {
        oled.clear();
        oled.home();
        oled.setScale(3);
        oled.println("PRESS: ");
        oled.println(i);
        oled.update();
        if (myReceiver.getResults()) {
          myDecoder.decode();  // Decode it

          // Store the received value in a new variable
          unsigned long receivedValue = myDecoder.value;

          // Convert the received value to a string
          receivedValueint = int(receivedValue);
        }
        if ((receivedValueint != repeat_code) && (receivedValueint != 0)) {
          oled.setScale(1.5);
          irsoftcode[i] = receivedValueint;
          oled.println("received and stored:");
          oled.println(receivedValueint);
          oled.update();
          delay(100);
          Serial.println("C");
        }
        Serial.println("D");
        int buttonState2 = digitalRead(buttonPin2);

        if (buttonState2 == LOW) {
          i = i + 1;
          Serial.println("E");
          delay(100);
        }
      }
      programIR = true;

      */
    }
    if (programIR == false) {
      Serial.println("PROGRAM IR MODE CANCELED");
      oled.println("PROGRAM IR MODE:");
      oled.print("CANCELED!");
      programIR = false;
      oled.update();
      delay(230);
    }
    // Add your desired actions or functions to be executed when the button is pressed
    // Debounce delay to prevent rapid multiple readings
  }

  if (programIR == false) {
    dupe = ".";
    if (myReceiver.getResults()) {
      myDecoder.decode();  // Decode it

      // Store the received value in a new variable
      unsigned long receivedValue = myDecoder.value;

      // Convert the received value to a string
      int receivedValueint = int(receivedValue);

      if (receivedValueint != 0) {
        Serial.print(F("|||IR value: "));
        Serial.println(receivedValueint);

        x = x + 1;
      }
      if (receivedValueint == ircode[0]) {
        performAction(0, "Received #0", 16738455);
      } else if (receivedValueint == ircode[1]) {
        performAction(1, "Received #1", 16724175);
      } else if (receivedValueint == ircode[2]) {
        performAction(2, "Received #2", 16718055);
      } else if (receivedValueint == ircode[3]) {
        performAction(3, "Received #3", 16743045);
      } else if (receivedValueint == ircode[4]) {
        performAction(4, "Received #4", 16716015);
      } else if (receivedValueint == ircode[5]) {
        performAction(5, "Received #5", 16726215);
      } else if (receivedValueint == ircode[6]) {
        performAction(6, "Received #6", 16734885);
      } else if (receivedValueint == ircode[7]) {
        performAction(7, "Received #7", 16728765);
      } else if (receivedValueint == ircode[8]) {
        performAction(8, "Received #8", 16730805);
      } else if (receivedValueint == ircode[9]) {
        performAction(9, "Received #9", 16732845);
      } else if (receivedValueint != 0) {



        Serial.print("|||");
        Serial.print("repeat action: ");
        Serial.println(last_cmd);

        receivedValueint = last_cmd;
        dupe = "+";
      }


      //myDecoder.dumpResults(false);  // Now print results. Use false for less detail
      myReceiver.enableIRIn();

      oled.home();
      oled.setScale(3);
      oled.print("IR: ");
      oled.print("-");
      oled.print(ir);
      oled.print("-");
      oled.println("||");
      oled.print(x);
      oled.print("  ");
      oled.print(dupe);
      oled.update();
      delay(5);
      //Serial.println("||Display update");
      // Restart receiver
    }
  }
}
