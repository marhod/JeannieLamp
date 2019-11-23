#include <Adafruit_NeoPixel.h>
#define neopixelsPin    10
#define neopixelsCount 24
Adafruit_NeoPixel strip(neopixelsCount, neopixelsPin, NEO_GRB + NEO_KHZ800);

// Variables and junk
uint32_t blue = 0;
uint32_t red = 0;  
uint32_t green = 255;

// Pins and Config
int smokePin = 5;   // This is what the input pin of the relay connects to
int fanPin =4;
int lowerButton = 8;  
int upperButton = 7; 
int lowerButtonState = 0;  
int upperButtonState = 0;
int ledPin =  LED_BUILTIN;   // This is the internal led, don't change it.    
int smokeTime = 5000;

void setup() {
  Serial.begin(9600);
  digitalWrite(smokePin, HIGH);
  digitalWrite(fanPin, HIGH);
  pinMode(lowerButton, INPUT);
  pinMode(upperButton, INPUT);
  pinMode(smokePin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  strip.begin();           
  strip.show();            
  strip.setBrightness(255);
  startUp();
  Serial.println("Connected");
}

void loop() {
  // Check for a button press
  lowerButtonState = digitalRead(lowerButton);
  upperButtonState = digitalRead(upperButton);
  
  // Upper Button held down
  if (upperButtonState == HIGH) {
    
    Serial.println("UB Press");
    goPink();
    fanOn();
    smokeOn();
    digitalWrite(ledPin, HIGH);
  } else {
    smokeOff();
    fanOff();
    goDark();
    digitalWrite(ledPin, LOW);
  }

  // Lower button press
  if (lowerButtonState == HIGH) {
    // Run the button action function
    Serial.println("Lower Button!");
    fanOff();
    smokeOff();
    digitalWrite(ledPin, HIGH);
    countDown(30);
    buttonAction();
    digitalWrite(ledPin, LOW);
  } 
}

void buttonAction () {
  // This turns the fan on, and then cycles the vape and the rainbow lights 3 times
  fanOn();
  smokeOn();
  rainbow(6);
  smokeOff();
  digitalWrite(ledPin, HIGH);
  rainbow(6);
  smokeOn();
  rainbow(6);
  smokeOff();
  digitalWrite(ledPin, HIGH);
  rainbow(6);
  smokeOn();
  rainbow(6);
  smokeOff();
  digitalWrite(ledPin, HIGH);
  rainbow(6);
  fanOff();
  strip.clear();
  strip.show();
}

void fanOn() {
  Serial.println("Fan on");
  digitalWrite(fanPin,LOW);
}

void fanOff() {
  Serial.println("Fan off");
  digitalWrite(fanPin,HIGH);
}

void smokeOn() {
  Serial.println("Smoke on");
  digitalWrite(smokePin, LOW);
  digitalWrite(ledPin, HIGH);
}

void smokeOff() {
  Serial.println("Smoke off");
  digitalWrite(smokePin, HIGH);
  digitalWrite(ledPin, LOW);
}

void goPink() {
  Serial.println("Go Pink");
  blue = 180;
  red = 255;  
  green = 105;
  for(int i=0; i<strip.numPixels(); i++) {
  strip.setPixelColor(i,red,green,blue);
  }
  strip.show();
}

void goGreen() {
  Serial.println("Go Green");
  blue = 0;
  red = 0;  
  green = 255;
  for(int i=0; i<strip.numPixels(); i++) {
  strip.setPixelColor(i,red,green,blue);
  }
  strip.show();
}


void goDark() {
  // Lights Out
  Serial.println("Go Dark");
  for(int i=0; i<strip.numPixels(); i++) {
  strip.setPixelColor(i,0,0,0);
  }
  strip.show(); 
}

void startUp() {
  // Flash green 3 times to show we're good to go.
  Serial.println("Start up");
  goGreen();
  delay(300);
  goDark();
  delay(100);
  goGreen();
  delay(300);
  goDark();
  delay(100);
  goGreen();
  delay(900);
  goDark();
}

void countDown(int seconds) {
  // Count down and show neopixels
  Serial.println("Counting down");
  blue = 252;
  red = 3;  
  green = 182;
  float waitTime = (seconds / strip.numPixels()) * 1000;
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,red,green,blue);
    strip.show();        
    delay(waitTime);
  }
}

// Rainbow-enhanced theater marquee. Borrowed code from Adafruit
void rainbow(int wait) {
    Serial.println("Rainbow");
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); 
    delay(wait);  
  }
}
