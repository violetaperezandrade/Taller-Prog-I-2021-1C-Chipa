#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../common/Entity.h"
#include "CollisionManager.h"
#include "../common/Config.h"
#include "entities/Character.h"
#include "../common/Logger.h"
#include "entities/Barrel.h"
#include "entities/Character.h"
#include "entities/Ember.h"
#include "entities/Fire.h"
#include "entities/Flame.h"
#include "entities/Monkey.h"
#include "entities/Platform.h"
#include "entities/Princess.h"
#include "entities/Stair.h"
#include "entities/Hammer.h"

class Game {
private:
    Config& config;
    Logger& logger;
    std::vector<Character> characters;
    std::vector<Entity> entities;
    CollisionManager collisionManager;
    int tickCounter;
    int currLevel;
    int amountCharacters;
    int finished;
    int playersWhoFinished;
    int charactersLeft;

    void updateCharacterStatus();
    bool moveCharacters();
    void attemptEmberSpawn();
    void attemptBarrelSpawn();
    void moveEntities();

public:
    Game(Config& config,Logger& logger, int amountCharacters);

    ~Game();

    void startMovingLeft(int i);

    void startMovingRight(int i);

    void startMovingUp(int i);

    void setInvincible(int i);

    void startMovingDown(int i);

    void startJumping(int i);

    void stopMovingLeft(int i);

    void stopMovingRight(int i);

    void stopMovingUp(int i);

    void stopMovingDown(int i);

    void stopJumping(int i);

    void disconnect(int i);

    void reconnect(int i);

    bool update();

    void spawnHammers();

    void setLevel1();

    void setLevel2();

    void lvl1SpawnEmber();

    void lvl2SpawnBarrel();

    void changeLevel();

    void spawnFlames();

    std::vector<Entity>& getEntities();

    std::vector<Character>& getCharacters();

    int isFinished();
};

#endif //GAME_H
