#include <FastLED.h>
#include <String.h>

#define PIN 12
#define NUM_LEDS 100
#define MATRIX_HEIGHT 10
#define MATRIX_WIDTH 10

CRGB leds[NUM_LEDS];

short int field[][10] = {
  {2, 0, -1, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 1, 0, 1, 0, -1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
};

void setup() {
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {

  String received;
  if (Serial.available() > 0) {
    received = Serial.readStringUntil('\n');

   Serial.println(received.length());
   if(received.equals("ON"))
   {
    Serial.println("SHIT IS ON");
   }

  for(int i = 0; i < received.length(); i++)
  {
    if(received[i] == '0')
    {
      leds[i] = CRGB(0,0,0);
    }
    else if(received[i] == '2')
    {
      leds[i] = CRGB(0,200,0);
    }
    else if(received[i] == '9')
    {
      leds[i] = CRGB(40,0,160);
    }
  }
  FastLED.show();
  }
  
}
