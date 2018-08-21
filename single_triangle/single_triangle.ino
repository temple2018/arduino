#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <stdio.h>

#define BUTTON_PIN 8
#define PIN 6
#define NUM_NODES 20
#define NUM_OUTPUTS_PER_NODE 3
#define ALL_ON_LEVEL 255
#define THIRD_ON_LEVEL 192
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NODES, PIN, NEO_RGB + NEO_KHZ800);

#define PI 3.14

int num_pixels = NUM_NODES * NUM_OUTPUTS_PER_NODE;


int maxBright = 255;
int minBright = 0;
int delayVal = 20;
float bright;
float in;
float out;

int mode = 0;

int buttonState; 
int lastButtonState;
// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void pixel(int num, int bright) {
  int node = round(num / 3);
  int output = num%3;
  
  uint8_t bytes[3];
  
  uint32_t color = strip.getPixelColor(node);
  
  bytes[0] = (color >> 16) & 0xff;
  bytes[1] = (color >> 8) & 0xff;
  bytes[2] = (color) & 0xff;
  
  bytes[output] = brightness(bright);

  strip.setPixelColor(node, bytes[0], bytes[1], bytes[2]);
}

uint8_t getPixelValue(int num) {
  int node = round(num / 3);
  int output = num%3;
  
  uint8_t bytes[3];
  
  uint32_t color = strip.getPixelColor(node);
  
  bytes[0] = (color >> 16) & 0xff;
  bytes[1] = (color >> 8) & 0xff;
  bytes[2] = (color) & 0xff;
  
  return bytes[output];
}

int brightness(int value) {
  return 255-value;
}

// This is a button debouncing function that makes sure you dont 
//skip states or button pushes. Hardware is real and reality sucks.
bool checkButton()
{
  bool Pressed = false;
  // read the state of the switch into a local variable:
  int reading = digitalRead(BUTTON_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is low
      if (buttonState == LOW) {
        Pressed = true;
      }
    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  return Pressed;
}

void setup()
{
    // initialize the button pin as an input with a pull up, 
    // so if it is not connected it stays stable
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastButtonState = digitalRead(BUTTON_PIN);
  
  strip.begin();
  
  for(int i=0; i<num_pixels;i++){
    pixel(i, minBright);
  }
  
  strip.show();
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Welcome to Muffin Control node instalation test software");
}

void loop()
{
//  for (in = 0; in < 2*PI; in = in + 0.001) {
//    bright = abs(sin(in))*maxBright;
//    for(int i=0; i < num_pixels; ++i) {
//      pixel(i, bright);
//    }
//    strip.show();
//    delay(delayVal);
//  }

  switch (mode)
  {
    case 4://Start at the third node and increment by 3
      for(int i=2; i < num_pixels; i+=3) {
        pixel(i, THIRD_ON_LEVEL);
       }
       break;
    case 3://Start at the second node and increment by 3
      for(int i=1; i < num_pixels; i+=3) {
        pixel(i, THIRD_ON_LEVEL);
       }
       break;
    case 2://Start at the first node and increment by 3
      for(int i=0; i < num_pixels; i+=3) {
        pixel(i, THIRD_ON_LEVEL);
      }
      break;
    case 1://set everything on
      for(int i=0; i < num_pixels; ++i) {
        pixel(i, ALL_ON_LEVEL);
      }
      break;
    case 0:
    default://Run the sin function across a timebase 
      for(int i=0; i < num_pixels; ++i) {
        float val = (exp(sin(i*PI/3+millis()/2000.0*PI)) - 0.36787944)*108;
        pixel(i, val);
      }
    break;
  }
  
  strip.show();
  
  if (checkButton())
  {
    Serial.println("Btn Pressed");
    Serial.print(mode);
    Serial.print(" -> ");
    mode ++ ;
    mode %= 5;//fix this
    Serial.print(mode);
    Serial.print("\r\n");
    for(int i=0; i < num_pixels; ++i) {
        pixel(i, 0);
      }
  }
}

