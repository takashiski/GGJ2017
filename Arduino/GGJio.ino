#include <FastLED.h>
#include <Wire.h>
#include <MPU6050.h>
#include "Enemy.hpp"

#define NUMPIXELS 144
#define DATAPIN 4
#define CLOCKPIN 5

#define THRESHOLD_HIGH 4000
#define THRESHOLD_LOW 2000
#define ATK_THRESHOLD 8000

#define BEATTIME 200
#define SPEAKER 8

uint16_t forwardSound[] ={200,300,400,600,800,1200,1600,2400};
uint16_t backSound[] = {10,50,80,100,120,150,200,300};
uint16_t damegeSound[] = {50};
uint16_t loseSound[] = {523,494,440,392,349,330,294,262};
uint16_t winSound[] = {262,349,262,294,330,349,392,440,494,523};

bool rsv_flag1 = false;
bool rsv_flag2 = false;
bool survive_flag = false;
bool recieve_stage_flag = false;
bool rsv_bytes[128];
uint8_t rsv_len=0;
uint8_t rsv_i = 0;


MPU6050 mpu6050;
int16_t ax,ay,az;
int16_t gx,gy,gz;

int16_t player_pos=1;
CRGB player_color = CRGB::Blue;
uint16_t ms_p;
bool atk_flag = false;
CRGB atk_color = CRGB::Red;
#define INTERRUPT_PIN 2


CRGB enemy_color = CRGB::Azure;

uint8_t enemy_len = 5;
Enemy list[5] = 
{
	{true,0,70,1,0,0,-1,CRGB::Red},
	{true,0,100,2,0,0,-1,CRGB::Red},
	{true,0,144,2,0,0,-1,CRGB::Red},
	{true,0,30,1,0,0,-1,CRGB::Red},
	{true,0,143,1,0,0,-1,CRGB::Red}
};
EnemyManager eManager(list,5, NUMPIXELS);

CRGB leds[NUMPIXELS];

uint32_t counter = 0;



void getInput()
{
  mpu6050.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
}

void movePlayer(int16_t* pos)
{
	if(ms_p==0)ms_p=millis();
	if(millis()-ms_p>30)
	{
		//Serial.print("move");
		//Serial.println(*pos);
	
		ms_p=millis();
		if(gy>ATK_THRESHOLD||gy<-ATK_THRESHOLD) atk_flag=true;
		else
		{
			atk_flag=false;
			if(ay>THRESHOLD_LOW)
			{
				*pos+=1;
        tone(SPEAKER,forwardSound,10);
			}
			if(ay<-THRESHOLD_LOW)
			{
				*pos-=1;
        tone(SPEAKER,backSound,10);
			}

			if(*pos>NUMPIXELS-1)
			{
				*pos=NUMPIXELS-1;
				survive();
				
				survive_flag = true;
			}
			if(*pos<0) *pos=0;
		}
	}
}

void clearLEDs()
{
  for(int i=0;i<NUMPIXELS;i+=1)
  {
    leds[i] = CRGB::Black;
  }
}
void setLEDs()
{
	eManager.show(leds);
  if(atk_flag == false)
  {
    leds[player_pos] = player_color;
		if(eManager.isDied(player_pos))
		{
			for(int i=0;i<10;i+=1)
			{
				tone(SPEAKER,damegeSound[0],200);
				delay(100);
			}
			die();
		}
  }
  else
  { 
    
		for(int i=player_pos-2;i<player_pos+3;i+=1)
		{
    	leds[i] =atk_color;
			eManager.killed(i);
		}
  }
  FastLED.show();

}
void die()
{
	delay(1000);
  for(int i=0;i<8;i+=1)
  {
    tone(SPEAKER,loseSound[i],8);
    delay(100);
  }
	for(int j=0;j<5;j+=1)
	{
		for(int i=0;i<NUMPIXELS;i+=1)
		{
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
		delay(500);
		for(int i=0;i<NUMPIXELS;i+=1)
		{
			leds[i] = CRGB::Black;
		}
		FastLED.show();
		delay(500);

	}
	player_pos=0;
}
void survive()
{
 for(int i=0;i<10;i+=1)
 {
		tone(SPEAKER,winSound[i],200);
		delay(100);
	}
  setSurvivedLED();

}


void setSurvivedLED()
{
  for(int i=0;i<NUMPIXELS;i+=1)
    leds[i] = CRGB::Black;  

  for(int i=NUMPIXELS-1;i>=0;i-=1)
  {
    for(int j=i;j<NUMPIXELS;j+=1)
    {
      leds[j] = CRGB::Red;  
    }
    delay(10);
    FastLED.show();
  }

  

}





//setup and loop *****************************************
void setup() {
  delay(1);
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  mpu6050.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  FastLED.addLeds<APA102, DATAPIN, CLOCKPIN, RGB>(leds, NUMPIXELS);
  FastLED.setBrightness(1);
  
  Serial.begin(9600);
	//Serial.begin(115200);
	Serial.println("INITED");
}


void recieveBytes()
{
  if(Serial.available()>0)
  {
		uint8_t u8 = Serial.read();	
		Serial.println(u8);
		//if(!rsv_flag2&&u8 == 42)//*
		if(!rsv_flag2&&u8 == 200)
		{
			Serial.println("get42");
			rsv_flag1=true;
			return;
		}
		//if(!rsv_flag2&&rsv_flag1&&u8 == 43)//+
		if(!rsv_flag2&&rsv_flag1&&u8 == 250)
		{
			Serial.println("get43");
			rsv_flag2 = true;
			return ;
		}
		if(rsv_flag1&&rsv_flag2)
		{
			if(rsv_len==0)
			{
				//rsv_len = u8-0x30;
				rsv_len = u8;
				Serial.print("set len:");
				Serial.println(rsv_len);  
			}
			else
			{
				Serial.print("set byte:");
//				Serial.println(u8-0x30);
//				rsv_bytes[rsv_i] = u8-0x30;
				rsv_bytes[rsv_i] = u8;
				rsv_i +=1;
				if(rsv_i>=rsv_len)
				{
					rsv_flag1 = false;
					rsv_flag2 = false;
					recieve_stage_flag = true;
					Serial.println("rsv!");  
					for(int i=0;i<NUMPIXELS;i+=1)
					{
						leds[i] = CRGB::White;
					}
					FastLED.show();
					delay(100);
					eManager.showList();

				}  
			}
		}
	} 
}


void createEnemyList()
{
	Serial.println("create Enemy List");
	uint8_t enemy_len = rsv_len;
	Serial.println(enemy_len);
	
	Enemy enemyList[enemy_len];
	for(int j=0;j<enemy_len;j+=1)
	{
		Serial.println(j);
		int i=j*5;

		enemyList[i] = {true,0/*rsv_bytes[i]*/,rsv_bytes[i+1],1/*rsv_bytes[i+2]*/,rsv_bytes[i+3],rsv_bytes[i+4],-1,CRGB::Red};
//		enemyList[i] = {true,rsv_bytes[i],50+i,1,rsv_bytes[i+3],rsv_bytes[i+4],-1,CRGB::Blue};
		leds[rsv_bytes[i+2]] = CRGB::Green;
	}
	FastLED.show();
	delay(1000);

	eManager.update(enemyList,enemy_len);
	eManager.showList();
	player_pos = 0;
	recieve_stage_flag = false;
	survive_flag = false;
	setColor(CRGB::Blue);
	delay(100);
	setColor(CRGB::Red);
	delay(100);
	setColor(CRGB::Blue);
	delay(100);
	setColor(CRGB::Red);
	delay(100);


	
	return;

}

void setColor(CRGB color)
{
	for(int i=0;i<NUMPIXELS;i+=1)
	{
		leds[i]=color;
	}
	FastLED.show();
}

void loop() 
{
	Serial.println("RUNNING");
  if(survive_flag)
  {
		Serial.println("SURVIVED");
    if(recieve_stage_flag)
    {
      createEnemyList();
    }
    else
    {
      recieveBytes();
    }
  }
  else
  {
//		tone(SPEAKER,200,100);
		//Serial.println("PLAYING NOW");
    if(atk_flag)
    {
      tone(SPEAKER,50,BEATTIME);
			Serial.println("ATK");
    }
    getInput();
		Serial.println("INPUT");
  	clearLEDs();
		Serial.println("clear");
  	eManager.move();
		Serial.println("enemy move");
    movePlayer(&player_pos);
		Serial.println("player");
  	setLEDs();
		Serial.println("setLED");
    delay(10);
  }
}

