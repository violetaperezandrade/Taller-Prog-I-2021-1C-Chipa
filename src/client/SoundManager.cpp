#include "SoundManager.h"

SoundManager::SoundManager(Logger& logger, bool& play) :
logger(logger),
play(play){
    if (initMixer() < 0){
        logger.errorMsg("Fallo initSDL", __FILE__, __LINE__);
    }
    load("../src/client/music/Stage1_BGM.wav", "level 1", SOUND_MUSIC);
    load("../src/client/music/Stage2_BGM.wav", "level 2", SOUND_MUSIC);
    load("../src/client/sfx/SFX_Walking.wav", "mario move", SOUND_SFX);
    load("../src/client/sfx/SFX_Jump.wav", "mario jump", SOUND_SFX);
}

bool SoundManager::initMixer(){
    bool error = false;
    if(Mix_OpenAudio( 22050, AUDIO_S16, 2, 4096 ) < 0){
        logger.errorMsg("Error al inicializar SDL Mixer", __FILE__, __LINE__);
        error = true;
    }
    return error;
}

bool SoundManager::load(std::string fileName, std::string id, soundType type){
    if (type == SOUND_SFX){
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if (pChunk == 0){
            logger.errorMsg("No se pudo cargar correctamente SFX", __FILE__, __LINE__);
            return false;
        }
        sfxs[id] = pChunk;
        return true;
    }
    else if(type == SOUND_MUSIC){
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if (pMusic == 0){
            logger.errorMsg("No se pudo cargar correctamente la musica", __FILE__, __LINE__);
            return false;
        }
        music[id] = pMusic;
        return true;
    }
    return false;
}

void SoundManager::playMusic(std::string id, int loop){
    Mix_PlayMusic(music[id], loop);
}

void SoundManager::playSound(std::string id, int loop){ //0
    Mix_PlayChannel(-1, sfxs[id], loop);
}

void SoundManager::playSoundFromState(char state){
    std::string move = "6789AB";
    std::string jump = "12CD";
    std::string id(1, state);
    if (move.find(id) != std::string::npos){
        playSound("mario move", 0);
    }
    else if(jump.find(id) != std::string::npos){
        playSound("mario jump", 0);
    }
    else return;
}

void SoundManager::iterateStates(std::vector<char>& states){
    std::vector<char>::iterator it = states.begin();
    while (it != states.end()) {
        playSoundFromState(*it);
        ++it;
    }
    states.clear();
}

void SoundManager::runLevel1(){
    if (play && Mix_PausedMusic() == 1) Mix_ResumeMusic();
    if (!play && Mix_PausedMusic() != 1) Mix_PauseMusic();
}

void SoundManager::runLevel2(){
    Mix_HaltMusic();
    if (play && Mix_PausedMusic() == 1) Mix_ResumeMusic();
    if (!play && Mix_PausedMusic() != 1) Mix_PauseMusic();
}

SoundManager::~SoundManager(){
    Mix_FreeMusic(music["level 1"]);
    Mix_FreeChunk(sfxs["mario move"]);
    Mix_FreeChunk(sfxs["mario jump"]);
    music["level 1"] = nullptr;
    sfxs["mario move"] = nullptr;
    sfxs["mario jump"] = nullptr;
    Mix_Quit();
}
