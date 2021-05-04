#include "Game.h"

Game::Game(Config& config) :
    config(config),
    character(0,0,0,0,0,0),
    vector(),
    collisionManager(character, vector)
{}

Game::~Game() {}

void Game::makeCharacterJump() {
    character.setJumping();

}

void Game::moveCharacterLeft() {
    if (!character.isMidair()){
        character.setSpeedX(-config.getCharacterSpeed());
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
    /* if(character.isGrounded() && colisionMangerStairCheck){
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

/*
void Game::run() {
    entityManager.
} */
