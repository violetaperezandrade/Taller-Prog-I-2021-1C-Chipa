#include "Config.h"

#include <iostream>

Config::Config(char* path){

    Json::Value actualJson;
    std::ifstream readFile(path);
    bool valid = true;
    if (readFile) {
        try {
            readFile >> actualJson;
        }
        catch (const std::exception& e) {
            valid = false;
            std::cerr << e.what() << std::endl;
            std::cout<< "json file not valid, using default file" << std::endl;
            std::ifstream readFile("../src/controller/default_data.json");
            readFile >> actualJson;
        }
    }
    else {
        valid = false;
        std::cerr << "Json file not found, using default file" << std::endl;
        std::ifstream readFile("../src/controller/default_data.json");
        readFile >> actualJson;
    }
    Json::Reader reader;
    reader.parse(readFile, actualJson);
    if(!valid){
        frameTime = actualJson["configuration"]["frame time"].asInt();
        debug = actualJson["configuration"]["debug"].asInt();
        path = actualJson["configuration"]["path"].asString();
        gravity = actualJson["configuration"]["gravity"].asInt();
        climbingSpeed = actualJson["character"]["climbing speed"].asInt();
        jumpingSpeed = actualJson["character"]["jumping speed"].asInt();
        movingSpeed = actualJson["character"]["moving speed"].asInt();
        flamesLevel1 = actualJson["level 1"]["flames"].asInt();
        barrelsLevel2 = actualJson["level 2"]["barrels"].asInt();
        resolutionWidth = actualJson["resolution"]["width"].asInt();
        resolutionHeight = actualJson["resolution"]["height"].asInt();
    }
    else{
        Json::Value defaultJson;
        std::ifstream defaultFile("../src/controller/default_data.json");
        defaultFile >> defaultJson;
        if(!actualJson["configuration"]["frame time"].isNumeric() || actualJson["configuration"]["frame time"].isNull()){
            enemiesQuantity = defaultJson["configuration"]["frame time"].asInt();
        }
        else{
            frameTime = actualJson["configuration"]["frame time"].asInt();
        }
        if(!actualJson["configuration"]["debug"].isNumeric() || actualJson["configuration"]["debug"].isNull()){
            debug = defaultJson["configuration"]["debug"].asInt();
        }
        else{
            debug = actualJson["configuration"]["debug"].asInt();
        }
        if(actualJson["configuration"]["path"].isNull() || actualJson["configuration"]["path"].isNumeric()){
            path = defaultJsonactualJson["configuration"]["path"]].asString();
        }
        else{
            path = actualJsonactualJson["configuration"]["path"].asString();
        }
        if(!actualJson["configuration"]["gravity"].isNumeric() || actualJson["configuration"]["gravity"].isNull()){
            gravity = defaultJson["configuration"]["gravity"].asInt();
        }
        else{
            gravity = actualJson["configuration"]["gravity"].asInt();
        }
        if(!actualJson["character"]["climbing speed"].isNumeric() || actualJson["character"]["climbing speed"].isNull()){
            climbingSpeed = defaultJson["character"]["climbing speed"].asInt();
        }
        else{
            climbingSpeed = actualJson["character"]["climbing speed"].asInt();
        }
        if(!actualJson["character"]["jumping speed"].isNumeric() || actualJson["character"]["jumping speed"].isNull()){
            jumpingSpeed = defaultJson["character"]["jumping speed"].asInt();
        }
        else{
            jumpingSpeed = actualJson["character"]["jumping speed"].asInt();
        }
        if(!actualJson["character"]["moving speed"].isNumeric() || actualJson["character"]["moving speed"].isNull()){
            movingSpeed = defaultJson["character"]["moving speed"].asInt();
        }
        else{
            movingSpeed = actualJson["character"]["moving speed"].asInt();
        }
        if(!actualJson["level 1"]["flames"].isNumeric() || actualJson["level 1"]["flames"].isNull()){
            flamesLevel1 = defaultJson["level 1"]["flames"].asInt();
        }
        else{
            flamesLevel1 = actualJson["level 1"]["flames"].asInt();
        }
        if(!actualJson["level 2"]["barrels"].isNumeric() || actualJson["level 2"]["barrels"].isNull()){
            barrelsLevel2 = defaultJson["level 2"]["barrels"].asInt();
        }
        else{
            barrelsLevel2 = actualJson["level 2"]["barrels"].asInt();
        }
        if(!actualJson["resolution"]["width"].isNumeric() || actualJson["resolution"]["width"].isNull()){
            resolutionWidth = defaultJson["resolution"]["width"].asInt();
        }
        else{
            resolutionWidth = actualJson["resolution"]["width"].asInt();
        }
        if(!actualJson["resolution"]["height"].isNumeric() || actualJson["resolution"]["height"].isNull()){
            resolutionHeight = defaultJson["resolution"]["height"].asInt();
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
    return climbingSpeed
};

int Config::getJumpingSpeed(){
    return jumpingSpeed;
};

int Config::getMovingSpeed(){
    return movingSpeed;
};

int getFlamesLevel1(){
    return flamesLevel1;
};

int getBarrelsLevel2(){
    return barrelsLevel2;
};

int Config::getResolutionWidth(){
    return resolutionWidth;
};

int Config::getResolutionHeight(){
    return resolutionHeight;
};

Config::~Config() {}