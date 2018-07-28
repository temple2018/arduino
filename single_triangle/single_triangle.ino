#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <stdio.h>

#define PIN 6
#define NUM_NODES 1
#define NUM_OUTPUTS_PER_NODE 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NODES, PIN, NEO_RGB + NEO_KHZ800);

#define PI 3.14

int num_pixels = NUM_NODES * NUM_OUTPUTS_PER_NODE;


int maxBright = 255;
int minBright = 0;
int delayVal = 20;
float bright;
float in;
float out;

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

void setup()
{
  strip.begin();
  
  for(int i=0; i<num_pixels;i++){
    pixel(i, minBright);
  }
  
  strip.show();
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
  for(int i=0; i < 3; ++i) {
    float val = (exp(sin(i*PI/3+millis()/2000.0*PI)) - 0.36787944)*108;
    pixel(i, val);
  }

  strip.show();
}

