#ifndef GAME_H
#define GAME_H

#include "EntityManager.h"

class Game {
private:
    Config config;
    EntityManager entityManager;

public:
    explicit Game(char** argv);
    Game();
    ~Game();

    void run();
};

#endif //GAME_H
