#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <stdio.h>

#define PIN 6
#define NUM_NODES 3
#define NUM_OUTPUTS_PER_NODE 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NODES, PIN, NEO_RGB + NEO_KHZ800);

int num_pixels = NUM_NODES * NUM_OUTPUTS_PER_NODE;

int maxbright = 255;
int minbright = 180;

uint32_t replaceByte(int x, int n, int c) {
    int shift = (c << (8 * n));
    int mask = 0xff << shift;
    return (~mask & x) | shift;
}

void pixel(int num, int bright) {
  int node = round(num / 3);
  int output = num%3;
  
  uint8_t bytes[3];
  
  uint32_t color = strip.getPixelColor(node);
  
  bytes[0] = (color >> 16) & 0xff;
  bytes[1] = (color >> 8) & 0xff;
  bytes[2] = (color) & 0xff;

  uint32_t newColor = replaceByte(color, output, brightness(bright));

  uint8_t newBytes[3];

  newBytes[0] = (newColor >> 16) & 0xff;
  newBytes[1] = (newColor >> 8) & 0xff;
  newBytes[2] = (newColor) & 0xff;

  Serial.print("Old: ");
  Serial.print(bytes[0]); Serial.print("\t");
  Serial.print(bytes[1]); Serial.print("\t");
  Serial.println(bytes[2]);

  Serial.print("New: ");
  Serial.print(newBytes[0]); Serial.print("\t");
  Serial.print(newBytes[1]); Serial.print("\t");
  Serial.println(newBytes[2]);;
  

  strip.setPixelColor(node, replaceByte(color, output, brightness(bright)));
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

void loop()
{

  for(int i=0; i<num_pixels; i++){
    pixel(i, 128);
    strip.show();
    delay(500);
    pixel(i, 0);
    strip.show();
    delay(500);
  }
}

