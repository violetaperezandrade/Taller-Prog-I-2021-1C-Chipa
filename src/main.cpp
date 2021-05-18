#include <iostream>
#include "controller/Config.h"
#include "controller/Controller.h"
#include "controller/Logger.h"

#define MAX_ARGC 1
#define MIN_ARGC 0


#define PATH "../log.txt"
#define DEBUG 3

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
    Logger logger(PATH, DEBUG);
    //aca creariamos el json
    Controller cont(logger);
    cont.run();

    return 0;
}
