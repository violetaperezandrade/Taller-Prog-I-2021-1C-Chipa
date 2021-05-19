#include "View.h"
#include <iostream>

View::View(Game& game,Logger& logger, Config& config) : game(game),logger(logger), config(config){

    texturesMario = {{'0', "../src/view/img/Sprites-Mario/mario_idle_back.png"},
                {'4', "../src/view/img/Sprites-Mario/mario_climbing.bmp"},
                {'r', "../src/view/img/Sprites-Mario/mario_ide_right.png"},
                {'l',"../src/view/img/Sprites-Mario/mario_idle_left.png"},
                {'7',"../src/view/img/Sprites-Mario/mario_walk_left.png"},
                {'6',"../src/view/img/Sprites-Mario/mario_walk_right.png"}

    };
    texturesEntities = {{'P', "../src/view/img/Sprites-Entities/platfotm_2.png"},
                        {'B',"../src/view/img/Sprites-Entities/Barrel.png"},
                        {'b',"../src/view/img/Sprites-Entities/oil_barrel.png"},
                        {'f',"../src/view/img/Sprites-Entities/flame.png"},
                        {'p',"../src/view/img/Sprites-Entities/princess.png"},
                        {'S',"../src/view/img/Sprites-Entities/long_cyan_stair.png"},
                        {'E',"../src/view/img/Sprites-Entities/ember.png"}};
    texturesMonkey = {{'0',"../src/view/img/Sprites-Monkey/monkey_left_hand_up.png"}};

    window = createWindow("Donkey Kong ii");
    windowRenderer = createRenderer(window);

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
    SDL_Window* window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
            textureEntity = loadImageTexture(texturesMario['0'], windowRenderer);
            break;
        case 'B': //barrel
            textureEntity = loadImageTexture(texturesEntities['B'], windowRenderer);
            break;
        case 'E': //ember
            textureEntity = loadImageTexture(texturesEntities['E'], windowRenderer);
            break;
        case 'F': //Fire
            textureEntity = loadImageTexture(texturesEntities['f'], windowRenderer);
            break;
        case 'f': //flame
            textureEntity = loadImageTexture(texturesEntities['f'], windowRenderer);
            break;
        case 'M': //monkey
            textureEntity = loadImageTexture(texturesMonkey['0'], windowRenderer);
            break;
        case 'P': //platform
            textureEntity = loadImageTexture(texturesEntities['P'], windowRenderer);
            break;
        case 'p': //princess
            textureEntity = loadImageTexture(texturesEntities['p'], windowRenderer);
            break;
        case 'S': //stair
            textureEntity = loadImageTexture(texturesEntities['S'], windowRenderer);
            break;
        default:
            break;
    }
    SDL_RenderCopyEx(windowRenderer, textureEntity, clip, &renderQuad, angle, center, flip);
    SDL_RenderPresent(windowRenderer);
}

void View::free(SDL_Texture* texture){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
void View::refresh(){
    //SDL_SetRenderDrawColor(windowRenderer,0,0,0,0xFF);
    //SDL_RenderClear(windowRenderer);
    //SDL_RenderPresent(windowRenderer);
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
        SDL_RenderPresent(windowRenderer);
    }
    SDL_RenderPresent(windowRenderer);
}
void View::renderFilledQuad(){
    SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );
}



