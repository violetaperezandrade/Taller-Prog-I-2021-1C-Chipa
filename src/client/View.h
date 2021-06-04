#ifndef VIEW_H
#define VIEW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "../server/Game.h"
#include "../common/Logger.h"
#include "../server/Config.h"
#define FONTSIZE 24
#define SCREEN_WIDTH_LOGIN 640
#define SCREEN_HEIGHT_LOGIN 480

struct TextRendered{
    SDL_Texture* texture;
    int width;
    int height;
};

class View {
private:
    std::map<char, SDL_Texture*> texturesMario; //only mario
    std::map<char, SDL_Texture*> texturesEntities; //entities - mario - monkey
    std::map<char, SDL_Texture*> texturesMonkey; //only monkey
    SDL_Renderer* windowRenderer;
    SDL_Renderer* windowRendererLogin;
    SDL_Window* window;
    SDL_Window* windowLogin;
    TTF_Font* globalFont;
    Game& game;
    Logger& logger;
    Config& config;
    SDL_Texture* defaultConfig;

    bool initSDL();
    void closeSDL();
public:
    void renderLogin(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer);
    void render(int x, int y, int width, int height, char stateEntity,char entityType);

    SDL_Renderer* createRenderer(SDL_Window* window);

    SDL_Window* createWindow(const char* title,int width, int height);

    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);

    TTF_Font* createFont(std::string path);

    TextRendered loadFromRenderedText(std::string textureText,
                                      SDL_Color textColor,
                                      SDL_Renderer* renderer, TTF_Font* font);

    int runLoginWindow();

    void free(SDL_Texture* texture);
    //int run();
    View(Game& game, Logger& logger, Config& config);

    void changeLevel();

    ~View();

    void refresh();

    void renderFilledQuad();

};

#endif //VIEW_H
