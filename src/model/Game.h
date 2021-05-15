#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entity.h"
#include "CollisionManager.h"
#include "../controller/Config.h"
#include "Entities/Character.h"
#include "../Message.h"
#include "../controller/Controller.h"

class Game {
private:
    Config& config;
    Character character;
    std::vector<Entity> vector;
    CollisionManager collisionManager;
    int tickCounter;
    int actLevel;

public:
    explicit Game(Config& config);

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

    Message get_status();

    void change_level();

    //void run();
};

#endif //GAME_H
