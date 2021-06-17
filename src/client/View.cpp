#include "View.h"
#include <iostream>

View::View(Monitor& monitor,Logger& logger, Config& config) : logger(logger), config(config), monitor(monitor),keepRuning(true){
    if (initSDL() < 0){
        logger.errorMsg("Fallo initSDL", __FILE__, __LINE__);
    }
    window = createWindow("Donkey Kong ii", config.getResolutionWidth(), config.getResolutionHeight());
    windowRenderer = createRenderer(window);

    texturesMario = {
            {1, { //red
                        {'1', loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_right.png", windowRenderer)},
                        {'2', loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_left.png", windowRenderer)},
                        {'6', loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_right.png", windowRenderer)},
                        {'7', loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_left.png", windowRenderer)},
                        {'8', loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing.png", windowRenderer)},
                        {'9',loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing.png", windowRenderer)},
                        {'r',loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_right.png", windowRenderer)},
                        {'l',loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_left.png", windowRenderer)}
                }},
            {2, { //yellow
                    {'1', loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_right.png", windowRenderer)},
                    {'2', loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_left.png", windowRenderer)},
                    {'6', loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_right.png", windowRenderer)},
                    {'7', loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_left.png", windowRenderer)},
                    {'8', loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing.png", windowRenderer)},
                    {'9',loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing.png", windowRenderer)},
                    {'r',loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_right.png", windowRenderer)},
                    {'l',loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_left.png", windowRenderer)}
            }},
            {3, { //lilac
                        {'1', loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_right.png", windowRenderer)},
                        {'2', loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_left.png", windowRenderer)},
                        {'6', loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_right.png", windowRenderer)},
                        {'7', loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_left.png", windowRenderer)},
                        {'8', loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing.png", windowRenderer)},
                        {'9',loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing.png", windowRenderer)},
                        {'r',loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_right.png", windowRenderer)},
                        {'l',loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_left.png", windowRenderer)}
                }},
            {4, {//green
                        {'1', loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_right.png", windowRenderer)},
                        {'2', loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_left.png", windowRenderer)},
                        {'6', loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_right.png", windowRenderer)},
                        {'7', loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_left.png", windowRenderer)},
                        {'8', loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing.png", windowRenderer)},
                        {'9',loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing.png", windowRenderer)},
                        {'r',loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_right.png", windowRenderer)},
                        {'l',loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_left.png", windowRenderer)}
                }}
    };

    texturesEntities = {{'P', loadImageTexture("../src/client/img/Sprites-Entities/blue_platform.png", windowRenderer)},
                        {'B',loadImageTexture("../src/client/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',loadImageTexture("../src/client/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',loadImageTexture("../src/client/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',loadImageTexture("../src/client/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',loadImageTexture("../src/client/img/Sprites-Entities/yellow_stair.png", windowRenderer)},
                        {'E',loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)}
    };

    texturesMonkey = {{'0',loadImageTexture("../src/client/img/Sprites-Monkey/monkey_left_hand_up.png", windowRenderer)}};

    defaultConfig = loadImageTexture("../src/client/img/default.png", windowRenderer);
}

SDL_Renderer* View::createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        logger.errorMsg("Error al inicializar SDL_Renderer", __FILE__, __LINE__);
    }
    else{
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        logger.infoMsg("SDL_Renderer Inicializado", __FILE__, __LINE__);
    }
    return renderer;
}

SDL_Window* View::createWindow(const char* title,int width, int height){
    SDL_Window* window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(!window) {
        logger.errorMsg("Error al inicializar SDL_Window", __FILE__, __LINE__);
    }
    else{
        logger.infoMsg("SDL_Window Inicializado", __FILE__, __LINE__);
    }
    return window;
}

bool View::initSDL() {

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logger.errorMsg("Fallo inicializar video SDL", __FILE__, __LINE__);
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        logger.errorMsg("Error al filtrar textura lineal", __FILE__, __LINE__);
    }
    return error;
}

void View::closeSDL() {

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    logger.infoMsg("Cerrar SDL", __FILE__, __LINE__);
}

void View::changeLevel(){
    texturesEntities = {{'P', loadImageTexture("../src/client/img/Sprites-Entities/pink_platform.png", windowRenderer)},
                        {'B',loadImageTexture("../src/client/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',loadImageTexture("../src/client/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',loadImageTexture("../src/client/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',loadImageTexture("../src/client/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',loadImageTexture("../src/client/img/Sprites-Entities/long_cyan_stair.png", windowRenderer)},
                        {'E',loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)}
    };

}

SDL_Texture* View::loadImageTexture(std::string path, SDL_Renderer* renderer){

    SDL_Texture* finalTexture = NULL;
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(!imageSurface) {
        logger.errorMsg("Error al inicializar SDL_Surface utilizando el path: " + path, __FILE__, __LINE__);
        imageSurface = IMG_Load("../src/client/img/missing.png");
    }
    if(!imageSurface) {
        logger.errorMsg("Error al inicializar missing.png", __FILE__, __LINE__);
    }
    else{
        SDL_SetColorKey(imageSurface,SDL_TRUE,SDL_MapRGB(imageSurface->format,0,0,0));
        finalTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if(!finalTexture) {
            logger.errorMsg("Error al inicializar SDL_Texture", __FILE__, __LINE__);
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
            textureEntity = texturesMario[playerID][stateEntity];
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
        case 'd'://default water mark
            textureEntity = defaultConfig;
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
/*void View::refresh(){
    if(config.getDefault()){
        render(0,200,800,200,'\0','d');
    }
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
    std::vector<Entity> entityVector = monitor.getEntityVector();
    std::vector<Entity>::iterator it = entityVector.begin();
    while(it != entityVector.end()) {
        char type = it->getType();
        int posX = it->getPosX();
        int posY = it->getPosY();
        int width = it->getWidth();
        int height = it->getHeight();
        char state = it->getState();
        render(posX, posY, width, height, state, type);
    }
    SDL_RenderPresent(windowRenderer);
    SDL_RenderClear(windowRenderer);
}*/
void View::renderFilledQuad(){
    SDL_Rect fillRect = { 0, 0, config.getResolutionWidth(), config.getResolutionHeight()};
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );
}

int View::run() {
    renderFilledQuad();
    while(keepRuning) {
        std::vector<Entity> entityVector = monitor.getEntities();
        std::vector<Entity>::iterator it = entityVector.begin();
        while (it != entityVector.end()) {
            char type = it->getType();
            if (type == 'c') {
                playerID++;
            }
            int posX = it->getPosX();
            int posY = it->getPosY();
            int width = it->getWidth();
            int height = it->getHeight();
            char state = it->getState();
            render(posX, posY, width, height, state, type);
        }
        SDL_RenderPresent(windowRenderer);
        SDL_RenderClear(windowRenderer);
    }
    return 0;
}

View::~View(){
    closeSDL();
}



