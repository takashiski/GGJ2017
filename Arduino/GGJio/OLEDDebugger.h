#ifndef OLEDDEBUGGER_H
#define OLEDDEBUGGER_H

#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

class OLEDDebugger{
  public:
    OLEDDebugger()
    {
      display = new Adafruit_SSD1306(OLED_RESET);
    };
    ~OLEDDebugger()
    {
      delete display;
    };

    void begin(){display->begin(SSD1306_SWITCHCAPVCC,0x3c);};
    void print(String str)
    {
      display->setTextSize(1);
      display->setTextColor(WHITE);
      display->setCursor(x,y);
      display->println(str);
      display->display();
      incrementPosition(str.length());
    };
    void println(String str)
    {
        print(str);
        CRLF();
    }
    void print(uint32_t num)
    {
      print(String(num));  
    }
    void incrementPosition(uint16_t len)
    {
      x+=len*x_offset;
      if(x>x_max)CRLF();  
    }
    void CRLF()
    {
      y+=y_offset;
      if(y>y_max){y=0;clear();}
      x=0;  
    };
    
    void clear(){display->clearDisplay();};
    void setPosition(uint8_t x, uint8_t y)
    {
        this->x=x;
        this->y=y;
    };
  private:
    uint8_t x=0;
    uint8_t y=0;
    const uint8_t x_max = 114;
    const uint8_t y_max = 31;
    const uint8_t x_offset = 6;
    const uint8_t y_offset = 8;
    const int8_t OLED_RESET = 4;
    Adafruit_SSD1306 *display = NULL;
};

#endif
