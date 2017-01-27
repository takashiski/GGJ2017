#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#define BEATTIME 200
#define SPEAKER 8

class SoundManager{

public:
  void 

private:
  const uint16_t beat_time = 200;
  const uint8_t speaker_pin = 8;
  uint16_t forwardSound[] ={200,300,400,600,800,1200,1600,2400};
  uint16_t backSound[] = {10,50,80,100,120,150,200,300};
  uint16_t damegeSound[] = {50};
  uint16_t loseSound[] = {523,494,440,392,349,330,294,262};
  uint16_t winSound[] = {262,349,262,294,330,349,392,440,494,523};


};

#endif
