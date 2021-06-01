#include <iostream>
#include "server/Config.h"
#include "controller/Controller.h"
#include "common/Logger.h"

#define MAX_ARGC 1
#define MIN_ARGC 0


#define LOG_PATH "../log.txt"
#define JSON_DEBUG_LVL 3

int main(int argc, char** argv){
    /*if (argc < MIN_ARGC || argc > MAX_ARGC){ // (argc != ARGC_NUM)
        return 0;
    }
    if (argc == MAX_ARGC){
        Game game(argv);
        game.run();
    } else {
        Game game;
        game.run();
    }*/
    Logger logger(LOG_PATH, JSON_DEBUG_LVL);
    Config config(argv[0], logger);
    logger.setLevel(config.getDebug());
    Controller cont(config, logger);
    cont.run();

    return 0;
}
