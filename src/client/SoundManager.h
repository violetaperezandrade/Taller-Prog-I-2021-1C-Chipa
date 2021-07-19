#ifndef DONKEYKONG_SOUNDMANAGER_H
#define DONKEYKONG_SOUNDMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <vector>
#include <string>
#include "../common/Logger.h"
#include "Monitor.h"

enum soundType{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager {
private:
    Logger& logger;
    bool& play;
    std::map<std::string, Mix_Music*> music;
    std::map<std::string, Mix_Chunk*> sfxs;
    bool load(std::string fileName, std::string id, soundType type);
public:
    SoundManager(Logger& logger, bool& play);

    bool initMixer();

    void playMusic(std::string id, int loop);

    void muteMusic();

    void playFinishMusic();

    void playSound(std::string id, int loop);

    void playSoundFromState(char state);

    void iterateStates(std::vector<char>& states);

    void runLevel1();

    void runLevel2();

    ~SoundManager();

};


#endif //DONKEYKONG_SOUNDMANAGER_H
