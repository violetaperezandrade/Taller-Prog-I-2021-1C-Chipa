#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <string>
#include <typeinfo>
#ifndef DONKEYKONG_CONFIG_H
#define DONKEYKONG_CONFIG_H


class Config {
private:
    int frameTime;
    int debug;
    std::string path;
    int gravity;
    int climbingSpeed;
    int jumpingSpeed;
    int movingSpeed;
    int flamesLevel1;
    int barrelsLevel2;
    int resolutionWidth;
    int resolutionHeight;

public:
    Config(char* path);
    ~Config();

    int getFrameTime();
    int getDebug();
    std::string getPath();
    int getGravity();
    int getClimbingSpeed();
    int getJumpingSpeed();
    int getMovingSpeed();
    int getFlamesLevel1();
    int getBarrelsLevel2();
    int getResolutionWidth();
    int getResolutionHeight();

};
#endif //DONKEYKONG_CONFIG_H
