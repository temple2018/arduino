#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <stdio.h>

#define PIN 6
#define NUM_NODES 2
#define NUM_OUTPUTS_PER_NODE 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NODES, PIN, NEO_RGB + NEO_KHZ800);

int num_pixels = NUM_NODES * NUM_OUTPUTS_PER_NODE;

int maxbright = 255;
int minbright = 180;

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
  return 255 - value;
}

void setup()
{
  Serial.begin(9600);
  strip.begin();
  
  for(int i=0; i<num_pixels;i++){
    pixel(i, minbright);
  }
  strip.show();
}

int maxdelay = 2000;
int mindelay = 1600;
int delayval = random(mindelay, maxdelay);
int bright = random(minbright, maxbright);

void loop()
{
  delayval = (random(15, 60)+delayval)/2;
  bright = (random(minbright, maxbright) + bright)/2;

  for(int i=random(0, num_pixels); i<num_pixels; i++){
    int random_pixel = random(0,num_pixels);
    int pixelVal = getPixelValue(random_pixel);
    int pixelBright = (bright + pixelVal)/pixelVal;
    pixel(random_pixel, bright);
  }
  strip.show();
  delay(delayval);
}

