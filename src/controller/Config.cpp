//
// Created by violeta on 2/5/21.
//

#include "Config.h"

Config::Config(){
    ifstream file("data.json");
    Json::Value actualJson;
    Json::Reader reader;

    reader.parse(file, actualJson);

    enemiesQuantity = actualJson["configuration"]["game"]["enemies"][0]["quantity"];
    enemiesType = actualJson["configuration"]["game"]["enemies"][0]["type"];
    resolutionWidth = actualJson["configuration"]["game"]["resolution"][0]["width"];
    resolutionHeight = actualJson["configuration"]["game"]["resolution"][0]["height"];

}

Config::Config(char path){
    ifstream file(path);
    Json::Value actualJson;
    Json::Reader reader;

    reader.parse(file, actualJson);

    enemiesQuantity = actualJson["configuration"]["game"]["enemies"][0]["quantity"];
    enemiesType = actualJson["configuration"]["game"]["enemies"][0]["type"];
    resolutionWidth = actualJson["configuration"]["game"]["resolution"][0]["width"];
    resolutionHeight = actualJson["configuration"]["game"]["resolution"][0]["height"];
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