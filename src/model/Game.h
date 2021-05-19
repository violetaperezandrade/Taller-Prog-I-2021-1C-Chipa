#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entity.h"
#include "CollisionManager.h"
#include "../controller/Config.h"
#include "entities/Character.h"
#include "../Message.h"
#include "../controller/Logger.h"


class Game {
private:
    Config& config;
    Logger& logger;
    Character character;
    std::vector<Entity> vector;
    CollisionManager collisionManager;
    int tickCounter;
    int actLevel;

public:
    Game(Config& config,Logger& logger);
    ~Game();

    void startMovingLeft();

    void startMovingRight();

    void startMovingUp();

    void startMovingDown();

    void startJumping();

    void stopMovingLeft();

    void stopMovingRight();

    void stopMovingUp();

    void stopMovingDown();

    void stopJumping();

    void update();

    void setLevel1();

    void setLevel2();

    void lvl1SpawnEmber();

    void lvl2SpawnBarrel();

    Message getStatus();

    void changeLevel();

    void spawnFlames();

    //void run();
};

#endif //GAME_H
