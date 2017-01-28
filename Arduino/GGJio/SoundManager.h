#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#define BEATTIME 200
#define SPEAKER 8

class SoundManager{

public:
  SoundManager(){};
  void shotAtack(){};
  void shotForward(int16_t spd){for(int i=0;i<8;i+=1){tone(SPEAKER,forward[i],10*spd);delay(3);}}; 
  void shotBack(uint16_t spd){for(int i=0;i<8;i+=1){tone(SPEAKER,back[i],10*spd);delay(3);}}
  void shotDamage(){tone(SPEAKER,damage,200);}
  void shotWin(){for(int i=0;i<10;i+=1){tone(SPEAKER,win[i],200);delay(100);}}
  void shotLose(){for(int i=0;i<8;i+=1){tone(SPEAKER,lose[i],8);delay(100);}}
  void shotATK(){tone(SPEAKER,50,200);}

private:
  const uint16_t beat_time = 200;
  const uint8_t speaker_pin = 8;
  uint16_t forward[8] ={200,300,400,600,800,1200,1600,2400};
  uint16_t back[8] = {10,50,80,100,120,150,200,300};
  uint16_t damage[1] = {50};
  uint16_t lose[8] = {523,494,440,392,349,330,294,262};
  uint16_t win[10] = {262,349,262,294,330,349,392,440,494,523};

  


};

#endif
