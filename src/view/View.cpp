#include "View.h"

SDL_Renderer* View::createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) std::cerr << "Error al crear renderer";
    else{
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    return renderer;
}

SDL_Window* View::createWindow(const char* title){
    SDL_Window* window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) std::cerr << "Error al crear ventana";
    return window;
}

SDL_Texture* View::loadImageTexture(std::string path, SDL_Renderer* renderer){

    SDL_Texture* finalTexture = NULL;
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(!imageSurface) printf("Error al cargar imagen %s. SDL_image error: %s\n",
                             path.c_str(), IMG_GetError());
    else{
        SDL_SetColorKey(imageSurface,SDL_TRUE,SDL_MapRGB(imageSurface->format,0,0,0));
        finalTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if(!finalTexture) printf("Error al cargar textura %s. SDL_Error: %s\n",
                                 path.c_str(),
                                 SDL_GetError());
        SDL_FreeSurface(imageSurface);
    }
    return finalTexture;
}

void View::render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer){
    SDL_Rect renderQuad = {x,y,width,height};
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(windowRenderer,texture,clip,&renderQuad,angle,center,flip);
}

void View::free(SDL_Texture* texture){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

int View::run(){

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error video";
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Error al filtrar textura lineal";
    }

    //Controller cont;

    SDL_Window* window = createWindow("Donkey Kong II");
    SDL_Renderer* windowRenderer = createRenderer(window);

    SDL_Texture* textureRight = loadImageTexture("/home/mauricio/Documents/Taller Azcurra/Taller-Prog-I-2021-1C-Chipa/src/view/img/Sprites Mario/mario_idle_right.bmp",windowRenderer);
    SDL_Texture* textureLeft = loadImageTexture("/home/mauricio/Documents/Taller Azcurra/Taller-Prog-I-2021-1C-Chipa/src/view/img/Sprites Mario/mario_idle_left.bmp",windowRenderer);

    //Render red filled quad
    SDL_Rect fillRect = { 0, 0, 800, 600 };
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );

    render(100,100,100,100,textureRight,windowRenderer);
    render(175,100,100,100,textureLeft,windowRenderer);
    SDL_RenderPresent(windowRenderer);
    SDL_Delay(3000);

    IMG_Quit();
    SDL_Quit();

    return 0;

}
