#ifndef GAME_H
#define GAME_H

class Game {
private:
    Config config;

public:
    explicit Game(char** argv);
    Game();
    ~Game();

    void run();
};

#endif //GAME_H
