#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

Servo myservo;

//Weitere Pins müssen vom RFID-Scanner beim Arduino gesteckt werden. (Siehe https://elektro.turanis.de/html/prj102/index.html)
  //    SCK	Pin 13
  //    MOSI Pin 11
  //    MISO	Pin 12
#define SS_PIN 10
#define RST_PIN 5

//MOTION SENSOR
const int pingPin = 6;
const int echoPin = 3; 
bool hasSent = false;


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 9  // On Trinket or Gemma, suggest changing this to 1
#define LEDPIN 8 // Second Pin for LEDs

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 50  // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 5  // Time (in milliseconds) to pause between pixels

int ledColor = 1;

MFRC522 rfid(SS_PIN, RST_PIN);

bool isOpen = false;

void setup() {
    Serial.begin(9600);
// These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
// Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels2.begin(); //überall anpassen bei den LED-Methoden, dass beide pixels dasselbe machen
  startLED();


  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  SPI.begin();      // init SPI bus
  rfid.PCD_Init();  // init MFRC522

  //Serial.println("Tap RFID/NFC Tag on reader");

  myservo.attach(2);  // attaches the servo on GIO2 to the servo object
  myservo.write(0);
  setColorOfLEDs(2);
}

void loop() {

  if (rfid.PICC_IsNewCardPresent()) {  // new tag is available
    if (rfid.PICC_ReadCardSerial()) {  // NUID has been read
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);


      rfid.PICC_HaltA();       // halt PICC
      rfid.PCD_StopCrypto1();  // stop encryption on PCD

      if (rfid.uid.size == 7) {
          for (int i = 0; i < rfid.uid.size; i++) {
            Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(rfid.uid.uidByte[i], HEX);
          }

        if (!isOpen) {
          delay(50);
          open();
        } else {
          close();
        }
        delay(500);
      }
    }
  }else{
    delay(250);
      long duration, cm;
      //send and receive ultrasound to detect distance
      digitalWrite(pingPin, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(pingPin, LOW);
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
      cm = microsecondsToCentimeters(duration);

    if(cm <=40){  //Anpassen, Zahl -> Abstand in cm zu dem Ultraschallsensor
      Serial.println("SOUND");
      delay(250);
    }
    delay(200);
  }

  if (Serial.available()) {
    setColorOfLEDs(Serial.readString().toInt());
  }
}


long microsecondsToCentimeters(long microseconds) {     // je nachdem wo unser Teil stellt, würde ich das auf mindestens 200cm setzen, bis hin zu 300cm und dann ein größeren Delay einbauen, für die Tonausgabe
  int real_distance = microseconds / 29 / 2;
  return real_distance;
}



void open() {
  isOpen = true;
  for (int pos = 0; pos <= 80; pos += 1) {  // goes from 0 degrees to 180 degrees
                                             // in steps of 1 degree
    myservo.write(pos);                      // tell servo to go to position in variable 'pos'
    delay(5);                                // waits 15ms for the servo to reach the position
  }
}


void close() {
  isOpen = false;
  for (int pos = 80; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(pos);                        // tell servo to go to position in variable 'pos'
    delay(5);                                  // waits 15ms for the servo to reach the position
  }
}


void startLED() {
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:

    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels2.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();  // Send the updated pixel colors to the hardware.
    pixels2.show();

    delay(DELAYVAL);
  }
}

void setColorOfLEDs(int color) {
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    if (color == 0) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels2.setPixelColor(i, pixels.Color(255, 0, 0));
    } else if (color == 1) {
      pixels.setPixelColor(i, pixels.Color(255, 165, 0));
      pixels2.setPixelColor(i, pixels.Color(255, 165, 0));
    } else if (color == 2) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels2.setPixelColor(i, pixels.Color(0, 255, 0));
    } else if (color == 3) {
      pixels.setPixelColor(i, pixels.Color(255, 192, 203));
      pixels2.setPixelColor(i, pixels.Color(255, 192, 203));
    }
  }
  pixels.show();  // Send the updated pixel colors to the hardware.
  pixels2.show();

  delay(DELAYVAL);  // Pause before next pass through loop
}
