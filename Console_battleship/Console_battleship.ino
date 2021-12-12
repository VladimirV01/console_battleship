#include <FastLED.h>
#include <String.h>

#define PIN 12
#define NUM_LEDS 100
#define MATRIX_HEIGHT 10
#define MATRIX_WIDTH 10

CRGB leds[NUM_LEDS];

short unsigned int go[][10] = {
  {0b0, 0b0, 0b1, 0b1, 0b0, 0b0, 0b0, 0b1, 0b0, 0b0},
  {0b0, 0b1, 0b0, 0b0, 0b1, 0b0, 0b1, 0b0, 0b1, 0b0},
  {0b1, 0b0, 0b0, 0b0, 0b0, 0b1, 0b0, 0b0, 0b0, 0b1},
  {0b1, 0b0, 0b0, 0b0, 0b0, 0b1, 0b0, 0b0, 0b0, 0b1},
  {0b1, 0b0, 0b0, 0b0, 0b0, 0b1, 0b0, 0b0, 0b0, 0b1},
  {0b1, 0b0, 0b1, 0b1, 0b1, 0b1, 0b0, 0b0, 0b0, 0b1},
  {0b1, 0b0, 0b0, 0b0, 0b1, 0b1, 0b0, 0b0, 0b0, 0b1},
  {0b1, 0b0, 0b0, 0b0, 0b1, 0b1, 0b0, 0b0, 0b0, 0b1},
  {0b0, 0b1, 0b0, 0b0, 0b1, 0b0, 0b1, 0b0, 0b1, 0b0},
  {0b0, 0b0, 0b1, 0b1, 0b0, 0b0, 0b0, 0b1, 0b0, 0b0}
};

void start_screen()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(i+120,i*2,i+50);
    FastLED.show();
    delay(5);
  }
  for(int i = NUM_LEDS; i >= 0; i--)
  {
    leds[i] = CRGB(int(i/100),i*2,i+100);
    FastLED.show();
    delay(5);
  }
  FastLED.show();
  delay(500);
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if (go[i][j])
        leds[i * 10 + j] =  CRGB(220,100,40);
      else
        leds[i * 10 + j] = CRGB(0,0,0);
      FastLED.show();
      delay(10);
    }    
  }
  FastLED.show();
  delay(500);
}

void setup() {
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS);

  Serial.begin(9600);
}

void loop() {

  String received;
  if (Serial.available() > 0) {
    received = Serial.readStringUntil('\n');

   //Serial.println(received.length());
   if(received.equals("check"))
   {
    Serial.println("Connection is OK.");
   }
   else if(received.equals("start"))
   {
    start_screen();
   }else
   {
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
}
