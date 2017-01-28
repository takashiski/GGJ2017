#include <SerialCommand.h>


//#include <FastLED.h>
#include <Wire.h>
#include <MPU6050.h>
#include "APA102Manager.h"
#include "Enemy.hpp"
#include "Player.h"
#include "OLEDDebugger.h"
#include "SoundManager.h"

#define NUMENEMIES 20
#define INTERRUPT_PIN 2

SerialCommand scmd;
//OLEDDebugger debugger;
Player player;
APA102Manager apa102;
Enemy enemies[NUMENEMIES];
SoundManager smanager;
int8_t stageArray[NUMPIXELS];
bool serial_flag = false;
uint8_t level_num=0;


void initEnemies(uint8_t level_num)
{
  switch(level_num)
  {
    case 0:initLevel0();break;
    case 1:initLevel1();break;
    case 2:initLevel2();break;
    case 3:initLevel3();break;
    case 4:initLevel4();break;
    default:break;
  }
}

void initLevel0()
{
  for(int i=0;i<NUMENEMIES;i+=1)
  {
    if(i<10)
    {
      enemies[i].update(i*400+700+i*13);  
    }
  }
}

void initLevel1()
{
  for(int i=0;i<NUMENEMIES;i+=1)
  {
      enemies[i].update(700+i*300+i*17,1);
  }  
}
void initLevel2()
{
  for(int i=0;i<NUMENEMIES;i+=1)
  {
    enemies[i].update(700+i*300,1,(i%5+1)*50);
  }  
}

void initLevel3()
{
  for(int i=0;i<NUMENEMIES;i+=1)
  {
    enemies[i].update(700+i*300,i%3+1,(i%5+1)*50);
  }  
}
void initLevel4()
{
  for(int i=0;i<NUMENEMIES;i+=1)
  {
    switch(random(0,99)%5)
    {
      case 0:
        enemies[i].update(random(i*100,i*100+150)+600);
        break;
      case 1:
        enemies[i].update(random(i*100,i*100+150)+1000,i%5+1);
        break;
      case 2:
      case 3:
      case 4: 
        enemies[i].update(random(i*1000,i*1000+1500)+1000,i%5+1,random(0,200)+100);
        break;
    }
  }  
}

CRGB leds[NUMPIXELS];

void setup()
{
  Wire.begin();
  Serial.begin(38400);
//  debugger.print("HELLO");  
  Serial.println("HELLO");
  randomSeed(analogRead(0));
  initEnemies(level_num++);
  initStage();
  scmd.addCommand("SEND",getNewEnemies);
  scmd.addDefaultHandler(defaultHandler);
}

void getNewEnemies()
{
  char *arg;
  arg = scmd.next();
  if(arg!=NULL)
    Serial.println(arg);
  Serial.println("RECIEVED");  
  serial_flag = false;
}

void defaultHandler()
{
  char *arg;
  arg = scmd.next();
  Serial.println("Uh?");
  int i=0;
  while(arg[i++]!=NULL)
  {
    Serial.println(arg[i]);
  } 
//  Serial.println("RECIEVED"); 
}

void initStage()
{
  for(int i=0;i<NUMPIXELS;i+=1)
    stageArray[i] = 0;  
}

void loop(){
  if(serial_flag)
  {
    scmd.readSerial();  
  }
  else
  {
    initStage();
    
    apa102.show(); 
    apa102.resetColor();
  
  
   player.getInput();
//    Serial.println(player.getInput());
    if(player.attack())
    {
      smanager.shotATK();
      int8_t atk_range = player.getAtkRange();
      int16_t pos = player.getPosition();
      for(int i = -atk_range;i<atk_range;i+=1)
      {
        if(pos+i>=0&&pos+i<NUMPIXELS)
        {
         apa102.setColor(pos+i,CRGB::Red);
         stageArray[pos+i] = 1;
        }
      }
    }
    else
    {  
      int16_t spd = player.move();
      /*
      if(spd>0)
      {
        smanager.shotForward(spd);
      }
      else if(spd<0)
      {
        smanager.shotBack(spd); 
      }
      */
      apa102.setColor(player.getPosition(),CRGB::Blue);
      stageArray[player.getPosition()] = -1;
    }
  
    for(int i=0;i<NUMENEMIES;i+=1)
    {
      if(enemies[i].live())
      {
        enemies[i].move();
        uint16_t pos = enemies[i].getPos();
        if(stageArray[pos]>0)
        {
          enemies[i].kill();
        }
        else if(stageArray[pos]<0)
        {
          player.kill();
          //enemies[i].kill();
          apa102.setColor(enemies[i].getPos()-1,CRGB::Purple);  
          apa102.setColor(enemies[i].getPos(),CRGB::Purple);  
          apa102.setColor(enemies[i].getPos()+1,CRGB::Purple); 
          apa102.show();
          delay(1000); 
        }
        else
        {
          apa102.setColor(enemies[i].getPos(),CRGB::Green);  
  
        }
      }  
    }
  
    if(player.reached())
    {
      smanager.shotWin();
      for(int i=0;i<NUMPIXELS;i+=1)
      {
        apa102.setColor(NUMPIXELS-i-1,CRGB::Blue);
        apa102.show();
        delay(10);
      }
      //serial_flag = true;
      Serial.println(level_num);
      initEnemies(level_num++);
      player.restart();
    }
  
    else if(player.died())
    {
      int16_t pos = player.getPosition();
      smanager.shotLose();
      for(int i=0;i<NUMPIXELS;i+=1)
      {
        
        if(pos+i<NUMPIXELS)
          apa102.setColor(pos+i,CRGB::Red);
        if(pos-i>=0)
          apa102.setColor(pos-i,CRGB::Red);
        apa102.show();
       // delay(10);
      }
      for(int i=0;i<NUMPIXELS;i+=1)
      {
        apa102.setColor(NUMPIXELS-i-1,CRGB::White);
        apa102.show();  
      }
      player.restart();
  
    }  
  }
  

}
