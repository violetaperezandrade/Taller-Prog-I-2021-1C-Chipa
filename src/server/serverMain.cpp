#include "Server.h"
#include <cstdlib> //atoi
#include "../common/Logger.h"
#include "../common/Config.h"

int main(int argc, char** argv){
    char ip[10] = "127.0.0.1";
    Logger logger(argv[4]);
    Config config(argv[3], logger);
    logger.setLevel(config.getDebug());
    Server sv(ip, argv[1],atoi(config.getPlayerAmount()), config, logger);
    sv.run();
    return 0;
}

