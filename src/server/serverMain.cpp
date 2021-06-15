#include "Server.h"
#include <cstdlib> //atoi
#include "../common/Logger.h"
#include "../common/Config.h"

int main(int argc, char** argv){
    Logger logger(argv[2]);
    Config config(argv[0], logger);
    logger.setLevel(config.getDebug());
    Server sv(argv[0],atoi(argv[1]), config, logger);
    sv.run();
    return 0;
}

