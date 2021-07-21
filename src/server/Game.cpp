#include "Game.h"

#include <string>
#include <algorithm>
#include <random>
#include <chrono>

Game::Game(Config& config, Logger& logger, int amountCharacters) :
        config(config),
        logger(logger),
        entities(),
        collisionManager(characters, entities, logger, config),
        tickCounter(0),
        currLevel(1),
        amountCharacters(amountCharacters),
        finished(0),
        playersWhoFinished(0),
        charactersLeft(amountCharacters)
    {
    setLevel1();
}
Game::~Game() {}

void Game::startMovingLeft(int i){
    characters[i].startMovingLeft();
}

void Game::startMovingRight(int i){
    characters[i].startMovingRight();
}

void Game::startMovingUp(int i){
    characters[i].startMovingUp();
}

void Game::startMovingDown(int i){
    characters[i].startMovingDown();
}

void Game::startJumping(int i){
    characters[i].startJumping();
}

void Game::stopMovingLeft(int i){
    characters[i].stopMovingLeft();
}

void Game::stopMovingRight(int i){
    characters[i].stopMovingRight();
}

void Game::stopMovingUp(int i){
    characters[i].stopMovingUp();
}

void Game::stopMovingDown(int i){
    characters[i].stopMovingDown();
}

void Game::stopJumping(int i){
    characters[i].stopJumping();
}

void Game::disconnect(int i) {
    characters[i].disconnect();
}

void Game::reconnect(int i) {
    characters[i].reconnect();
}

void Game::updateCharacterStatus(){
    for(int i = 0; i < amountCharacters; i++){
        characters[i].updateStatus(config);
        std::string str("Updated character " + std::to_string(i) + "status:");
        str += characters[i].getState();
        logger.debugMsg(str, __FILE__, __LINE__);
        str.clear();
    }
}

bool Game::moveCharacters(){
    bool switchLevel;
    for (int i = 0; i < amountCharacters; i++) {
        if(characters[i].isSilenced()) continue; //si pasa este if no está muerto
        bool reachedPrincess = collisionManager.moveCharacter(i, playersWhoFinished);
        if(characters[i].isDead()){ //significa que me acabo de morir
            charactersLeft--;
        }

        if(charactersLeft == 0){
            finished = 1;
            return false;
        }
        switchLevel = (playersWhoFinished == charactersLeft);
        if (switchLevel){
            changeLevel();
            return switchLevel;
        } else if (reachedPrincess){
            characters[i].silence();
        }
    }
    return switchLevel;
}

void Game::attemptEmberSpawn(){
    if(currLevel == 1 && tickCounter % config.getEmbersLevel1() == 0){
        lvl1SpawnEmber();
    }
}

void Game::attemptBarrelSpawn(){
    if (currLevel == 2 && tickCounter % config.getBarrelsLevel2() == 0){
        lvl2SpawnBarrel();
    }
}

void Game::moveEntities() {
    bool removed = false;
    std::vector<Entity>::iterator it = entities.begin();
    while(it != entities.end()){
        switch(it->getType()){
            case 'P':
                collisionManager.movePlatform(*it);
                logger.superDebugMsg("moved platform", __FILE__, __LINE__);
                break;
            case 'E':
                removed = collisionManager.moveEmber(*it);
                logger.superDebugMsg("moved ember", __FILE__, __LINE__);
                break;
            case 'B':
                removed = collisionManager.moveBarrel(*it, charactersLeft);
                logger.superDebugMsg("moved barrel", __FILE__, __LINE__);
                break;
        }
        if(removed){
            it = entities.erase(it);
            logger.debugMsg("removed entity", __FILE__, __LINE__);
        }
        else{
            ++it;
        }
        removed = false;
    }
}

bool Game::update() {
    tickCounter++;
    updateCharacterStatus();
    bool switchLevel = moveCharacters();
    if (switchLevel){
        return true;
    }

    attemptEmberSpawn();
    attemptBarrelSpawn();

    moveEntities();
    collisionManager.updateCollisionStatus();
    return false;
}

void Game::lvl1SpawnEmber(){
    int spawns[4] = {168,312,456,600};

    int randSpawn = spawns[rand()%4];
    Ember ember(randSpawn, 560, 60, 40, 0, -12);
    this->entities.push_back(ember);

    logger.infoMsg("Spawned ember on X=" + std::to_string(randSpawn), __FILE__, __LINE__);
}

void Game::lvl2SpawnBarrel(){
    int spawns[4] = {168,250,510,600};

    int randSpawn = spawns[rand()%4];
    Barrel barrel(randSpawn, 100, 24, 24, 0, 4);
    this->entities.push_back(barrel);

    logger.infoMsg("Spawned barrel on X=" + std::to_string(randSpawn), __FILE__, __LINE__);
}

void Game::spawnFlames(){
    int spawnsX[21] = {80,90,100,235,245,255,375,385,395,515,525,535,545,675,685,50,60,70,670,680,690};
    int spawnsY[21] = {435,435,435,435,435,435,435,435,435,435,435,435,435,435,435,540,540,540,540,540,540};
    std::vector<int> positions;
    for (int i = 0; i< 21; i++){
        positions.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (positions.begin(), positions.end(), std::default_random_engine(seed));
    for(int i=0; i < config.getFlamesLevel1(); i++) {
        Flame flame(spawnsX[positions[i]], spawnsY[positions[i]], 60, 40, 0, 0);
        this->entities.push_back(flame);
    }
}

void Game::spawnHammers(){
    std::vector<int> positions;
    std::vector<int> spawnsX;
    std::vector<int> spawnsY;

    if(currLevel == 1){
        spawnsX.push_back(40);
        spawnsX.push_back(750);
        spawnsX.push_back(372);
        spawnsX.push_back(750);
        spawnsX.push_back(40);
        spawnsX.push_back(750);

        spawnsY.push_back(410);
        spawnsY.push_back(410);
        spawnsY.push_back(530);
        spawnsY.push_back(530);
        spawnsY.push_back(250);
        spawnsY.push_back(250);
    } else {
        spawnsX.push_back(750);
        spawnsX.push_back(40);
        spawnsX.push_back(750);
        spawnsX.push_back(40);
        spawnsX.push_back(750);
        spawnsX.push_back(350);

        spawnsY.push_back(520);
        spawnsY.push_back(510);
        spawnsY.push_back(460);
        spawnsY.push_back(400);
        spawnsY.push_back(320);
        spawnsY.push_back(300);
    }
    for (int i = 0; i < 6; i++){
        positions.push_back(i);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (positions.begin(), positions.end(), std::default_random_engine(seed));
    for(int i = 0 ; i < 3 ; i++) {
        Hammer hammer(spawnsX[positions[i]], spawnsY[positions[i]], 30, 30, 0, 0);
        this->entities.push_back(hammer);
    }

}

//800x600 grid
void Game::setLevel1(){
    logger.infoMsg("Set Level 1", __FILE__, __LINE__);
    //spawnFlames();
    Monkey monkey(84, 146, 148, 52, 0, 0);
    this->entities.push_back(monkey);

    Princess princess(312, 79, 57, 52, 0, 0);
    this->entities.push_back(princess);

    for(int i = 0; i < amountCharacters; i++){
        Character player(5 + (i*20),544,59, 36,0,0);
        characters.push_back(player);
    }

    spawnHammers();

    //level 1
    Platform platform_1_1(0, 580, 84, 20, 0, 0);
    this->entities.push_back(platform_1_1);
    Platform platform_1_2(84, 580, 84, 20, 0, 0);
    this->entities.push_back(platform_1_2);
    Fire fire(168, 560, 60, 60, 0, 0);
    this->entities.push_back(fire);
    Platform platform_1_3(228, 580, 84, 20, 0, 0);
    this->entities.push_back(platform_1_3);
    Fire fire_2(312, 560, 60, 60, 0, 0);
    this->entities.push_back(fire_2);
    Platform platform_1_4(372, 580, 84, 20, 0, 0);
    this->entities.push_back(platform_1_4);
    Fire fire_3(456, 560, 60, 60, 0, 0);
    this->entities.push_back(fire_3);
    Platform platform_1_5(516, 580, 84, 20, 0, 0);
    this->entities.push_back(platform_1_5);
    Fire fire_4(600, 560, 60, 60, 0, 0);
    this->entities.push_back(fire_4);
    Platform platform_1_6(660, 580, 84, 20, 0, 0);
    this->entities.push_back(platform_1_6);
    Platform platform_1_7(744, 580, 84, 20, 0, 0);
    this->entities.push_back(platform_1_7);

    //level 2
    Platform platform_2_1(0, 468, 84, 20, 0, 0);
    this->entities.push_back(platform_2_1);
    Platform platform_2_2(84, 468, 84, 20, 0, 0);
    this->entities.push_back(platform_2_2);
    Platform platform_2_3(228, 468, 84, 20, 0, 0);
    this->entities.push_back(platform_2_3);
    Platform platform_2_4(372, 468, 84, 20, 0, 0);
    this->entities.push_back(platform_2_4);
    Platform platform_2_5(516, 468, 84, 20, 0, 0);
    this->entities.push_back(platform_2_5);
    Platform platform_2_6(660, 468, 84, 20, 0, 0);
    this->entities.push_back(platform_2_6);
    Platform platform_2_7(744, 468, 84, 20, 0, 0);
    this->entities.push_back(platform_2_7);
    Stair stair_2_1(114, 468, 30, 112, 0, 0);
    this->entities.push_back(stair_2_1);

    //level 3
    Platform shortPlat_3_1(0, 375, 58, 20, 0, 0);
    this->entities.push_back(shortPlat_3_1);
    Platform shortPlat_3_2(742, 375, 58, 20, 0, 0);
    this->entities.push_back(shortPlat_3_2);
    Stair stair_3_1(770, 375, 30, 96, 0, 0);
    this->entities.push_back(stair_3_1);

    //moving plarforms
    //left
    Platform shortPlat_3_3(102, 402, 58, 20, -1, 0);
    this->entities.push_back(shortPlat_3_3);
    Platform shortPlat_3_4(309, 402, 58, 20, -1, 0);
    this->entities.push_back(shortPlat_3_4);
    Platform shortPlat_3_5(516, 402, 58, 20, -1, 0);
    this->entities.push_back(shortPlat_3_5);

    //right
    Platform shortPlat_3_6(224, 381, 58, 20, 1, 0);
    this->entities.push_back(shortPlat_3_6);
    Platform shortPlat_3_7(431, 381, 58, 20, 1, 0);
    this->entities.push_back(shortPlat_3_7);
    Platform shortPlat_3_8(638, 381, 58, 20, 1, 0);
    this->entities.push_back(shortPlat_3_8);

    //level 4
    Platform shortPlat_4_1(0, 281, 58, 20, 0, 0);
    this->entities.push_back(shortPlat_4_1);
    Platform shortPlat_4_2(742, 281, 58, 20, 0, 0);
    this->entities.push_back(shortPlat_4_2);
    Stair stair_4_1(0, 281, 30, 96, 0, 0);
    this->entities.push_back(stair_4_1);

    //moving plarforms
    //right
    Platform shortPlat_4_3(102, 306, 58, 20, 1, 0);
    this->entities.push_back(shortPlat_4_3);
    Platform shortPlat_4_4(309, 306, 58, 20, 1, 0);
    this->entities.push_back(shortPlat_4_4);
    Platform shortPlat_4_5(516, 306, 58, 20, 1, 0);
    this->entities.push_back(shortPlat_4_5);

    //left
    Platform shortPlat_4_6(224, 287, 58, 20, -1, 0);
    this->entities.push_back(shortPlat_4_6);
    Platform shortPlat_4_7(431, 287, 58, 20, -1, 0);
    this->entities.push_back(shortPlat_4_7);
    Platform shortPlat_4_8(638, 287, 58, 20, -1, 0);
    this->entities.push_back(shortPlat_4_8);

    //level 5
    Platform platform_5_1(85, 197, 84, 20, 0, 0);
    this->entities.push_back(platform_5_1);
    Platform platform_5_2(169, 197, 84, 20, 0, 0);
    this->entities.push_back(platform_5_2);
    Platform platform_5_3(253, 197, 84, 20, 0, 0);
    this->entities.push_back(platform_5_3);
    Platform platform_5_4(337, 197, 84, 20, 0, 0);
    this->entities.push_back(platform_5_4);
    Platform platform_5_5(421, 197, 84, 20, 0, 0);
    this->entities.push_back(platform_5_5);
    Platform platform_5_6(570, 197, 84, 20, 0, 0);
    this->entities.push_back(platform_5_6);
    Platform platform_5_7(726, 197, 84, 20, 0, 0);
    this->entities.push_back(platform_5_7);
    Stair stair_5_1(767, 206, 30, 84, 0, 0);
    this->entities.push_back(stair_5_1);
    Platform platform_5_8(313, 131, 84, 20, 0, 0);
    this->entities.push_back(platform_5_8);
    Platform platform_5_9(397, 131, 84, 20, 0, 0);
    this->entities.push_back(platform_5_9);
    Stair stair_6_1(225, 73, 32, 124, 0, 0);
    this->entities.push_back(stair_6_1);
    Stair stair_6_2(282, 73, 32, 124, 0, 0);
    this->entities.push_back(stair_6_2);
    Stair stair_6_3(451, 131, 32, 66, 0, 0);
    this->entities.push_back(stair_6_3);

}
void Game::setLevel2() {
    logger.infoMsg("Set Level 2", __FILE__, __LINE__);

    Monkey monkey(84, 146, 148, 52, 0, 0);
    this->entities.push_back(monkey);
    Princess princess(312, 79, 57, 52, 0, 0);
    this->entities.push_back(princess);

    for(int i = 0 ; i < amountCharacters ; i++){
        characters[i].setPosX(5 + (i*20));
        characters[i].setPosY(544);
    }

    spawnHammers();

    //level 1
    Platform platform_1_1(0, 580, 54, 20, 0, 0);
    this->entities.push_back(platform_1_1);
    Platform platform_1_2(54, 580, 54, 20, 0, 0);
    this->entities.push_back(platform_1_2);
    Platform platform_1_3(108, 580, 54, 20, 0, 0);
    this->entities.push_back(platform_1_3);
    Platform platform_1_4(162, 580, 54, 20, 0, 0);
    this->entities.push_back(platform_1_4);
    Platform platform_1_5(216, 580, 54, 20, 0, 0);
    this->entities.push_back(platform_1_5);
    Platform platform_1_6(270, 580, 54, 20, 0, 0);
    this->entities.push_back(platform_1_6);
    Platform platform_1_7(324, 580, 54, 20, 0, 0);
    this->entities.push_back(platform_1_7);
    Platform platform_1_8(378, 578, 54, 20, 0, 0);
    this->entities.push_back(platform_1_8);
    Platform platform_1_9(432, 576, 54, 20, 0, 0);
    this->entities.push_back(platform_1_9);
    Platform platform_1_10(486, 574, 54, 20, 0, 0);
    this->entities.push_back(platform_1_10);
    Platform platform_1_11(540, 572, 54, 20, 0, 0);
    this->entities.push_back(platform_1_11);
    Platform platform_1_12(594, 570, 54, 20, 0, 0);
    this->entities.push_back(platform_1_12);
    Platform platform_1_13(648, 568, 54, 20, 0, 0);
    this->entities.push_back(platform_1_13);
    Platform platform_1_14(702, 566, 54, 20, 0, 0);
    this->entities.push_back(platform_1_14);
    Platform platform_1_15(756, 566, 54, 20, 0, 0);
    this->entities.push_back(platform_1_15);

    Stair brokenStair_1_1(285, 497, 30, 84, 0, 0);
    this->entities.push_back(brokenStair_1_1);
    Stair stair_1_2(654, 513, 30, 56, 0, 0);
    this->entities.push_back(stair_1_2);

    //level 2
    Platform platform_2_1(0, 486, 54, 20, 0, 0);
    this->entities.push_back(platform_2_1);
    Platform platform_2_2(54, 488, 54, 20, 0, 0);
    this->entities.push_back(platform_2_2);
    Platform platform_2_3(108, 490, 54, 20, 0, 0);
    this->entities.push_back(platform_2_3);
    Platform platform_2_4(162, 492, 54, 20, 0, 0);
    this->entities.push_back(platform_2_4);
    Platform platform_2_5(216, 494, 54, 20, 0, 0);
    this->entities.push_back(platform_2_5);
    Platform platform_2_6(270, 496, 54, 20, 0, 0);
    this->entities.push_back(platform_2_6);
    Platform platform_2_7(324, 498, 54, 20, 0, 0);
    this->entities.push_back(platform_2_7);
    Platform platform_2_8(378, 500, 54, 20, 0, 0);
    this->entities.push_back(platform_2_8);
    Platform platform_2_9(432, 502, 54, 20, 0, 0);
    this->entities.push_back(platform_2_9);
    Platform platform_2_10(486, 504, 54, 20, 0, 0);
    this->entities.push_back(platform_2_10);
    Platform platform_2_11(540, 506, 54, 20, 0, 0);
    this->entities.push_back(platform_2_11);
    Platform platform_2_12(594, 508, 54, 20, 0, 0);
    this->entities.push_back(platform_2_12);
    Platform platform_2_13(648, 510, 54, 20, 0, 0);
    this->entities.push_back(platform_2_13);

    Stair stair_2_1(113, 435, 30, 56, 0, 0);
    this->entities.push_back(stair_2_1);
    Stair stair_2_2(341, 426, 30, 75, 0, 0);
    this->entities.push_back(stair_2_2);

    //level 3
    Platform platform_3_1(54, 437, 54, 20, 0, 0);
    this->entities.push_back(platform_3_1);
    Platform platform_3_2(108, 435, 54, 20, 0, 0);
    this->entities.push_back(platform_3_2);
    Platform platform_3_3(162, 433, 54, 20, 0, 0);
    this->entities.push_back(platform_3_3);
    Platform platform_3_4(216, 431, 54, 20, 0, 0);
    this->entities.push_back(platform_3_4);
    Platform platform_3_5(270, 429, 54, 20, 0, 0);
    this->entities.push_back(platform_3_5);
    Platform platform_3_6(324, 427, 54, 20, 0, 0);
    this->entities.push_back(platform_3_6);
    Platform platform_3_7(378, 425, 54, 20, 0, 0);
    this->entities.push_back(platform_3_7);
    Platform platform_3_8(432, 423, 54, 20, 0, 0);
    this->entities.push_back(platform_3_8);
    Platform platform_3_9(486, 421, 54, 20, 0, 0);
    this->entities.push_back(platform_3_9);
    Platform platform_3_10(540, 419, 54, 20, 0, 0);
    this->entities.push_back(platform_3_10);
    Platform platform_3_11(594, 417, 54, 20, 0, 0);
    this->entities.push_back(platform_3_11);
    Platform platform_3_12(648, 415, 54, 20, 0, 0);
    this->entities.push_back(platform_3_12);
    Platform platform_3_13(702, 413, 54, 20, 0, 0);
    this->entities.push_back(platform_3_13);
    Platform platform_3_14(756, 413, 54, 20, 0, 0);
    this->entities.push_back(platform_3_14);

    Stair brokenStair_3_1(216, 340, 30, 94, 0, 0);
    this->entities.push_back(brokenStair_3_1);
    Stair stair_3_2(398, 348, 30, 76, 0, 0);
    this->entities.push_back(stair_3_2);
    Stair stair_3_3(654, 354, 30, 64, 0, 0);
    this->entities.push_back(stair_3_3);

    //level 4
    Platform platform_4_1(0, 332, 54, 20, 0, 0);
    this->entities.push_back(platform_4_1);
    Platform platform_4_2(54, 334, 54, 20, 0, 0);
    this->entities.push_back(platform_4_2);
    Platform platform_4_3(108, 336, 54, 20, 0, 0);
    this->entities.push_back(platform_4_3);
    Platform platform_4_4(162, 338, 54, 20, 0, 0);
    this->entities.push_back(platform_4_4);
    Platform platform_4_5(216, 340, 54, 20, 0, 0);
    this->entities.push_back(platform_4_5);
    Platform platform_4_6(270, 342, 54, 20, 0, 0);
    this->entities.push_back(platform_4_6);
    Platform platform_4_7(324, 344, 54, 20, 0, 0);
    this->entities.push_back(platform_4_7);
    Platform platform_4_8(378, 346, 54, 20, 0, 0);
    this->entities.push_back(platform_4_8);
    Platform platform_4_9(432, 348, 54, 20, 0, 0);
    this->entities.push_back(platform_4_9);
    Platform platform_4_10(486, 350, 54, 20, 0, 0);
    this->entities.push_back(platform_4_10);
    Platform platform_4_11(540, 352, 54, 20, 0, 0);
    this->entities.push_back(platform_4_11);
    Platform platform_4_12(594, 354, 54, 20, 0, 0);
    this->entities.push_back(platform_4_12);
    Platform platform_4_13(648, 356, 54, 20, 0, 0);
    this->entities.push_back(platform_4_13);

    Stair stair_4_1(113, 281, 30, 56, 0, 0);
    this->entities.push_back(stair_4_1);
    Stair stair_4_2(255, 276, 30, 67, 0, 0);
    this->entities.push_back(stair_4_2);
    Stair brokenStair_4_3(598, 260, 33, 97, 0, 0);
    this->entities.push_back(brokenStair_4_3);

    //level 5
    Platform platform_5_1(54, 282, 54, 20, 0, 0);
    this->entities.push_back(platform_5_1);
    Platform platform_5_2(108, 280, 54, 20, 0, 0);
    this->entities.push_back(platform_5_2);
    Platform platform_5_3(162, 278, 54, 20, 0, 0);
    this->entities.push_back(platform_5_3);
    Platform platform_5_4(216, 276, 54, 20, 0, 0);
    this->entities.push_back(platform_5_4);
    Platform platform_5_5(270, 274, 54, 20, 0, 0);
    this->entities.push_back(platform_5_5);
    Platform platform_5_6(324, 272, 54, 20, 0, 0);
    this->entities.push_back(platform_5_6);
    Platform platform_5_7(378, 270, 54, 20, 0, 0);
    this->entities.push_back(platform_5_7);
    Platform platform_5_8(432, 268, 54, 20, 0, 0);
    this->entities.push_back(platform_5_8);
    Platform platform_5_9(486, 266, 54, 20, 0, 0);
    this->entities.push_back(platform_5_9);
    Platform platform_5_10(540, 264, 54, 20, 0, 0);
    this->entities.push_back(platform_5_10);
    Platform platform_5_11(594, 262, 54, 20, 0, 0);
    this->entities.push_back(platform_5_11);
    Platform platform_5_12(648, 260, 54, 20, 0, 0);
    this->entities.push_back(platform_5_12);
    Platform platform_5_13(702, 258, 54, 20, 0, 0);
    this->entities.push_back(platform_5_13);
    Platform platform_5_14(756, 258, 54, 20, 0, 0);
    this->entities.push_back(platform_5_14);

    Stair brokenStair_5_1(313, 195, 30, 79, 0, 0);
    this->entities.push_back(brokenStair_5_1);
    Stair stair_5_2(654, 203, 30, 56, 0, 0);
    this->entities.push_back(stair_5_2);

    //level 6
    Platform platform_6_1(0, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_1);
    Platform platform_6_2(54, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_2);
    Platform platform_6_3(108, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_3);
    Platform platform_6_4(162, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_4);
    Platform platform_6_5(216, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_5);
    Platform platform_6_6(270, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_6);
    Platform platform_6_7(324, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_7);
    Platform platform_6_8(378, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_8);
    Platform platform_6_9(432, 196, 54, 20, 0, 0);
    this->entities.push_back(platform_6_9);
    Platform platform_6_10(486, 198, 54, 20, 0, 0);
    this->entities.push_back(platform_6_10);
    Platform platform_6_11(540, 200, 54, 20, 0, 0);
    this->entities.push_back(platform_6_11);
    Platform platform_6_12(594, 202, 54, 20, 0, 0);
    this->entities.push_back(platform_6_12);
    Platform platform_6_13(648, 204, 54, 20, 0, 0);
    this->entities.push_back(platform_6_13);

    Stair stair_6_1(225, 73, 32, 124, 0, 0);
    this->entities.push_back(stair_6_1);
    Stair stair_6_2(282, 73, 32, 124, 0, 0);
    this->entities.push_back(stair_6_2);
    Stair stair_4_3(454, 131, 33, 66, 0, 0);
    this->entities.push_back(stair_4_3);

    //level 7
    Platform platform_7_1(315, 131, 54, 20, 0, 0);
    this->entities.push_back(platform_7_1);
    Platform platform_7_2(369, 131, 54, 20, 0, 0);
    this->entities.push_back(platform_7_2);
    Platform platform_7_3(423, 131, 54, 20, 0, 0);
    this->entities.push_back(platform_7_3);
}

std::vector<Entity>& Game::getEntities(){
    return entities;
}

std::vector<Character>& Game::getCharacters(){
    return characters;
}

int Game::isFinished() {
    return finished;
}

void Game::setInvincible(int i) {
    characters[i].setInvincible();
}

void Game::changeLevel(){
    if(currLevel == 1){
        for (int i = 0; i < amountCharacters; i++) {
            if(!characters[i].isDead()) {
                characters[i].unsilence();
            }
        }
        playersWhoFinished = 0;
        this->entities.clear();
        currLevel = 2;
        setLevel2();
    } else {
        finished = 2;
    }
}
