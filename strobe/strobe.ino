#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <stdio.h>

#define PIN 6
#define NUM_NODES 2
#define NUM_OUTPUTS_PER_NODE 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NODES, PIN, NEO_RGB + NEO_KHZ800);

int num_pixels = NUM_NODES * NUM_OUTPUTS_PER_NODE;

int maxBright = 255;
int minbright = 0;
;

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
  Serial.begin(9600);
  strip.begin();
  pixel(0,0);
  pixel(1,0);
  pixel(2,minbright);
  strip.show();
}

int delayval = 2000;
void loop()
{
  pixel(0, maxBright);
  pixel(1,maxBright);
  pixel(2,maxBright);
  strip.show();
  delay(1000);
  pixel(0, 0);
  pixel(1,0);
  pixel(2,0);
  strip.show();
  delay(2000);
}

