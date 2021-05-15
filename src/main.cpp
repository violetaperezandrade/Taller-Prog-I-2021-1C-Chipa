#include <iostream>
#include "model/Game.h"

#define MAX_ARGC 1
#define MIN_ARGC 0

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

    Controller cont;
    cont.run();

    return 0;
}
