#include "SoundManager.h"

SoundManager::SoundManager(Logger& logger, bool& play) :
logger(logger),
play(play){
    if (initMixer() < 0){
        logger.errorMsg("Error al inicializar SDL Mixer", __FILE__, __LINE__);
    }
    load("../src/client/music/Stage1_BGM.wav", "level 1", SOUND_MUSIC);
    load("../src/client/music/Stage2_BGM-[AudioTrimmer.com].wav", "level 2", SOUND_MUSIC);
    load("../src/client/music/all-rounds-clear.wav", "finish success", SOUND_MUSIC);
    load("../src/client/sfx/SFX_Walking-[AudioTrimmer.com].wav", "mario move", SOUND_SFX);
    load("../src/client/sfx/SFX_Jump-[AudioTrimmer.com].wav", "mario jump", SOUND_SFX);
    load("../src/client/sfx/SFX_Bonus-[AudioTrimmer.com] (1).wav", "bonus", SOUND_SFX);
    load("../src/client/sfx/death-[AudioTrimmer.com].wav", "mario dead", SOUND_SFX);
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
            logger.errorMsg(fileName.c_str(), __FILE__, __LINE__);
            return false;
        }
        music[id] = pMusic;
        return true;
    }
    return false;
}

void SoundManager::playFinishMusic(){
    Mix_HaltMusic();
    playMusic("finish success", -1);
}

void SoundManager::playMusic(std::string id, int loop){
    if (id == "level 2"){
        Mix_HaltMusic();
    }
    Mix_PlayMusic(music[id], loop);
}

void SoundManager::playSound(std::string id, int loop){ //0
    Mix_PlayChannel(-1, sfxs[id], loop);
}

void SoundManager::playSoundFromState(char state){
    std::string move = "6789CD";
    std::string jump = "12AB";
    std::string id(1, state);
    if (move.find(id) != std::string::npos){
        playSound("mario move", 0);
    }
    else if(jump.find(id) != std::string::npos){
        playSound("mario jump", 0);
    }
    else if(state == 'X'){
        Mix_HaltMusic();
        playSound("mario dead", 0);
    }
    else if(state == 'h'){
        playSound("bonus", 0);
    }
    else return;
}

void SoundManager::iterateStates(std::vector<char>& states){
    auto it = states.begin();
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
    if (play && Mix_PausedMusic() == 1) Mix_ResumeMusic();
    if (!play && Mix_PausedMusic() != 1) Mix_PauseMusic();
}

SoundManager::~SoundManager(){
    Mix_FreeMusic(music["level 1"]);
    Mix_FreeMusic(music["level 2"]);
    Mix_FreeChunk(sfxs["mario move"]);
    Mix_FreeChunk(sfxs["mario jump"]);
    Mix_FreeChunk(sfxs["mario dead"]);
    Mix_FreeChunk(sfxs["bonus"]);
    music["level 1"] = nullptr;
    music["level 2"] = nullptr;
    sfxs["mario move"] = nullptr;
    sfxs["mario jump"] = nullptr;
    sfxs["mario dead"] = nullptr;
    sfxs["bonus"] = nullptr;
    Mix_Quit();
}



