#include "View.h"
#include <iostream>

View::View(Game& game,Logger& logger, Config& config) : game(game),logger(logger), config(config){
    if (initSDL() < 0){
        logger.errorMsg("Fallo initSDL", __FILE__, __LINE__);
    }
    window = createWindow("Donkey Kong ii",config.getResolutionWidth(),config.getResolutionHeight());
    windowLogin = createWindow("Login game",SCREEN_WIDTH_LOGIN,SCREEN_HEIGHT_LOGIN);
    windowRenderer = createRenderer(window);
    windowRendererLogin = createRenderer(windowLogin);
    globalFont = createFont("../src/client/fonts/Kongtext Regular.ttf");

    texturesMario = {
                {'1', loadImageTexture("../src/view/img/Sprites-Mario/mario_jump_right.png", windowRenderer)},
                {'2', loadImageTexture("../src/view/img/Sprites-Mario/mario_jump_left.png", windowRenderer)},
                {'6', loadImageTexture("../src/view/img/Sprites-Mario/mario_walk_right.png", windowRenderer)},
                {'7', loadImageTexture("../src/view/img/Sprites-Mario/mario_walk_left.png", windowRenderer)},
                {'8', loadImageTexture("../src/view/img/Sprites-Mario/mario_climbing.png", windowRenderer)},
                {'9',loadImageTexture("../src/view/img/Sprites-Mario/mario_climbing.png", windowRenderer)},
                {'r',loadImageTexture("../src/view/img/Sprites-Mario/mario_idle_right.png", windowRenderer)},
                {'l',loadImageTexture("../src/view/img/Sprites-Mario/mario_idle_left.png", windowRenderer)}


    };
    texturesEntities = {{'P', loadImageTexture("../src/view/img/Sprites-Entities/blue_platform.png", windowRenderer)},
                        {'B',loadImageTexture("../src/view/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',loadImageTexture("../src/view/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',loadImageTexture("../src/view/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',loadImageTexture("../src/view/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',loadImageTexture("../src/view/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',loadImageTexture("../src/view/img/Sprites-Entities/yellow_stair.png", windowRenderer)},
                        {'E',loadImageTexture("../src/view/img/Sprites-Entities/flame.png", windowRenderer)}
    };

    texturesMonkey = {{'0',loadImageTexture("../src/view/img/Sprites-Monkey/monkey_left_hand_up.png", windowRenderer)}};

    defaultConfig = loadImageTexture("../src/view/img/default.png", windowRenderer);
}

TTF_Font* View::createFont(std::string path){

    TTF_Font* font = TTF_OpenFont(path.c_str(),FONTSIZE);
    if(font == NULL) logger.errorMsg("Error al cargar fuente",__FILE__,__LINE__);
    return font;
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
        finalTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if(finalTexture == NULL) logger.errorMsg("Error al cargar textura desde texto",__FILE__,__LINE__);
        else{
            w = textSurface->w;
            h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    text.texture = finalTexture;
    text.width = w;
    text.height = h;
    return text;
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
    if(TTF_Init() == -1){
        logger.errorMsg("Error al inicializar TTF",__FILE__,__LINE__);
        error = true;
    }
    return error;
}

void View::closeSDL() {

    TTF_CloseFont(globalFont);
    globalFont = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    logger.infoMsg("Cerrar SDL", __FILE__, __LINE__);
}

void View::changeLevel(){
    texturesEntities = {{'P', loadImageTexture("../src/view/img/Sprites-Entities/pink_platform.png", windowRenderer)},
                        {'B',loadImageTexture("../src/view/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',loadImageTexture("../src/view/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',loadImageTexture("../src/view/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',loadImageTexture("../src/view/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',loadImageTexture("../src/view/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',loadImageTexture("../src/view/img/Sprites-Entities/long_cyan_stair.png", windowRenderer)},
                        {'E',loadImageTexture("../src/view/img/Sprites-Entities/flame.png", windowRenderer)}
    };

}

SDL_Texture* View::loadImageTexture(std::string path, SDL_Renderer* renderer){

    SDL_Texture* finalTexture = NULL;
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(!imageSurface) {
        logger.errorMsg("Error al inicializar SDL_Surface utilizando el path: " + path, __FILE__, __LINE__);
        imageSurface = IMG_Load("../src/view/img/missing.png");
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
void View::refresh(){
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
    SDL_RenderPresent(windowRenderer);
    SDL_RenderClear(windowRenderer);
}
void View::renderFilledQuad(){
    SDL_Rect fillRect = { 0, 0, config.getResolutionWidth(), config.getResolutionHeight()};
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );
}

void View::renderLogin(int x, int y, int width, int height, SDL_Texture *texture, SDL_Renderer *windowRenderer) {

    SDL_Rect renderQuad = {x,y,width,height};
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(windowRendererLogin,texture,clip,&renderQuad,angle,center,flip);
}

int View::runLoginWindow() {

    std::string inputTextUser = "";
    std::string inputTextPsw = "";
    std::string playText = "PLAY!";

    SDL_Color textColorPrompt = {0xFF,0xFF,0xFF,0xFF};
    SDL_Color textColorInput = {0,0,0,0};
    SDL_Color textColorPlay = {204,255,0};

    TextRendered prompTextureUsr;
    TextRendered prompTexturePsw;
    TextRendered inputTextTextureUser;
    TextRendered inputTextTexturePsw;
    TextRendered playButtonText;

    inputTextTextureUser = loadFromRenderedText(inputTextUser.c_str(),textColorInput,windowRendererLogin,globalFont);
    inputTextTexturePsw = loadFromRenderedText(inputTextPsw.c_str(),textColorInput,windowRendererLogin,globalFont);
    prompTextureUsr = loadFromRenderedText("Username: ",textColorPrompt,windowRendererLogin,globalFont);
    prompTexturePsw = loadFromRenderedText("Password: ",textColorPrompt,windowRendererLogin,globalFont);
    playButtonText = loadFromRenderedText(playText.c_str(),textColorPlay,windowRendererLogin,globalFont);

    SDL_Texture* textbox = loadImageTexture("../src/client/img/textbox-blue.png",windowRendererLogin);
    SDL_Texture* playButton = loadImageTexture("../src/client/img/play.png",windowRendererLogin);
    SDL_Texture* monkey = loadImageTexture("../src/client/img/dk2.png",windowRendererLogin);

    SDL_StartTextInput();

    bool renderPass = false;

    bool quit = false;
    SDL_Event e;

    while(!quit){
        bool renderText = false;

        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN){

                if(e.key.keysym.sym == SDLK_TAB || e.key.keysym.sym == SDLK_RETURN){
                    renderPass = true;
                    continue;
                }
                if(e.key.keysym.sym == SDLK_BACKSPACE && (inputTextUser.length() > 0 || inputTextPsw.length() > 0)){
                    if(renderPass) inputTextPsw.pop_back();
                    else inputTextUser.pop_back();
                    renderText = true;
                }
                    //copy paste
                else if(e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL){
                    if(renderPass) SDL_SetClipboardText(inputTextPsw.c_str());
                    else SDL_SetClipboardText(inputTextUser.c_str());
                }
                else if(e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL){
                    if(renderPass) inputTextPsw = SDL_GetClipboardText();
                    else inputTextUser = SDL_GetClipboardText();
                    renderText = true;
                }
            }
            else if(e.type == SDL_TEXTINPUT){
                if(!(SDL_GetModState() & KMOD_CTRL && (tolower(e.text.text[0]) == 'c' || tolower(e.text.text[0]) == 'v'))){
                    if(renderPass) inputTextPsw += e.text.text;
                    else inputTextUser += e.text.text;
                    renderText = true;
                }
            }
        }

        if(renderText){
            if(renderPass){
                if(inputTextPsw != "") inputTextTexturePsw = loadFromRenderedText(inputTextPsw.c_str(),textColorInput,windowRendererLogin,globalFont);
                else inputTextTexturePsw = loadFromRenderedText("|",textColorInput,windowRendererLogin,globalFont);
            }
            else{
                if(inputTextUser != "") inputTextTextureUser = loadFromRenderedText(inputTextUser.c_str(),textColorInput,windowRendererLogin,globalFont);
                else inputTextTextureUser = loadFromRenderedText("|",textColorInput,windowRendererLogin,globalFont);
            }
        }

        SDL_SetRenderDrawColor(windowRendererLogin,0,0,0,0xFF);
        SDL_RenderClear(windowRendererLogin);

        renderLogin(300,150,300,50,textbox,windowRendererLogin);
        renderLogin(300,250,300,50,textbox,windowRendererLogin);

        renderLogin(300,120, prompTextureUsr.width,prompTextureUsr.height,prompTextureUsr.texture,windowRendererLogin);
        renderLogin(310,165,inputTextTextureUser.width,inputTextTextureUser.height,inputTextTextureUser.texture,windowRendererLogin);
        renderLogin(300,220,prompTexturePsw.width,prompTexturePsw.height,prompTexturePsw.texture,windowRendererLogin);
        renderLogin(310,265,inputTextTexturePsw.width,inputTextTexturePsw.height,inputTextTexturePsw.texture,windowRendererLogin);

        renderLogin(220,350,200,70,playButton,windowRendererLogin);
        renderLogin(253,359,playButtonText.width+50,playButtonText.height+30,playButtonText.texture,windowRendererLogin);

        renderLogin(50,140,200,200,monkey,windowRendererLogin);
        SDL_RenderPresent(windowRendererLogin);
    }
    SDL_StopTextInput();
    return 0;
}

View::~View(){
    closeSDL();
}



