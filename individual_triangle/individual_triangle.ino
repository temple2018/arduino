#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <stdio.h>

#define PIN 6
#define NUM_NODES 3
#define NUM_OUTPUTS_PER_NODE 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NODES, PIN, NEO_RGB + NEO_KHZ800);

int num_pixels = NUM_NODES * NUM_OUTPUTS_PER_NODE;

int delayval = 30;
int maxbright = 128;
int minbright = 10;

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

void loop()
{
  delayval = (random(15, 60)+delayval)/delayval;
  for(uint8_t i=0; i<num_pixels+num_pixels/2; i++){
    pixel(i, maxbright);
    pixel(i-1, maxbright*2/3);
    pixel(i-2, maxbright*1/3);
    pixel(i-3, minbright);
    strip.show();
    delay(delayval);
  }
  delayval = (random(15, 60)+delayval)/delayval;
  for(int i=num_pixels; i>0-(num_pixels+num_pixels/2); i--){
    pixel(i, maxbright);
    pixel(i+1, maxbright*2/3);
    pixel(i+2, maxbright*1/3);
    pixel(i+3, minbright);
    strip.show();
    delay(delayval);
  }
}

