#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#ifndef DONKEYKONG_CONFIG_H
#define DONKEYKONG_CONFIG_H


class Config {
private:
    int enemiesQuantity;
    std::string enemiesType;
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
