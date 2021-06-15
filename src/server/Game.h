#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entity.h"
#include "CollisionManager.h"
#include "../common/Config.h"
#include "entities/Character.h"
#include "../common/Message.h"
#include "../common/Logger.h"


class Game {
private:
    Config& config;
    Logger& logger;
    std::vector<Character> players;
    std::vector<Entity> entities;
    CollisionManager collisionManager;
    int tickCounter;
    int actLevel;
    int amountPlayers;
    bool finished;

public:
    Game(Config& config,Logger& logger, int amountPlayers);

    ~Game();

    void startMovingLeft(int i);

    void startMovingRight(int i);

    void startMovingUp(int i);

    void startMovingDown(int i);

    void startJumping(int i);

    void stopMovingLeft(int i);

    void stopMovingRight(int i);

    void stopMovingUp(int i);

    void stopMovingDown(int i);

    void stopJumping(int i);

    void update();

    void setLevel1();

    void setLevel2();

    void lvl1SpawnEmber();

    void lvl2SpawnBarrel();

    Message getStatus();

    void changeLevel();

    void spawnFlames();

    const std::vector<Entity>& getEntities();

    const std::vector<Character>& getPlayers();

    bool isFinished();
};

#endif //GAME_H
