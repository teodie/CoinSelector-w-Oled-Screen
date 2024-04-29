#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte interruptPin = 2;

// Count the pulse recieved
volatile int pulseCount = 0;
volatile int interval = 0;
// Variable for total amount and time
int totalAmount = 0;
const byte intervalSpan = 10;


void initDisplay(){
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}


void displayCount(){
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  String Amount = "Amount: " + String(totalAmount);
  display.println(Amount);

  display.setCursor(0,18);             // Start at top-left corner
  String Interval = "Inter:" + String(interval);
  display.println(Interval);

  display.setCursor(0, 40);
  String Time = "pulse: " + String(pulseCount) ;
  display.println(Time);

  display.display();
}

void incrementPulse() {
  pulseCount+=1;
  interval = 0;
}

void setup() {
  initDisplay();

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), incrementPulse, FALLING);
}

void loop() {
  interval++;

  if(interval >= intervalSpan && pulseCount != 0){

    if(pulseCount == 4){
      totalAmount += 1;
    }

    if(pulseCount == 5){
      totalAmount += 5;
    }

    if(pulseCount == 6){
      totalAmount += 10;
    }

    pulseCount = 0;
  }


  displayCount();
}

