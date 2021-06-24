#include "View.h"

View::View(Monitor& monitor,Logger& logger, Config& config, bool& keepRunning, bool& serverActive) :
    logger(logger),
    config(config),
    monitor(monitor),
    playerID(0),
    keepRuning(keepRunning),
    serverActive(serverActive)
{
    if (initSDL() < 0){
        logger.errorMsg("Fallo initSDL", __FILE__, __LINE__);
    }
    window = createWindow("Donkey Kong ii", config.getResolutionWidth(), config.getResolutionHeight());
    windowRenderer = createRenderer(window);

    //grey
    texturesMario[0]['d'] = loadImageTexture("../src/client/img/Sprites-Mario/mario_idle_back_off.png", windowRenderer);
    //red
    texturesMario[1]['1'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_right.png", windowRenderer);
    texturesMario[1]['2'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_left.png", windowRenderer);
    texturesMario[1]['6'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_right.png", windowRenderer);
    texturesMario[1]['7'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_left.png", windowRenderer);
    texturesMario[1]['8'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['9'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['r'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_right.png", windowRenderer);
    texturesMario[1]['l'] = loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_left.png", windowRenderer);


    //yellow
    texturesMario[2]['1'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_right.png", windowRenderer);
    texturesMario[2]['2'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_left.png", windowRenderer);
    texturesMario[2]['6'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_right.png", windowRenderer);
    texturesMario[2]['7'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_left.png", windowRenderer);
    texturesMario[2]['8'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['9'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['r'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_right.png", windowRenderer);
    texturesMario[2]['l'] = loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_left.png", windowRenderer);

    //lilac
    texturesMario[3]['1'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_right.png", windowRenderer);
    texturesMario[3]['2'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_left.png", windowRenderer);
    texturesMario[3]['6'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_right.png", windowRenderer);
    texturesMario[3]['7'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_left.png", windowRenderer);
    texturesMario[3]['8'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['9'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['r'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_right.png", windowRenderer);
    texturesMario[3]['l'] = loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_left.png", windowRenderer);

    //green
    texturesMario[4]['1'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_right.png", windowRenderer);
    texturesMario[4]['2'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_left.png", windowRenderer);
    texturesMario[4]['6'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_right.png", windowRenderer);
    texturesMario[4]['7'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_left.png", windowRenderer);
    texturesMario[4]['8'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['9'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['r'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_right.png", windowRenderer);
    texturesMario[4]['l'] = loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_left.png", windowRenderer);

    std::string fontPath = "../src/client/fonts/Kongtext Regular.ttf";
    font = TTF_OpenFont(fontPath.c_str(),10);

    SDL_Color colorP1 = {255, 0, 0};
    SDL_Color colorP2 = {255, 233, 0};
    SDL_Color colorP3 = {178, 0, 255};
    SDL_Color colorP4 = {0, 255, 0};
    //SDL_Color colorOff = {134,134,134};

    usersNames[1] = loadFromRenderedText("P1", colorP1, windowRenderer, font);
    usersNames[2] = loadFromRenderedText("P2", colorP2, windowRenderer, font);
    usersNames[3] = loadFromRenderedText("P3", colorP3, windowRenderer, font);
    usersNames[4] = loadFromRenderedText("P4", colorP4, windowRenderer, font);

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


bool View::initSDL() {

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logger.errorMsg("Fallo inicializar video SDL", __FILE__, __LINE__);
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        logger.errorMsg("Error al filtrar textura lineal", __FILE__, __LINE__);
    }
    if(TTF_Init() == -1){
        logger.errorMsg("Error al inicializar TTF",__FILE__,__LINE__);
        error = true;
    }
    return error;
}

SDL_Window* View::createWindow(const char* title,int width, int height){
    SDL_Window* window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(!window) {
        logger.errorMsg("Error al inicializar SDL_Window", __FILE__, __LINE__);
    }
    else{
        logger.infoMsg("SDL_Window Inicializado", __FILE__, __LINE__);
    }
    logger.debugMsg("Ventana creada",__FILE__,__LINE__);
    return window;
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
    }
    logger.debugMsg("SDL_Renderer Inicializado", __FILE__, __LINE__);
    return renderer;
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

TextRendered View::loadFromRenderedText(std::string textureText,
                                        SDL_Color textColor,
                                        SDL_Renderer* renderer, TTF_Font* font){
    TextRendered text;
    SDL_Texture* finalTexture = NULL;
    int w,h;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,textureText.c_str(),textColor);
    if(textSurface != NULL){

        //crear textura desde superficie
        finalTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(finalTexture == NULL) logger.errorMsg("Error al cargar textura des texto desde la vista",__FILE__,__LINE__);
        else{
            w = textSurface->w;
            h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    text.texture = finalTexture;
    text.width = w;
    text.height = h;
    logger.debugMsg("Textura desde texto creada correctamente", __FILE__, __LINE__);
    return text;
}

void View::render(int x, int y, int width, int height, char stateEntity,char entityType) {
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_Rect *clip = NULL;
    double angle = 0.0;
    SDL_Point *center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture *textureEntity;
    std::string c("Renderizar entidad de tipo: ");
    c.append(&entityType);
    logger.debugMsg(c, __FILE__, __LINE__);
    switch (entityType) {
        case 'C': //mario
            if(stateEntity == 'd'){
                textureEntity = texturesMario[0][stateEntity];
            }
            else {
                textureEntity = texturesMario[playerID][stateEntity];
            }
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

void View::renderFilledQuad(){
    SDL_Rect fillRect = { 0, 0, config.getResolutionWidth(), config.getResolutionHeight()};
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );
}

void View::renderText(int x, int y, int width, int height, SDL_Texture* texture){
    SDL_Rect renderQuad = {x,y,width,height};
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(windowRenderer, texture, clip, &renderQuad, angle, center, flip);

}

void View::renderWarning(std::string error){
    SDL_SetWindowSize(window, 410, 110);
    logger.errorMsg("Se cayo el servidor", __FILE__, __LINE__);
    TTF_Font* fontWarning = TTF_OpenFont("../src/client/fonts/Kongtext Regular.ttf", 15);
    TextRendered textureError = loadFromRenderedText(error.c_str(), {255, 0, 0}, windowRenderer, fontWarning);
    SDL_Texture* warning = loadImageTexture("../src/client/img/Login/warning.png", windowRenderer);
    SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(windowRenderer);
    renderText((config.getResolutionWidth()-textureError.width)/6, 10, textureError.width, textureError.height, textureError.texture);
    renderText(165, 30, 80, 80, warning);
    SDL_RenderPresent(windowRenderer);
    SDL_Delay(3000);
    TTF_CloseFont(fontWarning);
    fontWarning = NULL;
    free(textureError.texture);
    free(warning);
}

int View::run() {
    int playersAmount = config.getPlayersAmount();
    renderFilledQuad();
    int previousLevel = 1;
    TextRendered waitMessage = loadFromRenderedText("Waiting for the other players...",{255,0,0},windowRenderer,font);
    renderText((config.getResolutionWidth()-waitMessage.width)/2,(config.getResolutionHeight()-waitMessage.height)/4,waitMessage.width+20,waitMessage.height+20,waitMessage.texture);
    SDL_RenderPresent(windowRenderer);
    while(keepRuning && serverActive) {
        SDL_RenderClear(windowRenderer);
        std::vector<Entity> entityVector = monitor.getEntities();
        std::string len = std::to_string(entityVector.size());
        logger.debugMsg("Obtengo el vector de entities con longitud: " + len,__FILE__,__LINE__);
        std::vector<Entity>::iterator it = entityVector.begin();
        while (it != entityVector.end()) {
            if(monitor.getLevel() != previousLevel){
                logger.infoMsg("View setting level 2: " + len,__FILE__,__LINE__);
                changeLevel();
                previousLevel++;
            }
            int posX = it->getPosX();
            int posY = it->getPosY();
            int width = it->getWidth();
            int height = it->getHeight();
            char type = it->getType();
            char state = it->getState();

            if (type == 'C') {
                playerID++;
                if (playersAmount > 1){
                    renderText(posX+(width/3), posY-15, usersNames[playerID].width,usersNames[playerID].height, usersNames[playerID].texture);
                    logger.debugMsg("Renderizando player ID", __FILE__, __LINE__);
                }
            }
            logger.debugMsg("Renderizo una entidad",__FILE__,__LINE__);
            render(posX, posY, width, height, state, type);
            ++it;
        }
        playerID = 0;
        logger.debugMsg("Fin de iteracion sobre vector de entidades", __FILE__, __LINE__);
        SDL_RenderPresent(windowRenderer);
        SDL_RenderClear(windowRenderer);
    }
    if (!serverActive){
        logger.debugMsg("Inactive server", __FILE__, __LINE__);
        renderWarning("Server crashed unexpectedly");
    }
    return 0;
}

void View::closeSDL() {
    TTF_CloseFont(font);
    font = NULL;
    SDL_DestroyRenderer(windowRenderer);
    windowRenderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_ClearError();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    logger.infoMsg("Cerrar SDL", __FILE__, __LINE__);
}

View::~View(){
    closeSDL();
}