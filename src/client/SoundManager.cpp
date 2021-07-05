#include "SoundManager.h"

SoundManager::SoundManager(Logger& logger) :
logger(logger){
    load("../src/client/music/auxStage1_BGM.mp3", "level 1", SOUND_MUSIC);
    load("../src/client/music/Stage2_BGM.mp3", "level 2", SOUND_MUSIC);
    load("../src/client/sfx/SFX_Walking.mp3", "mario move", SOUND_SFX);
    load("../src/client/sfx/SFX_Jump.mp3", "mario jump", SOUND_SFX);
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
    std::string move = "6789";
    std::string jump = "12";
    std::string id(1, state);
    if (move.find(id) != std::string::npos){
        playSound("mario move", 0);
    }
    else if(jump.find(id) != std::string::npos){
        playSound("mario jump", 0);
    }
    else return;
}

void SoundManager::runLevel1(bool& keepRuning){
    playMusic("level 1", -1);
    //esto en realidad va a ir en el input, es provisorio!!!
    /*SDL_Event e;
    while(keepRuning){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_KEYDOWN){
                switch( e.key.keysym.sym ){
                    case SDLK_p:
                        if(Mix_PausedMusic() == 1) Mix_ResumeMusic();
                        else Mix_PauseMusic();
                        break;
                    case SDLK_0:
                        Mix_HaltMusic();
                        break;
                    default:
                        break;
                }
            }
        }

    }*/
}

void SoundManager::runLevel2(bool& keepRuning){
    Mix_HaltMusic();
    playMusic("level 2", -1);
    //esto en realidad va a ir en el input, es provisorio!!!
    /*SDL_Event e;
    while(keepRuning){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_KEYDOWN){
                switch( e.key.keysym.sym ){
                    case SDLK_p:
                        if(Mix_PausedMusic() == 1) Mix_ResumeMusic();
                        else Mix_PauseMusic();
                        break;
                    case SDLK_0:
                        Mix_HaltMusic();
                        break;
                    default:
                        break;
                }
            }
        }

    }*/
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
