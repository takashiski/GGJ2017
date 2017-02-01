#ifndef PLAYER_H
#define PLAYER_H
#include<math.h>
#include<RunningMedian.h>
#include <I2Cdev.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include <Wire.h>
#endif
#include <MPU6050.h>
#define INTERRUPT_PIN 2
RunningMedian medianQueue(10);

class Player
{
  public:
    void init(){
      pinMode(INTERRUPT_PIN, INPUT);
      #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
          Wire.begin();
      #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
          Fastwire::setup(400, true);
      #endif

      mpu6050.initialize();

    }
    Player(){alive=true;}
    //Player(){mpu6050.initialize();}
    ~Player(){}
    uint8_t getInput()
    {
      mpu6050.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
      speed = (int16_t)ay/2000;
      medianQueue.add(fabs(gy));
      atk_range = medianQueue.getMedian();
//      Serial.println(ay);
      return speed;
    }
    void kill(){
      alive = false;
    
    }
    bool move(){
      position+=speed;
      if(position<0)
        position=0;
//      Serial.println(position);
      return speed;
    }
    bool attack()
    {
        if(fabs(ay)>20000)
        {
          atk_flag = true;  
        }
        else
        {
          atk_flag = false;  
        }
        return atk_flag;
    }
    int8_t getAtkRange(){return atk_range/2000>4?4:atk_range/2000;}
    uint16_t getPosition(){
//      Serial.println(position/10);
      return position/10;}

    bool reached()
    {
      return position/10>NUMPIXELS;  
    }
    bool died()
    {
      return !alive;  
    }
    void restart()
    {
      position=0;
      alive = true;
    }

  
  private:
    MPU6050 mpu6050;
    int16_t ax,ay,az;
    int16_t gx,gy,gz;
    int16_t position;//100で割るくらい
    int16_t speed;
    int16_t atk_range;
    bool atk_flag;
    bool alive=true;
  
};


#endif
