#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#define BEATTIME 200
#define SPEAKER 8

class SoundManager{

public:
  SoundManager(){};
  void shotSound(uint16_t *sounds, uint16_t len, uint16_t duration)
  {
    for(uint16_t i=0;i<len&&i<8;i+=1)
    {
      tone(SPEAKER,sounds[i],duration);  
      delay(duration);
    }  
  }
  void shotSound(uint16_t *sounds, uint16_t len)
  {
    for(uint16_t i=0;i<len;i+=1)
    {
      tone(SPEAKER,sounds[i]);  
    }  
  }
  void shotAttack(){shotSound(attack,1,10);};
  void shotForward(int16_t spd){shotSound(forward,spd,10);}; 
  void shotBack(uint16_t spd){shotSound(back,spd,10);}
  void shotDamage(){tone(SPEAKER,damage,200);}
  void shotWin(){shotSound(win,10,200);}
  void shotLose(){shotSound(lose,8,200);}
  void shotATK(){tone(SPEAKER,50,200);}

private:
  const uint16_t beat_time = 200;
  const uint8_t speaker_pin = 8;
  uint16_t attack[5] = {600,800,1000,1200,1400};
  uint16_t forward[8] ={200,300,400,600,800,1200,1600,2400};
  uint16_t back[8] = {10,50,80,100,120,150,200,300};
  uint16_t damage[1] = {300};
  uint16_t lose[8] = {523,494,440,392,349,330,294,262};
  uint16_t win[10] = {262,349,262,294,330,349,392,440,494,523};

  


};

#endif
