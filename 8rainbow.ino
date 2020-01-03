#include <Adafruit_NeoPixel.h>
#define LED_PIN    5
#define LED_COUNT 8
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int mock[8][3];
int current[8][3];

void setup() {
  strip.begin();           
  strip.show();            
  strip.setBrightness(50); 
}

void loop() {
  //rainbowCycle(100);    
  for(int i=0; i<8; i++) {
    blip(i);
    fadeBlip(20);
  }
}




void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void blip(int point) {

  int bright = 255;
  int ray = point;
  int iray = point;

  mock[point][0] = 255;
  mock[point][1] = 0;
  mock[point][2] = 0;
  
  for (int i=1; i <= 4; i++) { 

    iray =   (iray + (8 - 1)) % 8;
    ray =    (ray + 1) % 8;
    bright = bright / 3;

    mock[ray][0] = 255;
    mock[ray][1] = 0;
    mock[ray][2] = 0;
    mock[iray][0] = 255;
    mock[iray][1] = 0;
    mock[iray][2] = 0;
  }
}

void fadeBlip(uint8_t wait) {
  bool done = false;
  while(done == false) {
    for(int i=0; i< strip.numPixels(); i++) {
          
      int r = current[i][0];
      int g = current[i][1];
      int b = current[i][2];
    
      if (r < mock[i][0]) {
        r++;
        done = false;
      }
      if (g < mock[i][1]) {
        g++;
        done = false;
      }
      if (b < mock[i][2]) {
        b++;
        done = false;
      }
    
      if (r > mock[i][0]) {
        r--;
        done = false;
      }
      if (g > mock[i][1]) {
        g--;
        done = false;
      }
      if (b > mock[i][2]) {
        b--;
        done = false;
      }

      current[i][0] = r;
      current[i][1] = g;
      current[i][2] = b;
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
    delay(wait);

  }
}
