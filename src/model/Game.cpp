#include "Game.h"

Game::Game(Config& config) :
    config(config),
    character(0,0,59, 36,0,0),
    vector(),
    collisionManager(character, vector)
{}

Game::~Game() {}

void Game::startMovingLeft(){
    character.startMovingLeft();
}

void Game::startMovingRight(){
    character.startMovingRight();
}

void Game::startMovingUp(){
    character.startMovingUp();
}

void Game::startMovingDown(){
    character.startMovingDown();
}

void Game::startJumping(){
    character.startJumping();
}

void Game::stopMovingLeft(){
    character.stopMovingLeft();
}

void Game::stopMovingRight(){
    character.stopMovingRight();
}

void Game::stopMovingUp(){
    character.stopMovingUp();
}

void Game::stopMovingDown(){
    character.stopMovingDown();
}

void Game::stopJumping(){
    character.stopJumping();
}

void Game::makeCharacterJump() {
    character.setJumping();
}

void Game::moveCharacterLeft() {
    if (!character.isMidair()){
        character.setSpeedX(config.getCharacterSpeed() * -1);
    }
}

void Game::moveCharacterRight() {
    if (!character.isMidair()){
        character.setSpeedX(config.getCharacterSpeed());
    }
}

void Game::update() { //nombre
    collisionManager.move(character);

    for (int i = 0; i < vector.size(); i++){
        if (vector[i].canMove()){
            collisionManager.move(vector[i]);
        }
    }
}

void Game::moveCharacterUp(){
    /* if(character.isGrounded() && colisionManagerStairCheck){
     *      character.climb();
     *      character.setSpeedY(config.getClimbingSpeed); //Go up
     * }
     */
}

void Game::moveCharacterDown(){
    /* if(character.isGrounded() && colisionMangerStairCheck){
     *      character.climb();
     *      character.setSpeedY(config.getClimbingSpeed * -1); //Go down
     * }
     */
}

Message Game::get_status() {
    Message message;
    message.add(character);
    for (int i = 0; i < vector.size(); i++){
        message.add(vector[i]);
    }
    return std::move(message);
}

//800x600 grid

void Game::setLevel1(){

    Monkey monkey(84, 146, 148, 52, 0, 0);
    this->vector.push_back(monkey);

    Princess princess(312, 79, 57, 52, 0, 0)
    this->vector.push_back(princess);

    character.setPosX(10);
    character.setPosY(544);

    //level 1
    Platform platform_1_1(0, 580, 84, 20, 0, 0);
    this->vector.push_back(platform_1_1);
    Platform platform_1_2(84, 580, 84, 20, 0, 0);
    this->vector.push_back(platform_1_2);
    Fire fire(168, 560, 60, 40, 0, 0);
    this->vector.push_back(fire);
    Platform platform_1_3(228, 580, 84, 20, 0, 0);
    this->vector.push_back(platform_1_3);
    Fire fire_2(312, 560, 60, 40, 0, 0);
    this->vector.push_back(fire_2);
    Platform platform_1_4(372, 580, 84, 20, 0, 0)
    this->vector.push_back(platform_1_4);
    Fire fire_3(456, 560, 60, 40, 0, 0);
    this->vector.push_back(fire_3);
    Platform platform_1_5(516, 580, 84, 20, 0, 0);
    this->vector.push_back(platform_1_5);
    Fire fire_4(600, 560, 60, 40, 0, 0);
    this->vector.push_back(fire_4);
    Platform platform_1_6(660, 580, 84, 20, 0, 0);
    this->vector.push_back(platform_1_6);
    Platform platform_1_7(744, 580, 84, 20, 0, 0);
    this->vector.push_back(platform_1_6);

    //level 2
    Platform platform_2_1(0, 468, 84, 20, 0, 0);
    this->vector.push_back(platform_2_1);
    Platform platform_2_2(84, 468, 84, 20, 0, 0);
    this->vector.push_back(platform_2_2);
    Platform platform_2_3(228, 468, 84, 20, 0, 0);
    this->vector.push_back(platform_2_3);
    Platform platform_2_4(372, 468, 84, 20, 0, 0);
    this->vector.push_back(platform_2_4);
    Platform platform_2_5(516, 468, 84, 20, 0, 0);
    this->vector.push_back(platform_2_5);
    Platform platform_2_6(660, 468, 84, 20, 0, 0)
    this->vector.push_back(platform_2_6);
    Platform platform_2_7(744, 468, 84, 20, 0, 0)
    this->vector.push_back(platform_2_7);
    Stair stair_2_1(114, 468, 30, 112, 0, 0);
    this->vector.push_back(stair_2_1);
    Stair stair_2_2(670, 468, 30, 112, 0, 0);
    this->vector.push_back(stair_2_2);

    //level 3
    Platform shortPlat_3_1(0, 375, 58, 20, 0, 0);
    this->vector.push_back(shortPlat_3_1);
    Platform shortPlat_3_2(742, 375, 58, 20, 0, 0);
    this->vector.push_back(shortPlat_3_2);
    Stair stair_3_1(770, 375, 30, 96, 0, 0);
    this->vector.push_back(stair_3_1);

    //moving plarforms
    //right
    Platform shortPlat_3_3(102, 402, 58, 20, 1, 0);
    this->vector.push_back(shortPlat_3_3);
    Platform shortPlat_3_4(309, 402, 58, 20, 1, 0);
    this->vector.push_back(shortPlat_3_4);
    Platform shortPlat_3_5(516, 402, 58, 20, 1, 0);
    this->vector.push_back(shortPlat_3_5);

    //left
    Platform shortPlat_3_6(224, 381, 58, 20, -1, 0);
    this->vector.push_back(shortPlat_3_6);
    Platform shortPlat_3_7(431, 381, 58, 20, -1, 0);
    this->vector.push_back(shortPlat_3_7);
    Platform shortPlat_3_8(638, 381, 58, 20, -1, 0);
    this->vector.push_back(shortPlat_3_8);

    //level 4
    Platform shortPlat_4_1(0, 281, 58, 20, 0, 0);
    this->vector.push_back(shortPlat_4_1);
    Platform shortPlat_4_2(742, 281, 58, 20, 0, 0);
    this->vector.push_back(shortPlat_4_2);
    Stair stair_4_1(0, 281, 30, 96, 0, 0);
    this->vector.push_back(stair_4_1);

    //moving plarforms
    //left
    Platform shortPlat_4_3(102, 306, 58, 20, -1, 0);
    this->vector.push_back(shortPlat_4_3);
    Platform shortPlat_4_4(309, 306, 58, 20, -1, 0);
    this->vector.push_back(shortPlat_4_4);
    Platform shortPlat_4_5(516, 306, 58, 20, -1, 0);
    this->vector.push_back(shortPlat_4_5);

    //right
    Platform shortPlat_4_6(224, 287, 58, 20, 1, 0);
    this->vector.push_back(shortPlat_4_6);
    Platform shortPlat_4_7(431, 287, 58, 20, 1, 0);
    this->vector.push_back(shortPlat_4_7);
    Platform shortPlat_4_8(638, 287, 58, 20, 1, 0)
    this->vector.push_back(shortPlat_4_8);

    //level 5
    Platform platform_5_1(85, 197, 84, 20, 0, 0);
    this->vector.push_back(platform_5_1);
    Platform platform_5_2(169, 197, 84, 20, 0, 0);
    this->vector.push_back(platform_5_2);
    Platform platform_5_3(253, 197, 84, 20, 0, 0);
    this->vector.push_back(platform_5_3);
    Platform platform_5_4(337, 197, 84, 20, 0, 0);
    this->vector.push_back(platform_5_4);
    Platform platform_5_5(421, 197, 84, 20, 0, 0);
    this->vector.push_back(platform_5_5);
    Platform platform_5_6(570, 197, 84, 20, 0, 0);
    this->vector.push_back(platform_5_6);
    Platform platform_5_7(726, 197, 84, 20, 0, 0);
    this->vector.push_back(platform_5_7);
    Stair stair_4_1(767, 206, 30, 84, 0, 0);
    this->vector.push_back(stair_4_1);
    Platform platform_5_8(313, 131, 84, 20, 0, 0);
    this->vector.push_back(platform_5_8);
    Platform platform_5_9(397, 131, 84, 20, 0, 0);
    this->vector.push_back(platform_5_9);
}
void Game::setLevel2() {
    this->vector.push_back(Monkey monkey(84, 146, 148, 52, 0, 0));
    this->vector.push_back(Princess princess(312, 79, 57, 52, 0, 0));
    character.setPosX(10);
    character.setPosY(544);

    //level 1
    Platform platform_1_1(0, 580, 54, 20, 0, 0);
    this->vector.push_back(platform_1_1);
    Platform platform_1_2(54, 580, 54, 20, 0, 0);
    this->vector.push_back(platform_1_2);
    Platform platform_1_3(108, 580, 54, 20, 0, 0);
    this->vector.push_back(platform_1_3);
    Platform platform_1_4(162, 580, 54, 20, 0, 0);
    this->vector.push_back(platform_1_4);
    Platform platform_1_5(216, 580, 54, 20, 0, 0);
    this->vector.push_back(platform_1_5);
    Platform platform_1_6(270, 580, 54, 20, 0, 0);
    this->vector.push_back(platform_1_6);
    Platform platform_1_7(324, 580, 54, 20, 0, 0);
    this->vector.push_back(platform_1_7);
    Platform platform_1_8(378, 578, 54, 20, 0, 0);
    this->vector.push_back(platform_1_8);
    Platform platform_1_9(432, 576, 54, 20, 0, 0);
    this->vector.push_back(platform_1_9);
    Platform platform_1_10(486, 574, 54, 20, 0, 0);
    this->vector.push_back(platform_1_10);
    Platform platform_1_11(540, 572, 54, 20, 0, 0);
    this->vector.push_back(platform_1_11);
    Platform platform_1_12(594, 570, 54, 20, 0, 0);
    this->vector.push_back(platform_1_12);
    Platform platform_1_13(648, 568, 54, 20, 0, 0);
    this->vector.push_back(platform_1_13);
    Platform platform_1_14(702, 566, 54, 20, 0, 0);
    this->vector.push_back(platform_1_14);

    Stair brokenStair_1_1(285, 497, 30, 84, 0, 0);
    this->vector.push_back(brokenStair_1_1);
    Stair stair_1_2(654, 513, 30, 56, 0, 0);
    this->vector.push_back(stair_1_2);

    //level 2
    Platform platform_2_1(0, 486, 54, 20, 0, 0);
    this->vector.push_back(platform_2_1);
    Platform platform_2_2(54, 488, 54, 20, 0, 0);
    this->vector.push_back(platform_2_2);
    Platform platform_2_3(108, 490, 54, 20, 0, 0);
    this->vector.push_back(platform_2_3);
    Platform platform_2_4(162, 492, 54, 20, 0, 0);
    this->vector.push_back(platform_2_4);
    Platform platform_2_5(216, 494, 54, 20, 0, 0);
    this->vector.push_back(platform_2_5);
    Platform platform_2_6(270, 496, 54, 20, 0, 0);
    this->vector.push_back(platform_2_6);
    Platform platform_2_7(324, 498, 54, 20, 0, 0);
    this->vector.push_back(platform_2_7);
    Platform platform_2_8(378, 500, 54, 20, 0, 0);
    this->vector.push_back(platform_2_8);
    Platform platform_2_9(432, 502, 54, 20, 0, 0);
    this->vector.push_back(platform_2_9);
    Platform platform_2_10(486, 504, 54, 20, 0, 0);
    this->vector.push_back(platform_2_10);
    Platform platform_2_11(540, 506, 54, 20, 0, 0);
    this->vector.push_back(platform_2_11);
    Platform platform_2_12(594, 508, 54, 20, 0, 0);
    this->vector.push_back(platform_2_12);
    Platform platform_2_13(648, 510, 54, 20, 0, 0);
    this->vector.push_back(platform_2_13);

    Stair stair_2_1(113, 435, 30, 56, 0, 0)
    this->vector.push_back(stair_2_1);
    Stair stair_2_2(341, 426, 30, 75, 0, 0)
    this->vector.push_back(stair_2_2);

    //level 3
    Platform platform_3_1(54, 437, 54, 20, 0, 0);
    this->vector.push_back(platform_3_1);
    Platform platform_3_2(108, 435, 54, 20, 0, 0);
    this->vector.push_back(platform_3_2);
    Platform platform_3_3(162, 433, 54, 20, 0, 0);
    this->vector.push_back(platform_3_3);
    Platform platform_3_4(216, 431, 54, 20, 0, 0);
    this->vector.push_back(platform_3_4);
    Platform platform_3_5(270, 429, 54, 20, 0, 0);
    this->vector.push_back(platform_3_5);
    Platform platform_3_6(324, 427, 54, 20, 0, 0);
    this->vector.push_back(platform_3_6);
    Platform platform_3_7(378, 425, 54, 20, 0, 0);
    this->vector.push_back(platform_3_7);
    Platform platform_3_8(432, 423, 54, 20, 0, 0);
    this->vector.push_back(platform_3_8);
    Platform platform_3_9(486, 421, 54, 20, 0, 0);
    this->vector.push_back(platform_3_9);
    Platform platform_3_10(540, 419, 54, 20, 0, 0);
    this->vector.push_back(platform_3_10);
    Platform platform_3_11(594, 417, 54, 20, 0, 0);
    this->vector.push_back(platform_3_11);
    Platform platform_3_12(648, 415, 54, 20, 0, 0);
    this->vector.push_back(platform_3_12);
    Platform platform_3_13(702, 413, 54, 20, 0, 0);
    this->vector.push_back(platform_3_13);

    Stair brokenStair_3_1(216, 340, 30, 84, 0, 0);
    this->vector.push_back(brokenStair_3_1);
    Stair stair_3_2(398, 348, 30, 76, 0, 0);
    this->vector.push_back(stair_3_2);
    Stair stair_3_3(654, 388, 30, 27, 0, 0);
    this->vector.push_back(stair_3_3);

    //level 4
    Platform platform_4_1(0, 332, 54, 20, 0, 0);
    this->vector.push_back(platform_4_1);
    Platform platform_4_2(54, 334, 54, 20, 0, 0);
    this->vector.push_back(platform_4_2);
    Platform platform_4_3(108, 336, 54, 20, 0, 0);
    this->vector.push_back(platform_4_3);
    Platform platform_4_4(162, 338, 54, 20, 0, 0);
    this->vector.push_back(platform_4_4);
    Platform platform_4_5(216, 340, 54, 20, 0, 0);
    this->vector.push_back(platform_4_5);
    Platform platform_4_6(270, 342, 54, 20, 0, 0);
    this->vector.push_back(platform_4_6);
    Platform platform_4_7(324, 344, 54, 20, 0, 0);
    this->vector.push_back(platform_4_7);
    Platform platform_4_8(378, 346, 54, 20, 0, 0);
    this->vector.push_back(platform_4_8);
    Platform platform_4_9(432, 348, 54, 20, 0, 0);
    this->vector.push_back(platform_4_9);
    Platform platform_4_10(486, 350, 54, 20, 0, 0);
    this->vector.push_back(platform_4_10);
    Platform platform_4_11(540, 352, 54, 20, 0, 0);
    this->vector.push_back(platform_4_11);
    Platform platform_4_12(594, 354, 54, 20, 0, 0);
    this->vector.push_back(platform_4_12);
    Platform platform_4_13(648, 356, 54, 20, 0, 0);
    this->vector.push_back(platform_4_13);

    Stair stair_4_1(113, 281, 30, 56, 0, 0);
    this->vector.push_back(stair_4_1);
    Stair stair_4_2(255, 276, 30, 67, 0, 0);
    this->vector.push_back(stair_4_2);
    Stair brokenStair_4_3(598, 260, 33, 97, 0, 0);
    this->vector.push_back(brokenStair_4_3);

    //level 5
    Platform platform_5_1(54, 282, 54, 20, 0, 0);
    this->vector.push_back(platform_5_1);
    Platform platform_5_2(108, 280, 54, 20, 0, 0);
    this->vector.push_back(platform_5_2);
    Platform platform_5_3(162, 278, 54, 20, 0, 0);
    this->vector.push_back(platform_5_3);
    Platform platform_5_4(216, 276, 54, 20, 0, 0);
    this->vector.push_back(platform_5_4);
    Platform platform_5_5(270, 274, 54, 20, 0, 0);
    this->vector.push_back(platform_5_5);
    Platform platform_5_6(324, 272, 54, 20, 0, 0);
    this->vector.push_back(platform_5_6);
    Platform platform_5_7(378, 270, 54, 20, 0, 0);
    this->vector.push_back(platform_5_7);
    Platform platform_5_8(432, 268, 54, 20, 0, 0);
    this->vector.push_back(platform_5_8);
    Platform platform_5_9(486, 266, 54, 20, 0, 0);
    this->vector.push_back(platform_5_9);
    Platform platform_5_10(540, 264, 54, 20, 0, 0);
    this->vector.push_back(platform_5_10);
    Platform platform_5_11(594, 262, 54, 20, 0, 0);
    this->vector.push_back(platform_5_11);
    Platform platform_5_12(648, 260, 54, 20, 0, 0);
    this->vector.push_back(platform_5_12);
    Platform platform_5_13(702, 258, 54, 20, 0, 0);
    this->vector.push_back(platform_5_13);

    Stair brokenStair_5_1(313, 195, 30, 79, 0, 0)
    this->vector.push_back(brokenStair_5_1);
    Stair stair_5_2(654, 203, 30, 56, 0, 0);
    this->vector.push_back(stair_5_2);

    //level 6
    Platform platform_6_1(0, 196, 54, 20, 0, 0)
    this->vector.push_back(platform_6_1);
    Platform platform_6_2(54, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_2);
    Platform platform_6_3(108, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_3);
    Platform platform_6_4(162, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_4);
    Platform platform_6_5(216, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_5);
    Platform platform_6_6(270, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_6);
    Platform platform_6_7(324, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_7);
    Platform platform_6_8(378, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_8);
    Platform platform_6_9(432, 196, 54, 20, 0, 0);
    this->vector.push_back(platform_6_9);
    Platform platform_6_10(486, 198, 54, 20, 0, 0);
    this->vector.push_back(platform_6_10);
    Platform platform_6_11(540, 200, 54, 20, 0, 0);
    this->vector.push_back(platform_6_11);
    Platform platform_6_12(594, 202, 54, 20, 0, 0);
    this->vector.push_back(platform_6_12);
    Platform platform_6_13(648, 204, 54, 20, 0, 0);
    this->vector.push_back(platform_6_13);

    Stair stair_4_1(225, 73, 32, 124, 0, 0);
    this->vector.push_back(stair_4_1);
    Stair stair_4_2(282, 73, 32, 124, 0, 0);
    this->vector.push_back(stair_4_2);
    Stair stair_4_3(454, 131, 33, 66, 0, 0);
    this->vector.push_back(stair_4_3);

    //level 7
    Platform platform_7_1(315, 131, 54, 20, 0, 0);
    this->vector.push_back(platform_7_1);
    Platform platform_7_2(369, 131, 54, 20, 0, 0);
    this->vector.push_back(platform_7_2);
    Platform platform_7_3(423, 131, 54, 20, 0, 0);
    this->vector.push_back(platform_7_3);
}


void Game::changeLevel(){
    this->vector.clear();
    setLevel2();
}
/*
void Game::run() {
    entityManager.
} */
