#ifndef APA102MANAGER_H
#define APA102MANAGER_H

#include<FastLED.h>
#define DATAPIN 4
#define CLOCKPIN 5
#define NUMPIXELS 288


class APA102Manager
{
  public:
    APA102Manager()
    {
      FastLED.addLeds<APA102,DATAPIN,CLOCKPIN,BGR>(leds,NUMPIXELS,0);
      FastLED.setBrightness(1);
      numpixels = NUMPIXELS;
      for(int i=0;i<numpixels;i+=1)
      {
        leds[i] = CRGB::White;  
      }
      show();
    };
    ~APA102Manager(){};
    void show(){FastLED.show();}
    CRGB getColor(uint16_t pos){return leds[pos];}
    void setColor(uint16_t pos,CRGB color)
    {
      leds[pos] = color;  
    };
    void resetColor()
    {
      for(int i=0;i<numpixels;i+=1)
      {
        leds[i] = CRGB::Black;
        //leds[i] = CRGB::White;  
      }  
    }

  private:
    struct CRGB leds[432];
    uint16_t numpixels;
};

#endif
