#include "Game.h"

#define DEFAULT_PATH "default_config.json"

Game::Game(char **argv) : config(argv), entityManager(){}

Game::Game() : config(DEFAULT_PATH), entityManager() {}

Game::~Game() {}

void Game::run() {

}