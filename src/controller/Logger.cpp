#include "Logger.h"
#include <time.h>

Logger::Logger(std::string path, int logLvl) :
    path(path),
    file(),
    logLvl(logLvl)

{
    file.open(path,std::ofstream::app);
    //if(!file.is_open()) hacemos algo
    file << "------------------------------------------------------------------------------------------\n";
}

void Logger::superDebugMsg(std::string str){//logLvl SUPER_DEBUG 4
    if(logLvl >= 4) {
        file << currentDateTime() << " [DEBUG]: " << str << std::endl;
    }
}

void Logger::debugMsg(std::string str){//logLvl DEBUG 3
    if(logLvl >= 3) {
        file << currentDateTime() << " [DEBUG]: " << str << std::endl;
    }
}

void Logger::infoMsg(std::string str){//logLvl INFO 2
    if (logLvl >= 2) {
        file << currentDateTime() << " [INFO]: " << str << std::endl;
    }
}

void Logger::errorMsg(std::string str){//logLvl ERROR 1
    file << currentDateTime() << " [ERROR]: " << str << std::endl;
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
