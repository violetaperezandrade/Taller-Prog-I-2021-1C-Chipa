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

/*
void Game::run() {
    entityManager.
} */
