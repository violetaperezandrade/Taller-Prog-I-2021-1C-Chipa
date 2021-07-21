#include "SDLManager.h"

SDLManager::SDLManager(Logger& logger) : logger(logger){

    if (initSDL() < 0){
        logger.errorMsg("Fallo initSDL", __FILE__, __LINE__);
    }
}

bool SDLManager::initSDL(){

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logger.errorMsg("Fallo inicializar video SDL", __FILE__, __LINE__);
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        logger.errorMsg("Error al filtrar textura lineal", __FILE__, __LINE__);
    }
    if(TTF_Init() == -1){
        logger.errorMsg("Error al inicializar TTF", __FILE__, __LINE__);
        error = true;
    }
    logger.debugMsg("SDL Iniciado correctamente para login", __FILE__, __LINE__);
    return error;
}

SDL_Window* SDLManager::createWindow(const char* title, int width, int height){

    SDL_Window* window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                           width,
                                           height,
                                           SDL_WINDOW_SHOWN);
    if(!window) {
        logger.errorMsg("Error al crear ventana de login con SDL", __FILE__, __LINE__);
    }
    logger.debugMsg("Ventana de login creada correctamente", __FILE__, __LINE__);
    return window;
}

SDL_Renderer* SDLManager::createRenderer(SDL_Window* window){

    SDL_Renderer* renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        logger.errorMsg("Error al crear renderer",__FILE__,__LINE__);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    logger.debugMsg("Renderer de login creado correctamente", __FILE__, __LINE__);
    return renderer;
}

TTF_Font* SDLManager::createFont(std::string path, int size){

    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if(font == NULL){
        logger.errorMsg("Error al cargar fuente", __FILE__, __LINE__);
    }
    logger.debugMsg("Fuente creada correctamente", __FILE__, __LINE__);
    return font;
}


SDL_Texture* SDLManager::loadImageTexture(std::string path, SDL_Renderer* renderer){

    SDL_Texture* finalTexture = NULL;
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(!imageSurface) {
        logger.errorMsg("Error al cargar superifice", __FILE__, __LINE__);
    }
    else{
        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 0, 0, 0));
        finalTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if(!finalTexture) {
            logger.errorMsg("Error al cargar textura", __FILE__, __LINE__);
        }
        SDL_FreeSurface(imageSurface);
    }
    logger.debugMsg("Textura creada correctamente", __FILE__, __LINE__);
    return finalTexture;
}

TextRendered SDLManager::loadFromRenderedText(std::string textureText,
                                              SDL_Color textColor,
                                              SDL_Renderer* renderer,
                                              TTF_Font* font){

    TextRendered text;
    SDL_Texture* finalTexture = NULL;
    int w,h;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if(textSurface != NULL){

        //crear textura desde superficie
        finalTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if(finalTexture == NULL){
            logger.errorMsg("Error al cargar textura desde texto",__FILE__,__LINE__);
        }
        else{
            w = textSurface->w;
            h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    text.texture = finalTexture;
    text.width = w;
    text.height = h;
    logger.debugMsg("Textura desde texto creada correctamente",__FILE__,__LINE__);
    return text;
}

void SDLManager::render(int x, int y, int width, int height, SDL_Texture* texture,
                        SDL_Renderer* renderer,SDL_Rect* clip){

    SDL_Rect renderQuad = {x, y, width, height};
    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

void SDLManager::renderWarnings(std::string message,SDL_Renderer* renderer, SDL_Window* window){

    SDL_SetWindowSize(window, 410, 110);
    TTF_Font* fontWarning = createFont("../src/client/fonts/Kongtext Regular.ttf", 15);
    TextRendered textureError = loadFromRenderedText(message.c_str(),
                                                     {255, 0, 0},
                                                     renderer,
                                                     fontWarning);
    SDL_Texture* warning = loadImageTexture("../src/client/img/Login/warning.png", renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    render((410-textureError.width)/2,
           10,
           textureError.width,
           textureError.height,
           textureError.texture,
           renderer);
    render(165, 30, 80, 80, warning,renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    destroyFont(fontWarning);
    destroyTexture(textureError.texture);
    destroyTexture(warning);
}

bool SDLManager::mouseWasClickedOnPosition(int x1, int x2, int y1, int y2, SDL_Event* e){

    bool ok = false;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if((x > x1 && x < x2) && (y > y1 && y < y2)){
            ok = true;
            logger.debugMsg("El mouse se posiciono sobre un textbox", __FILE__, __LINE__);
        }
    }
    return ok;
}

void SDLManager::renderFilledQuad(SDL_Renderer* renderer, int width, int height){

    SDL_Rect fillRect = { 0, 0, width, height};
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fillRect);
}

void SDLManager::destroyTexture(SDL_Texture* texture){

    SDL_DestroyTexture(texture);
}

void SDLManager::freeAllTextures(std::vector<SDL_Texture*>& vector){

    auto it = vector.begin();
    while (it != vector.end()) {
        destroyTexture(*it);
        ++it;
    }
    logger.debugMsg("Se liberan todas las texturas del login", __FILE__, __LINE__);
    vector.clear();
}

void SDLManager::destroyFont(TTF_Font* font){

    TTF_CloseFont(font);
}

void SDLManager::destroyRenderer(SDL_Renderer *renderer){

    SDL_DestroyRenderer(renderer);
}

void SDLManager::destroyWindow(SDL_Window *window){

    SDL_DestroyWindow(window);
}

void SDLManager::clearRender(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
}

void SDLManager::presentRender(SDL_Renderer *renderer){
    SDL_RenderPresent(renderer);
}

void SDLManager::startInputText(){
    SDL_StartTextInput();
}

void SDLManager::finishInputText(){
    SDL_StopTextInput();
}

bool SDLManager::closeSDL(){

    SDL_ClearError();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    logger.debugMsg("Cerrar SDL y destruccion objetos", __FILE__, __LINE__);
}

SDLManager::~SDLManager(){
    closeSDL();
}