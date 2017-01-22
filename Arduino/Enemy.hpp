#ifndef ENEMY_CPP
#define ENEMY_CPP
#include <stdint.h>

	typedef struct
	{
		bool doa;//¶€
		uint8_t type;
		int8_t position;
		uint8_t speed;
		uint8_t range_first;
		uint8_t range_last;
		int8_t dir;//Œü‚«
		CRGB color;
	}Enemy;


class EnemyManager
{
	public:
		EnemyManager(){enemyList = NULL;length = 0;};
		EnemyManager(Enemy* list,uint32_t len,uint32_t numpixels){enemyList = list;length = len;num = numpixels;};
		~EnemyManager(){};
		void update(Enemy* list, uint32_t len)
		{
			for(int i=0;i<len;i+=1)
			{
				enemyList[i].doa = false;
			}
			for(int i=0;i<len;i+=1)
			{
				enemyList[i].doa = true;
				enemyList[i].type == list[i].type;
				enemyList[i].position= list[i].position;
				enemyList[i].speed= list[i].speed;
				enemyList[i].range_first= list[i].range_first;
				enemyList[i].range_first= list[i].range_first;
				enemyList[i].dir = -1; 
			}
			length=len;
		};

		void showList()
		{
			for(int i=0;i<length;i+=1)
			{
				if(enemyList[i].doa)
				{
					Serial.print("alive");
				}
				else Serial.print("die");
				Serial.println(enemyList[i].position);
			}
		}
		void move(){
			if(ms==0)
			{
				ms = millis();
			}
			
			if(millis()-ms > 200)
			{
				
				ms = millis();
				for(int i=0;i<length;i+=1)
				{
					if(enemyList[i].doa == true)
					{
						enemyList[i].position = enemyList[i].position+ enemyList[i].dir * enemyList[i].speed;
						if(enemyList[i].position > num-1 || enemyList[i].position < 0)
						{
							enemyList[i].doa = false;
						}
					}
				}
			}
		
		};
		void show(CRGB leds[])
		{
			for(int i=0;i<length;i+=1)
			{
				if(enemyList[i].doa == true)
				{
					leds[enemyList[i].position] = enemyList[i].color;
				}
			}
		};
		void killed(int32_t pos)
		{
			for(int i=0;i<length;i+=1)
			{
				if(enemyList[i].doa == true && enemyList[i].position==pos)
				{
					enemyList[i].doa = false;
					break;
				}
			}
		}
		bool isDied(int32_t pos)
		{
			for(int i=0;i<length;i+=1)
			{
				if(enemyList[i].doa == true&& enemyList[i].position==pos)
				{
					Serial.println(i);
					Serial.println(enemyList[i].position);
					Serial.println(pos);
					return true;
				}
			}
			return false;
			
		}


	private:
		Enemy *enemyList;
		uint32_t length;
		uint32_t ms;
		uint32_t num;

	



};

#endif
