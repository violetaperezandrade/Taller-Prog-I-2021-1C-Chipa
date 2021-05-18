#include "Config.h"

#include <iostream>

Config::Config(char path){

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
        enemiesQuantity = actualJson["configuration"]["game"]["enemies"][0]["quantity"].asInt();
        enemiesType = actualJson["configuration"]["game"]["enemies"][0]["type"].asString();
        resolutionWidth = actualJson["configuration"]["game"]["resolution"][0]["width"].asInt();
        resolutionHeight = actualJson["configuration"]["game"]["resolution"][0]["height"].asInt();
    }
    else{
        Json::Value defaultJson;
        std::ifstream defaultFile("../src/controller/default_data.json");
        defaultFile >> defaultJson;
        if(!actualJson["configuration"]["game"]["enemies"][0]["quantity"].isNumeric() || actualJson["configuration"]["game"]["enemies"][0]["quantity"].isNull()){
            enemiesQuantity = defaultJson["configuration"]["game"]["enemies"][0]["quantity"].asInt();
        }
        else{
            enemiesQuantity = actualJson["configuration"]["game"]["enemies"][0]["quantity"].asInt();
        }
        if(actualJson["configuration"]["game"]["enemies"][0]["type"].isNull() || actualJson["configuration"]["game"]["enemies"][0]["type"].isNumeric()){
            enemiesType = defaultJson["configuration"]["game"]["enemies"][0]["type"].asString();
        }
        else{
            enemiesType = actualJson["configuration"]["game"]["enemies"][0]["type"].asString();
        }
        if(!actualJson["configuration"]["game"]["resolution"][0]["width"].isNumeric() || actualJson["configuration"]["game"]["resolution"][0]["width"].isNull()){
            resolutionWidth = defaultJson["configuration"]["game"]["resolution"][0]["width"].asInt();
        }
        else{
            resolutionWidth = actualJson["configuration"]["game"]["resolution"][0]["width"].asInt();
        }
        if(!actualJson["configuration"]["game"]["resolution"][0]["height"].isNumeric() || actualJson["configuration"]["game"]["resolution"][0]["height"].isNull()){
            resolutionHeight = defaultJson["configuration"]["game"]["resolution"][0]["height"].asInt();
        }
        else{
            resolutionHeight = actualJson["configuration"]["game"]["resolution"][0]["height"].asInt();
        }

    }
}

int Config::getEnemiesQuantity(){
    return enemiesQuantity;
};

char Config::getEnemiesType(){
    return enemiesType;
};

int Config::getResolutionWidth(){
    return resolutionWidth;
}

int Config::getResolutionHeight(){
    return resolutionHeight;
}

Config::~Config() {}