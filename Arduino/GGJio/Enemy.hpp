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
    Enemy():position(100),speed(1),type(0),dir(-1),alive(true){};
    Enemy(uint16_t pos):position(pos),speed(1),type(0),dir(-1),alive(true){};
    Enemy(uint16_t pos,uint8_t speed):position(pos),speed(speed),type(0),dir(-1),alive(true){};
    Enemy(const Enemy &enemy):position(enemy.position),speed(enemy.speed),type(enemy.type),dir(enemy.dir),alive(enemy.alive){};
    Enemy &operator=(const Enemy &enemy)
    {
      this->position = enemy.position;
      this->speed = enemy.speed;
      this->type = enemy.type;
      this->dir = enemy.dir;
      this->alive = enemy.alive;  
    };
    void Kill(){alive=false;};
    void Move(){position += dir*speed;};
    void getPos(){return position;};
    static void setRange(uint16_t f, uint16_t l)
    {
      first = f;
      last = l;
    };

  private:
    uint8_t speed;
    uint16_t position;
    uint8_t type;
    int8_t dir;
    bool alive;
    static uint16_t first;
    static uint16_t last;
};


#endif
