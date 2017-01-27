#include <SerialCommand.h>


#include <FastLED.h>
#include <Wire.h>
#include <MPU6050.h>
#include "Enemy.hpp"
#include "Player.h"
#include "OLEDDebugger.h"


#define NUMPIXELS 144
#define DATAPIN 4
#define CLOCKPIN 5

#define INTERRUPT_PIN 2

SerialCommand scmd;
OLEDDebugger debugger;
Player player;



CRGB leds[NUMPIXELS];

void setup()
{
  Serial.begin(38400);
  debugger.print("HELLO");  
  Serial.println("HELLO");
}

void loop(){
  
// player.getInput();
  Serial.println(player.getInput());
//  debugger.print(player.getPosition());  
}
