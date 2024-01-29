#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

Servo myservo;

/*
    Additional pins must be plugged into the Arduino by the RFID scanner. (See https://elektro.turanis.de/html/prj102/index.html)
      SCK	Pin 13
      MOSI Pin 11
      MISO	Pin 12
*/
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

/* Neopixel Setup
   When setting up the NeoPixel library, we tell it how many pixels,
   and which pin to use to send signals. Note that for older NeoPixel
   strips you might need to change the third parameter -- see the
   strandtest example for more information on possible values.
*/   

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

//Time (in milliseconds) to pause between pixels
#define DELAYVAL 5

int ledColor = 1;

//rfid obejct
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
  
  // INITIALIZE NeoPixel strip objects
  pixels.begin();  
  pixels2.begin(); 
  startLED();


  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  SPI.begin();      // init SPI bus
  rfid.PCD_Init();  // init MFRC522


  myservo.attach(2);  // attaches the servo on GIO2 to the servo object
  myservo.write(0);  //
  setColorOfLEDs(2);
}

/* LOOP
Checks if there is a Card to scan with the rfid.
  If so, either:  call open()
                  call close()
Else checks if someone is walking in front of the 'TechTresor'.
  If so: send signal to Raspberry
Checks if there is a signal from the raspberry.
  If so: Change color of the leds.
*/
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

    if(cm <=40){
      Serial.println("SOUND");
      delay(250);
    }
    delay(200);
  }

  if (Serial.available()) {
    setColorOfLEDs(Serial.readString().toInt());
  }
}


//Used to calculate the correct distance for the ultra souud meter
long microsecondsToCentimeters(long microseconds) {
  int real_distance = microseconds / 29 / 2;
  return real_distance;
}


//Opens the door by using the servo, which is connected to the lock
void open() {
  isOpen = true;
  for (int pos = 0; pos <= 80; pos += 1) {                         
      myservo.write(pos);                      
      delay(5);                                
  }
}

//Closes the door by using the servo, which is connected to the lock
void close() {
  isOpen = false;
  for (int pos = 80; pos >= 0; pos -= 1) {  
      myservo.write(pos);                        
      delay(5);                                  
  }
}


void startLED() {
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels2.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();  // Send the updated pixel colors to the hardware.
    pixels2.show();  // Send the updated pixel colors to the hardware.

    delay(DELAYVAL);
  }
}

//Sets color of leds corresponding to the percentage of still available items in the 'TechTresor'
void setColorOfLEDs(int color) {
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
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
  pixels2.show(); // Send the updated pixel colors to the hardware.

  delay(DELAYVAL);  // Pause before next pass through loop
}
