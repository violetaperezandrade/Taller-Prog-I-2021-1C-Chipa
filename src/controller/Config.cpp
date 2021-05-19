#include "Config.h"
#include <iostream>

Config::Config(char* str, Logger& logger) : logger(logger) {
    Json::Value actualJson;
    std::ifstream readFile("../src/controller/data.json");
    bool valid = true;
    if (readFile) {
        try {
            readFile >> actualJson;
        }
        catch (const std::exception& e) {
            valid = false;
            logger.errorMsg("json file not valid, using default file");
            std::ifstream readFile("../src/controller/default_data.json");
            readFile >> actualJson;
        }
    }
    else {
        valid = false;
        logger.errorMsg("Json file not found, using default file");
        std::ifstream readFile("../src/controller/default_data.json");
        readFile >> actualJson;
    }

    if(!valid){
        std::ifstream readFile("../src/controller/default_data.json");
        Json::Value actualJson;
        Json::Reader reader;
        reader.parse(readFile, actualJson);
        frameTime = actualJson["configuration"]["frame time"].asInt();
        debug = actualJson["configuration"]["debug"].asInt();
        path = actualJson["configuration"]["path"].asString();
        gravity = actualJson["configuration"]["gravity"].asInt();
        climbingSpeed = actualJson["character"]["climbing speed"].asInt();
        jumpingSpeed = actualJson["character"]["jumping speed"].asInt();
        movingSpeed = actualJson["character"]["moving speed"].asInt();
        flamesLevel1 = actualJson["level 1"]["flames"].asInt();
        embersLevel1 = actualJson["level 1"]["embers"].asInt();
        barrelsLevel2 = actualJson["level 2"]["barrels"].asInt();
        resolutionWidth = actualJson["resolution"]["width"].asInt();
        resolutionHeight = actualJson["resolution"]["height"].asInt();
    }
    else{
        Json::Reader reader;
        reader.parse(readFile, actualJson);
        Json::Value defaultJson;
        std::ifstream defaultFile("../src/controller/default_data.json");
        defaultFile >> defaultJson;
        if(!actualJson["configuration"]["frame time"].isNumeric() || actualJson["configuration"]["frame time"].isNull()){
            enemiesQuantity = defaultJson["configuration"]["frame time"].asInt();
            logger.debugMsg("Frame time value not found, reading from default");
        }
        else{
            frameTime = actualJson["configuration"]["frame time"].asInt();
        }
        if(!actualJson["configuration"]["debug"].isNumeric() || actualJson["configuration"]["debug"].isNull()){
            debug = defaultJson["configuration"]["debug"].asInt();
            logger.debugMsg("Debug level not found, reading from default");
        }
        else{
            debug = actualJson["configuration"]["debug"].asInt();
        }
        if(actualJson["configuration"]["path"].isNull() || actualJson["configuration"]["path"].isNumeric()){
            path = defaultJson["configuration"]["path"].asString();
            logger.debugMsg("Log file path not found, reading from default");
        }
        else{
            path = actualJson["configuration"]["path"].asString();
        }
        if(!actualJson["configuration"]["gravity"].isNumeric() || actualJson["configuration"]["gravity"].isNull()){
            gravity = defaultJson["configuration"]["gravity"].asInt();
            logger.debugMsg("Gravity value not found, reading from default");
        }
        else{
            gravity = actualJson["configuration"]["gravity"].asInt();
        }
        if(!actualJson["character"]["climbing speed"].isNumeric() || actualJson["character"]["climbing speed"].isNull()){
            climbingSpeed = defaultJson["character"]["climbing speed"].asInt();
            logger.debugMsg("Climbing speed value not found, reading from default");
        }
        else{
            climbingSpeed = actualJson["character"]["climbing speed"].asInt();
        }
        if(!actualJson["character"]["jumping speed"].isNumeric() || actualJson["character"]["jumping speed"].isNull()){
            jumpingSpeed = defaultJson["character"]["jumping speed"].asInt();
            logger.debugMsg("Jumping speed value not found, reading from default");
        }
        else{
            jumpingSpeed = actualJson["character"]["jumping speed"].asInt();
        }
        if(!actualJson["character"]["moving speed"].isNumeric() || actualJson["character"]["moving speed"].isNull()){
            movingSpeed = defaultJson["character"]["moving speed"].asInt();
            logger.debugMsg("Moving speed value not found, reading from default");
        }
        else{
            movingSpeed = actualJson["character"]["moving speed"].asInt();
        }
        if(!actualJson["level 1"]["embers"].isNumeric() || actualJson["level 1"]["embers"].isNull()){
            embersLevel1 = defaultJson["level 1"]["embers"].asInt();
            logger.debugMsg("Level 1 embers quantity not found, reading from default");
        }
        else{
            embersLevel1 = actualJson["level 1"]["embers"].asInt();
        }
        if(!actualJson["level 1"]["flames"].isNumeric() || actualJson["level 1"]["flames"].isNull() || actualJson["level 1"]["flames"].asInt() < 0 || actualJson["level 1"]["flames"].asInt() > 21){
            flamesLevel1 = defaultJson["level 1"]["flames"].asInt();
            logger.debugMsg("Level 1 flames quantity not found, reading from default");
        }
        else{
            flamesLevel1 = actualJson["level 1"]["flames"].asInt();
        }
        if(!actualJson["level 2"]["barrels"].isNumeric() || actualJson["level 2"]["barrels"].isNull()){
            barrelsLevel2 = defaultJson["level 2"]["barrels"].asInt();
            logger.debugMsg("Level 2 barrels quantity not found, reading from default");
        }
        else{
            barrelsLevel2 = actualJson["level 2"]["barrels"].asInt();
        }
        if(!actualJson["resolution"]["width"].isNumeric() || actualJson["resolution"]["width"].isNull()){
            resolutionWidth = defaultJson["resolution"]["width"].asInt();
            logger.debugMsg("Resolution width value not found, reading from default");
        }
        else{
            resolutionWidth = actualJson["resolution"]["width"].asInt();
        }
        if(!actualJson["resolution"]["height"].isNumeric() || actualJson["resolution"]["height"].isNull()){
            resolutionHeight = defaultJson["resolution"]["height"].asInt();
            logger.debugMsg("Resolution height value not found, reading from default");
        }
        else{
            resolutionHeight = actualJson["resolution"]["height"].asInt();
        }
    }
}


int Config::getFrameTime(){
    return frameTime;
};

int Config::getDebug(){
    return debug;
};

std::string Config::getPath(){
    return path;
};

int Config::getGravity(){
    return gravity;
};

int Config::getClimbingSpeed(){
    return climbingSpeed;
};

int Config::getJumpingSpeed(){
    return jumpingSpeed;
};

int Config::getMovingSpeed(){
    return movingSpeed;
};

int Config::getFlamesLevel1(){
    return flamesLevel1;
};

int Config::getBarrelsLevel2(){
    return barrelsLevel2;
};

int Config::getResolutionWidth(){
    return resolutionWidth;
};

int Config::getResolutionHeight(){
    return resolutionHeight;
};

Config::~Config() {}