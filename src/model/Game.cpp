#include "Game.h"

#define DEFAULT_PATH "default_config.json"

Game::Game(char **argv) : config(argv){}

Game::Game() : config(DEFAULT_PATH) {}

Game::~Game() {}

void Game::run() {

}