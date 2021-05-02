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
    character.set_left(); //Tiene que fijarse que no este en el aire
    /*
    int map_width = config.get_map_width();
    int character_speed = config.get_character_speed();
    if (character.get_x() - character_speed < 0){ //? le sumo 1
        character.set_x(0);
    } else {
        character.add_x(-character_speed);
    }*/
}

void Game::move_character_right() {
    character.set_right(); //Tiene que fijarse que no este en el aire
    /*
    int map_width = config.get_map_width();
    int character_speed = config.get_character_speed();
    int character_width = config.get_character_width();
    if (character.get_x() + character_width + character_speed > map_width){
        character.set_x(map_width - character_width);
    } else {
        character.add_x(character_speed);
    }*/
}

void Game::simulate() {
    collisionManager.move(character);

    for (int i = 0; i < vector.size(); i++){
        collisionManager.move(vector[i]);
    }
}

/*
void Game::run() {
    entityManager.
} */