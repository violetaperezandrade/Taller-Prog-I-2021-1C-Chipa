#include "Config.h"
#include <nlohmann/json.hpp>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <string_view>
using json = nlohmann::json;

Config::Config(char* str, Logger& logger) : logger(logger) {
    Json::Value actualJson;
    std::ifstream readFile(str);
    bool valid = true;
    if (readFile) {
        try {
            readFile >> actualJson;
        }
        catch (const std::exception& e) {
            valid = false;
            logger.errorMsg("json file not valid, using default file", __FILE__, __LINE__);
            std::ifstream readFile("../src/common/default_data.json");
            readFile >> actualJson;
        }
    }
    else {
        valid = false;
        logger.errorMsg("Json file not found, using default file", __FILE__, __LINE__);
        std::ifstream readFile("../src/common/default_data.json");
        readFile >> actualJson;
    }

    if(!valid){
        std::ifstream readFile("../src/common/default_data.json");
        std::ifstream nhFile("../src/common/data.json");
        json j = json::parse(nhFile);
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
        playersAmount = actualJson["players amount"].asInt();
        userPass = j.at("user password").get<std::map<std::string, std::string>>();
    }
    else{
        Json::Reader reader;
        reader.parse(readFile, actualJson);
        std::ifstream nhFile(str);
        json j = json::parse(nhFile);
        std::ifstream nhFileDefault("../src/common/default_data.json");
        json jDefault = json::parse(nhFileDefault);
        Json::Value defaultJson;
        std::ifstream defaultFile("../src/common/default_data.json");
        defaultFile >> defaultJson;
        if(!actualJson["configuration"]["frame time"].isNumeric() || actualJson["configuration"]["frame time"].isNull()){
            frameTime = defaultJson["configuration"]["frame time"].asInt();
            logger.debugMsg("Frame time value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            frameTime = actualJson["configuration"]["frame time"].asInt();
        }
        if(!actualJson["configuration"]["debug"].isNumeric() || actualJson["configuration"]["debug"].isNull()){
            debug = defaultJson["configuration"]["debug"].asInt();
            logger.debugMsg("Debug level not found, reading from default", __FILE__, __LINE__);
        }
        else{
            debug = actualJson["configuration"]["debug"].asInt();
        }
        if(actualJson["configuration"]["path"].isNull() || actualJson["configuration"]["path"].isNumeric()){
            path = defaultJson["configuration"]["path"].asString();
            logger.debugMsg("Log file path not found, reading from default", __FILE__, __LINE__);
        }
        else{
            path = actualJson["configuration"]["path"].asString();
        }
        if(!actualJson["configuration"]["gravity"].isNumeric() || actualJson["configuration"]["gravity"].isNull()){
            gravity = defaultJson["configuration"]["gravity"].asInt();
            logger.debugMsg("Gravity value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            gravity = actualJson["configuration"]["gravity"].asInt();
        }
        if(!actualJson["character"]["climbing speed"].isNumeric() || actualJson["character"]["climbing speed"].isNull()){
            climbingSpeed = defaultJson["character"]["climbing speed"].asInt();
            logger.debugMsg("Climbing speed value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            climbingSpeed = actualJson["character"]["climbing speed"].asInt();
        }
        if(!actualJson["character"]["jumping speed"].isNumeric() || actualJson["character"]["jumping speed"].isNull()){
            jumpingSpeed = defaultJson["character"]["jumping speed"].asInt();
            logger.debugMsg("Jumping speed value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            jumpingSpeed = actualJson["character"]["jumping speed"].asInt();
        }
        if(!actualJson["character"]["moving speed"].isNumeric() || actualJson["character"]["moving speed"].isNull()){
            movingSpeed = defaultJson["character"]["moving speed"].asInt();
            logger.debugMsg("Moving speed value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            movingSpeed = actualJson["character"]["moving speed"].asInt();
        }
        if(!actualJson["level 1"]["embers"].isNumeric() || actualJson["level 1"]["embers"].isNull()){
            embersLevel1 = defaultJson["level 1"]["embers"].asInt();
            logger.debugMsg("Level 1 embers quantity not found, reading from default", __FILE__, __LINE__);
        }
        else{
            embersLevel1 = actualJson["level 1"]["embers"].asInt();
        }
        if(!actualJson["level 1"]["flames"].isNumeric() || actualJson["level 1"]["flames"].isNull() || actualJson["level 1"]["flames"].asInt() < 0 || actualJson["level 1"]["flames"].asInt() > 21){
            flamesLevel1 = defaultJson["level 1"]["flames"].asInt();
            logger.debugMsg("Level 1 flames quantity not found, reading from default", __FILE__, __LINE__);
        }
        else{
            flamesLevel1 = actualJson["level 1"]["flames"].asInt();
        }
        if(!actualJson["level 2"]["barrels"].isNumeric() || actualJson["level 2"]["barrels"].isNull()){
            barrelsLevel2 = defaultJson["level 2"]["barrels"].asInt();
            logger.debugMsg("Level 2 barrels quantity not found, reading from default", __FILE__, __LINE__);
        }
        else{
            barrelsLevel2 = actualJson["level 2"]["barrels"].asInt();
        }
        if(!actualJson["resolution"]["width"].isNumeric() || actualJson["resolution"]["width"].isNull()){
            resolutionWidth = defaultJson["resolution"]["width"].asInt();
            logger.debugMsg("Resolution width value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            resolutionWidth = actualJson["resolution"]["width"].asInt();
        }
        if(!actualJson["resolution"]["height"].isNumeric() || actualJson["resolution"]["height"].isNull()){
            resolutionHeight = defaultJson["resolution"]["height"].asInt();
            logger.debugMsg("Resolution height value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            resolutionHeight = actualJson["resolution"]["height"].asInt();
        }
        if(!actualJson["players amount"].isNumeric() || actualJson["players amount"].isNull()){
            playersAmount = defaultJson["players amount"].asInt();
            logger.debugMsg("Players amount value not found, reading from default", __FILE__, __LINE__);
        }
        else{
            playersAmount = actualJson["players amount"].asInt();
        }
        if(!j.contains("user password")){
            userPass = jDefault.at("user password").get<std::map<std::string, std::string>>();
            logger.debugMsg("Usernames and passwords values not found, reading from default", __FILE__, __LINE__);
        }
        else{
            userPass = j.at("user password").get<std::map<std::string, std::string>>();
            //if(json::accept(j.at("user password"))){
            //    userPass = j.at("user password").get<std::map<std::string, std::string>>();
            //}
            //else{
            //    userPass = jDefault.at("user password").get<std::map<std::string, std::string>>();
            //    logger.debugMsg("Usernames and passwords values not valid, reading from default", __FILE__, __LINE__);
            }
        }
    defaultLog = !valid; //json not valid then use default log true
}


int Config::getFrameTime(){
    return frameTime;
}

int Config::getDebug(){
    return debug;
}

std::string Config::getPath(){
    return path;
}

int Config::getGravity(){
    return gravity;
}

int Config::getClimbingSpeed(){
    return climbingSpeed;
}

int Config::getJumpingSpeed(){
    return jumpingSpeed;
}

int Config::getMovingSpeed(){
    return movingSpeed;
}

int Config::getFlamesLevel1(){
    return flamesLevel1;
}

int Config::getEmbersLevel1(){
    return embersLevel1;
}

int Config::getBarrelsLevel2(){
    return barrelsLevel2;
}

int Config::getResolutionWidth(){
    return resolutionWidth;
}

int Config::getResolutionHeight(){
    return resolutionHeight;
}

int Config::getPlayersAmount(){
    return playersAmount;
}

std::map<std::string, std::string> Config::getUserPass(){
    return userPass;
}

bool Config::getDefault(){
    return defaultLog;
}

Config::~Config() {}