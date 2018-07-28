#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 25;
int maxbright = 200;
int minbright = 255;
void setup()
{
  strip.begin();
  strip.show(); //initialize all pixels to off
}

void loop()
{

  for(int i=maxbright;i<minbright;i++){
    strip.setPixelColor(0,i,i,i);
    strip.setPixelColor(1,i,i,i);
    strip.show();
    delay(delayval);
  }

  for(int i=minbright;i>maxbright;i--){
    strip.setPixelColor(0,i,i,i);
    strip.setPixelColor(1,i,i,i);
    strip.show();
    delay(delayval);
  }

}

