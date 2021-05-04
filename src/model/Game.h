#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entity.h"
#include "CollisionManager.h"
#include "../controller/Config.h"
#include "Entities/Character.h"

class Game {
private:
    Config& config;
    Character character;
    std::vector<Entity> vector;
    CollisionManager collisionManager;

public:
    explicit Game(Config& config);

    ~Game();

    void moveCharacterLeft();

    void moveCharacterRight();

    void makeCharacterJump();

    void moveCharacterUp();

    void moveCharacterDown();

    void update();

    //void run();
};

#endif //GAME_H
