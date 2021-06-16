#include "Logger.h"
#include <time.h>

Logger::Logger(std::string path) :
    path(path),
    file(),
    logLvl(1)

{
    file.open(path);
    //file.open(path,std::ofstream::app);
    //if(!file.is_open()) hacemos algo
    file << "------------------------------------------------------------------------------------------\n";
}

void Logger::setLevel(int lvl) {
    logLvl = lvl;
}

void Logger::superDebugMsg(std::string str, std::string filename, int line){//logLvl SUPER_DEBUG 4
    if(logLvl < 4) {
        return;
    }
    std::unique_lock<std::mutex> lock(m);
    file << currentDateTime() << " [S.DEBUG]: ";
    int pos = filename.find_last_of("/");
    file << filename.substr(pos+1) << ':' << std::to_string(line) << ". ";
    file << str << std::endl;
}

void Logger::debugMsg(std::string str, std::string filename, int line){//logLvl DEBUG 3
    if(logLvl < 3) {
        return;
    }
    std::unique_lock<std::mutex> lock(m);
    file << currentDateTime() << " [DEBUG]: ";
    int pos = filename.find_last_of("/");
    file << filename.substr(pos+1) << ':' << std::to_string(line) << ". ";
    file << str << std::endl;
}

void Logger::infoMsg(std::string str, std::string filename, int line){//logLvl INFO 2
    if (logLvl < 2) {
        return;
    }
    std::unique_lock<std::mutex> lock(m);
    file << currentDateTime() << " [INFO]: ";
    int pos = filename.find_last_of("/");
    file << filename.substr(pos+1) << ':' << std::to_string(line) << ". ";
    file << str << std::endl;
}

void Logger::errorMsg(std::string str, std::string filename, int line){//logLvl ERROR 1
    std::unique_lock<std::mutex> lock(m);
    file << currentDateTime() << " [ERROR]: ";
    int pos = filename.find_last_of("/");
    file << filename.substr(pos+1) << ':' << std::to_string(line) << ". ";
    file << str << std::endl;
}

std::string Logger::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


Logger::~Logger() {}
