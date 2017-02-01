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
      delay(5000);
    };
    ~APA102Manager(){};
    void show(){FastLED.show();}
    CRGB getColor(uint16_t pos){return leds[pos];}
    void setColor(uint16_t pos,CRGB color)
    {
      leds[pos] = color;  
    };
    void setEnemy(uint16_t pos){setColor(pos,enemyColor);}
    void setPlayer(uint16_t pos){setColor(pos,playerColor);}
    
    
    void resetColor()
    {
      for(int i=0;i<numpixels;i+=1)
      {
        leds[i] = CRGB::Black;
        //leds[i] = CRGB::White;  
      }  
      show();
    }

  private:
    struct CRGB leds[500];
    uint16_t numpixels;
    CRGB enemyColor;
    CRGB playerColor;
};

#endif
