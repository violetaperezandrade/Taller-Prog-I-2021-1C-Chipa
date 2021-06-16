#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <string>
#include <typeinfo>

#include "Logger.h"

class Config {
private:
    Logger& logger;
    int frameTime;
    int debug;
    std::string path;
    int gravity;
    int climbingSpeed;
    int jumpingSpeed;
    int movingSpeed;
    int flamesLevel1;
    int embersLevel1;
    int barrelsLevel2;
    int resolutionWidth;
    int resolutionHeight;
    int playersAmount;
    std::map<std::string, std::string> userPass;
    bool defaultLog;

public:
    Config(char* str, Logger& logger);
    ~Config();

    int getFrameTime();
    int getDebug();
    std::string getPath();
    int getGravity();
    int getClimbingSpeed();
    int getJumpingSpeed();
    int getMovingSpeed();
    int getFlamesLevel1();
    int getEmbersLevel1();
    int getBarrelsLevel2();
    int getResolutionWidth();
    int getResolutionHeight();
    int getPlayersAmount();
    std::map<std::string, std::string> getUserPass();
    bool getDefault();

};
#endif //CONFIG_H
