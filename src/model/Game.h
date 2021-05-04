#ifndef GAME_H
#define GAME_H

#include "vector"
#include "Entity.h"
#include "Character.h"
#include "CollisionManager.h"

class Game {
private:
    Config& config;
    Character character;
    std::vector<Entity> vector;
    CollisionManager collisionManager;

public:
    explicit Game(char** argv);
    Game();
    ~Game();
    void move_character_left();
    void move_character_right();
    void make_character_jump();
    void update();

    //void run();
};

#endif //GAME_H
