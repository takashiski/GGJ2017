#ifndef APA102MANAGER_H
#define APA102MANAGER_H

#include<FastLED.h>
#define DATAPIN 4
#define CLOCKPIN 5
#define NUMPIXELS 300
#define BRIGHTNESS 255


class APA102Manager
{
  public:
    APA102Manager()
    {
      FastLED.addLeds<APA102,DATAPIN,CLOCKPIN,BGR>(leds,NUMPIXELS,0);
      FastLED.setBrightness(BRIGHTNESS);
      numpixels = NUMPIXELS;
      for(int i=0;i<numpixels;i+=1)
      {
        leds[i] = CRGB::White;  

      }
      show();
//      delay(5000);
    };
    ~APA102Manager(){};
    void show(){FastLED.show();}
    CRGB getColor(uint16_t pos){return leds[pos];}
    void setColor(uint16_t pos,CRGB color)
    {
      leds[pos] = color;  
    };
    void setColor(uint16_t *poses,uint16_t len,CRGB color)
    {
      for(uint16_t i=0;i<len;i+=1)
      {
        setColor(poses[i],color);
      }
  
    }
    void setEnemy(uint16_t pos){setColor(pos,enemyColor);}
    void setPlayer(uint16_t pos){setColor(pos,playerColor);}
    void setYellow(uint16_t pos, uint8_t brightness){setColor(pos,CRGB(brightness,brightness,0));}
    void setRed(uint16_t pos, uint8_t brightness){setColor(pos,CRGB(brightness,0,0));}
    void setGreen(uint16_t pos, uint8_t brightness){setColor(pos,CRGB(0,brightness,0));}
    void setBlue(uint16_t pos, uint8_t brightness){setColor(pos,CRGB(0,0,brightness));}
    void setPurple(uint16_t pos, uint8_t brightness){setColor(pos,CRGB(brightness,0,brightness));}
    void setSkyBlue(uint16_t pos, uint8_t brightness){setColor(pos,CRGB(0,brightness,brightness));}
    
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
