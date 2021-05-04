#include "Game.h"

#define DEFAULT_PATH "default_config.json"

Game::Game(Config& config) : config(config), character(), vector(),
                            collisionManager(character, vector){}

Game::Game() : config(DEFAULT_PATH) {}

Game::~Game() {}

void Game::make_character_jump() {
    character.set_jumping();

}

void Game::move_character_left() {
    if (!character.isMidair()){
        character.setSpeedX(-config.getCharacterSpeed());
    }
}

void Game::move_character_right() {
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

/*
void Game::run() {
    entityManager.
} */