#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
#include <fstream>

class Logger {
private:
    std::string path;
    std::ofstream file;
    int logLvl;
public:
    Logger(std::string path, int logLvl);

    void debugMsg(std::string str);

    void infoMsg(std::string str);

    void errorMsg(std::string str);

    std::string currentDateTime();

    ~Logger();
};

#endif // LOGGER_H
