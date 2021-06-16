#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
private:
    std::string path;
    std::ofstream file;
    int logLvl;
    std::mutex m;
public:
    Logger(std::string path);

    void setLevel(int lvl);

    void superDebugMsg(std::string str, std::string filename, int line);

    void debugMsg(std::string str, std::string filename, int line);

    void infoMsg(std::string str, std::string filename, int line);

    void errorMsg(std::string str, std::string filename, int line);

    std::string currentDateTime();

    ~Logger();
};

#endif // LOGGER_H
