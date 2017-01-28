#ifndef ENEMY_CPP
#define ENEMY_CPP
#include <stdint.h>

/*
	typedef struct
	{
		bool doa;//����
		uint8_t type;
		int8_t position;
		uint8_t speed;
		uint8_t range_first;
		uint8_t range_last;
		int8_t dir;//����
		CRGB color;
	}Enemy;
*/
class Enemy
{
  public:
    Enemy():defaultPos(1000),position(1000),speed(1),type(0),dir(-1),alive(false){};
    Enemy(uint16_t pos):defaultPos(pos),position(pos),speed(1),type(0),dir(-1),alive(true){};
    Enemy(uint16_t pos,uint8_t speed):defaultPos(pos),position(pos),speed(speed),type(1),dir(-1),alive(true){};
    Enemy(uint16_t pos,uint8_t speed, uint16_t range):defaultPos(pos),position(pos),speed(speed),range(range),type(2),dir(-1),alive(true){};
    
    Enemy(const Enemy &enemy):defaultPos(enemy.position),position(enemy.position),speed(enemy.speed),type(enemy.type),dir(enemy.dir),alive(enemy.alive){};
    Enemy &operator=(const Enemy &enemy)
    {
      this->defaultPos = enemy.defaultPos;
      this->position = enemy.position;
      this->speed = enemy.speed;
      this->type = enemy.type;
      this->dir = enemy.dir;
      this->alive = enemy.alive;  
    };
    void kill(){
      alive=false;
      tone(8,250,300);  
    };
    void move(){
      if(type==0)
      {
        //do nothing
      }
      else if(type==1){
        position += dir*speed;
        if(position<0)
          kill();
      }
      else if(type==2)
      {
        position+=dir*speed;
        if(position<0)
        {
          position=0;
          dir*=-1;
        }
        else if(position>=NUMPIXELS*20)
        {
          position=(NUMPIXELS-1)*20;
          dir*=-1;  
        }
        else if(position>defaultPos&&position>defaultPos+range)
        {
          dir*=-1;  
          
        }
        else if(position<defaultPos&&position<defaultPos-range)
        {
          dir*=-1;
        }

      }
    };
    bool live(){return alive;}
    uint16_t getPos(){return position/20;};
    void update(uint16_t pos){alive=true;type=0;position=pos;}
    void update(uint16_t pos, uint8_t spd){alive=true;type=1;defaultPos = pos;position=pos;speed=spd;}
    void update(uint16_t pos, uint8_t spd,uint16_t rng){alive=true;type=2;defaultPos = pos;position=pos;speed=spd;range=rng;}
    static void setRange(uint16_t f, uint16_t l)
    {
      first = f;
      last = l;
    };

  private:
    uint8_t speed;
    uint16_t defaultPos;
    int16_t position;
    uint8_t type;
    int8_t dir;
    bool alive;
    uint16_t range;
    static uint16_t first;
    static uint16_t last;
};


#endif
