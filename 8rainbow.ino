#include <Adafruit_NeoPixel.h>
#define LED_PIN    5
#define LED_COUNT 8
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint8_t peak = 0;
uint16_t hue = 0;
uint8_t anger = 0;

void setup() {
  strip.begin();           
  strip.show();            
  strip.setBrightness(50); 
}

void loop() {
  rainbowCycle(20);    
/*
  uint8_t anger = 128;

  hue = (uint16_t) (85 * (255 - anger));
  blip(peak, hue);
  peak++;

  delay( (255 - anger) >> 2 );
*/
}


void blip(uint8_t pos, uint16_t hue) {
  int val;
  
  for(int ptr = 0; ptr < 8; ptr++) {
    val = 255*(pow((0.98), (abs( ((pos + (ptr * 32)) + 128) % 256 - 128))));
    strip.setPixelColor(ptr, strip.ColorHSV(hue, 255, val));
  }  
  strip.show();
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
