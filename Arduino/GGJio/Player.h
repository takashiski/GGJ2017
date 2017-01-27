#ifndef PLAYER_H
#define PLAYER_H

#include <Wire.h>
#include <MPU6050.h>

class Player
{
  public:
    Player(){mpu6050.initialize();}
    ~Player(){}
    uint8_t getInput()
    {
      mpu6050.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
      speed = ay/1000;
      attack_range = gy/4000;
      //Serial.print(ay);
      //Serial.println(gy);
      return speed;
    }
    void Kill(){alive = false;}
    void Move(){position+=speed;}
    uint8_t Attack()
    {
        return gy>0?gy:gy*-1;
    }
    uint16_t getPosition(){return position;}
  
  private:
    MPU6050 mpu6050;
    int16_t ax,ay,az;
    int16_t gx,gy,gz;
    uint16_t position;
    int8_t speed;
    int8_t attack_range;
    bool alive;
  
};


#endif
