//
// Created by violeta on 2/5/21.
//
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
    int enemiesQuantity;
    char enemiesType;
    int resolutionWidth;
    int resolutionHeight;

public:
    Config();
    ~Config();

    int getEnemiesQuantity();
    char getEnemiesType();
    int getResolutionWidth();
    int getResolutionHeight();

};
#endif //DONKEYKONG_CONFIG_H
