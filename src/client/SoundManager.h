#ifndef DONKEYKONG_SOUNDMANAGER_H
#define DONKEYKONG_SOUNDMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include<map>
#include <string>
#include "SDLManager.h"
#include "../common/Logger.h"
#include "Monitor.h"


enum soundType{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager {
private:
    Logger& logger;
    //Monitor& monitor; //esto es provisorio
    std::map<std::string, Mix_Music*> music;
    std::map<std::string, Mix_Chunk*> sfxs;
    bool load(std::string fileName, std::string id, soundType type);
public:
    SoundManager(Logger& logger);

    void playMusic(std::string id, int loop);

    void playSound(std::string id, int loop);

    void playSoundFromState(char state);

    void runLevel1(bool& keepRuning);

    void runLevel2(bool& keepRuning);

    ~SoundManager();

};


#endif //DONKEYKONG_SOUNDMANAGER_H
