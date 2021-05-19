#include "View.h"
#include <iostream>

View::View(Game& game,Logger& logger, Config& config) : game(game),logger(logger), config(config){
    if (initSDL() < 0){
        logger.errorMsg("Fallo initSDL");
    }
    window = createWindow("Donkey Kong ii");
    windowRenderer = createRenderer(window);

    texturesMario = {{'0', loadImageTexture("../src/view/img/Sprites-Mario/mario_idle_back.png", windowRenderer)},
                {'4', loadImageTexture("../src/view/img/Sprites-Mario/mario_climbing.bmp", windowRenderer)},
                {'r', loadImageTexture("../src/view/img/Sprites-Mario/mario_idle_right.png", windowRenderer)},
                {'l',loadImageTexture("../src/view/img/Sprites-Mario/mario_climbing.bmp", windowRenderer)},
                {'7',loadImageTexture("../src/view/img/Sprites-Mario/mario_walk_left.png", windowRenderer)},
                {'6',loadImageTexture("../src/view/img/Sprites-Mario/mario_walk_right.png", windowRenderer)}


    };
    texturesEntities = {{'P', loadImageTexture("../src/view/img/Sprites-Entities/blue_platform.png", windowRenderer)},
                        {'B',loadImageTexture("../src/view/img/Sprites-Entities/Barrel.png", windowRenderer)},
                        {'b',loadImageTexture("../src/view/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',loadImageTexture("../src/view/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',loadImageTexture("../src/view/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',loadImageTexture("../src/view/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',loadImageTexture("../src/view/img/Sprites-Entities/long_cyan_stair.png", windowRenderer)},
                        {'E',loadImageTexture("../src/view/img/Sprites-Entities/ember.png", windowRenderer)}
    };

    texturesMonkey = {{'0',loadImageTexture("../src/view/img/Sprites-Monkey/monkey_left_hand_up.png", windowRenderer)}};

}

SDL_Renderer* View::createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        std::string str("Error al inicializar SDL_Renderer");
        logger.errorMsg(str);
    }
    else{
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        std::string str("SDL_Renderer Inicializado");
        logger.infoMsg(str);
    }
    return renderer;
}

SDL_Window* View::createWindow(const char* title){
    SDL_Window* window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.getResolutionWidth(), config.getResolutionHeight(), SDL_WINDOW_SHOWN);
    if(!window) {
        std::string str("Error al inicializar SDL_Window");
        logger.errorMsg(str);
    }
    else{
        std::string str("SDL_Window Inicializado");
        logger.infoMsg(str);
    }
    return window;
}

bool View::initSDL() {

    bool error = false;
    int perro = SDL_Init(SDL_INIT_VIDEO);
    if (perro < 0) {
        logger.errorMsg("Fallo inicializar video SDL");
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        logger.errorMsg("Error al filtrar textura lineal");
    }
    return error;
}

void View::closeSDL() {
    IMG_Quit();
    SDL_Quit();
    logger.infoMsg("Cerrar SDL");
}

SDL_Texture* View::loadImageTexture(std::string path, SDL_Renderer* renderer){

    SDL_Texture* finalTexture = NULL;
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(!imageSurface) {
        std::string str("Error al inicializar SDL_Surface");
        logger.errorMsg(str);
    }
    else{
        SDL_SetColorKey(imageSurface,SDL_TRUE,SDL_MapRGB(imageSurface->format,0,0,0));
        finalTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if(!finalTexture) {
            std::string str("Error al inicializar SDL_Texture");
            logger.errorMsg(str);
        }
        SDL_FreeSurface(imageSurface);
    }
    return finalTexture;
}

void View::render(int x, int y, int width, int height, char stateEntity,char entityType) {
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_Rect *clip = NULL;
    double angle = 0.0;
    SDL_Point *center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture *textureEntity;
    switch (entityType) {
        case 'C': //mario
            textureEntity = texturesMario[stateEntity];
            break;
        case 'B': //barrel
            textureEntity = texturesEntities['B'];
            break;
        case 'E': //ember
            textureEntity = texturesEntities['E'];
            break;
        case 'F': //Fire
            textureEntity = texturesEntities['F'];
            break;
        case 'f': //flame
            textureEntity = texturesEntities['f'];
            break;
        case 'M': //monkey
            textureEntity = texturesMonkey['0'];
            break;
        case 'P': //platform
            textureEntity = texturesEntities['P'];
            break;
        case 'p': //princess
            textureEntity = texturesEntities['p'];
            break;
        case 'S': //stair
            textureEntity = texturesEntities['S'];
            break;
        default:
            break;
    }
    SDL_RenderCopyEx(windowRenderer, textureEntity, clip, &renderQuad, angle, center, flip);
}

void View::free(SDL_Texture* texture){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
void View::refresh(){
    Message entityInfo = game.getStatus();
    while(!entityInfo.isEmpty()){
        char entityType;
        int posX;
        int posY;
        int width;
        int height;
        char state;
        entityInfo.getEntityInfo(entityType,posX,posY,width,height,state);
        render(posX,posY,width,height,state,entityType);
    }
    SDL_RenderPresent(windowRenderer);
    SDL_RenderClear(windowRenderer);
}
void View::renderFilledQuad(){
    SDL_Rect fillRect = { 0, 0, config.getResolutionWidth(), config.getResolutionHeight()};
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );
}

View::~View(){
    closeSDL();
}



