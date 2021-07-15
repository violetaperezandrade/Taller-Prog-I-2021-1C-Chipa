#include "View.h"

View::View(Monitor& monitor, Logger& logger, Config& config, SDLManager& mngr, bool& keepRunning, bool& serverActive, int& playerNumber, SoundManager& soundManager) :
    logger(logger),
    config(config),
    sdlMngr(mngr),
    monitor(monitor),
    playerID(0),
    keepRuning(keepRunning),
    serverActive(serverActive),
    playerNumber(playerNumber),
    soundManager(soundManager){
    window = sdlMngr.createWindow("Donkey Kong ii", config.getResolutionWidth(), config.getResolutionHeight());
    windowRenderer = sdlMngr.createRenderer(window);

    //grey
    texturesMario[0]['d'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/mario_idle_back_off.png", windowRenderer);

    //red
    texturesMario[1]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_right.png", windowRenderer);
    texturesMario[1]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_left.png", windowRenderer);
    texturesMario[1]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_right.png", windowRenderer);
    texturesMario[1]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_left.png", windowRenderer);
    texturesMario[1]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_right.png", windowRenderer);
    texturesMario[1]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_left.png", windowRenderer);

    //yellow
    texturesMario[2]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_right.png", windowRenderer);
    texturesMario[2]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_left.png", windowRenderer);
    texturesMario[2]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_right.png", windowRenderer);
    texturesMario[2]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_left.png", windowRenderer);
    texturesMario[2]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_right.png", windowRenderer);
    texturesMario[2]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_left.png", windowRenderer);

    //lilac
    texturesMario[3]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_right.png", windowRenderer);
    texturesMario[3]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_left.png", windowRenderer);
    texturesMario[3]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_right.png", windowRenderer);
    texturesMario[3]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_left.png", windowRenderer);
    texturesMario[3]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_right.png", windowRenderer);
    texturesMario[3]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_left.png", windowRenderer);

    //green
    texturesMario[4]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_right.png", windowRenderer);
    texturesMario[4]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_left.png", windowRenderer);
    texturesMario[4]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_right.png", windowRenderer);
    texturesMario[4]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_left.png", windowRenderer);
    texturesMario[4]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_right.png", windowRenderer);
    texturesMario[4]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_left.png", windowRenderer);

    std::string fontPath = "../src/client/fonts/Kongtext Regular.ttf";
    font = sdlMngr.createFont(fontPath.c_str(), FONTSIZE_IDENTIFIERS);

    playersColor[1] = {255,0,0};
    playersColor[2] = {255,233,0};
    playersColor[3] = {178,0,255};
    playersColor[4] = {0,255,0};
    playersColor[5] = {255,255,255}; //white

    usersNames[1] = sdlMngr.loadFromRenderedText("P1", playersColor[1], windowRenderer, font);
    usersNames[2] = sdlMngr.loadFromRenderedText("P2", playersColor[2], windowRenderer, font);
    usersNames[3] = sdlMngr.loadFromRenderedText("P3", playersColor[3], windowRenderer, font);
    usersNames[4] = sdlMngr.loadFromRenderedText("P4", playersColor[4], windowRenderer, font);
    usersNames[5] = sdlMngr.loadFromRenderedText("Lives",playersColor[5],windowRenderer,font);
    usersNames[6] = sdlMngr.loadFromRenderedText("Points",playersColor[5],windowRenderer,font);

    texturesEntities = {{'P', sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/blue_platform.png", windowRenderer)},
                        {'B',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/yellow_stair.png", windowRenderer)},
                        {'E',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)}
    };

    texturesMonkey = {{'0',sdlMngr.loadImageTexture("../src/client/img/Sprites-Monkey/monkey_left_hand_up.png", windowRenderer)}};

    defaultConfig = sdlMngr.loadImageTexture("../src/client/img/default.png", windowRenderer);

    divisorPoints = sdlMngr.loadImageTexture("../src/client/img/divisor.png",windowRenderer);
}

void View::changeLevel(){
    texturesEntities = {{'P', sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/pink_platform.png", windowRenderer)},
                        {'B',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/long_cyan_stair.png", windowRenderer)},
                        {'E',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)}
    };

}


void View::getEntityInfoAndRender(int x, int y, int width, int height, char stateEntity, char entityType) {

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
    sdlMngr.render(x, y, width, height, textureEntity, windowRenderer);
}

void View::renderPlayerID(int posX, int width, int posY){
    if (config.getPlayersAmount() > 1){
        sdlMngr.render(posX+(width/3), posY-15, usersNames[playerID].width, usersNames[playerID].height, usersNames[playerID].texture, windowRenderer);
        logger.debugMsg("Renderizando player ID", __FILE__, __LINE__);
    }
}

void View::renderLivesAndPoints(){

    sdlMngr.render(0, 40, 800, 10, divisorPoints, windowRenderer);
    sdlMngr.render(1, 1, usersNames[5].width, usersNames[5].height, usersNames[5].texture, windowRenderer);
    sdlMngr.render(1,40-usersNames[6].height, usersNames[6].width, usersNames[6].height, usersNames[6].texture, windowRenderer);

    TextRendered textLives;
    TextRendered textPoints;
    SDL_Color white = {255,255,255};
    for (int i = 1; i <= playerID ; i++) {
        int posX = ((config.getResolutionWidth() / config.getPlayersAmount())/2) + (config.getResolutionWidth()*(i-1)/config.getPlayersAmount());
        int posY = 20-(usersNames[i].height/2);

        textLives = sdlMngr.loadFromRenderedText(std::to_string(lives[i-1]),white,windowRenderer,font);
        textPoints = sdlMngr.loadFromRenderedText(std::to_string(points[i-1]),white,windowRenderer,font);

        sdlMngr.render(posX,posY, usersNames[i].width, usersNames[i].height, usersNames[i].texture, windowRenderer);
        sdlMngr.render(posX + usersNames[i].width + 10, 1, textLives.width,textLives.height,textLives.texture,windowRenderer);
        sdlMngr.render(posX + usersNames[i].width + 10,40-textPoints.height, textPoints.width, textPoints.height,textPoints.texture,windowRenderer);
    }
}

void View::renderEntity(std::vector<Entity>::iterator it, std::vector<char>& states){
    int posX = it->getPosX();
    int posY = it->getPosY();
    int width = it->getWidth();
    int height = it->getHeight();
    char type = it->getType();
    char state = it->getState();

    if (type == 'C') {
        playerID++;
        renderPlayerID(posX, width, posY);
        states.push_back(state);

    }
    logger.debugMsg("Renderizo una entidad", __FILE__, __LINE__);
    //soundManager.playSoundFromState(state);
    getEntityInfoAndRender(posX, posY, width, height, state, type);
}

void View::renderResults(bool partial){
    TTF_Font* fontResults = sdlMngr.createFont("../src/client/fonts/Kongtext Regular.ttf",FONTSIZE_RESULTS);
    TextRendered result;
    if(partial){
        result = sdlMngr.loadFromRenderedText("Partial results",playersColor[5],windowRenderer,fontResults);
        TextRendered winner = sdlMngr.loadFromRenderedText("Winner!",playersColor[2],windowRenderer,fontResults);
    }
    else{
        result = sdlMngr.loadFromRenderedText("Final results",playersColor[5],windowRenderer,fontResults);
    }
    sdlMngr.clearRender(windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-result.width/2,10,result.width,
                   result.height,result.texture,windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-result.width/2, result.height + 10,
                   result.width, 10, divisorPoints, windowRenderer);

    TextRendered player;
    TextRendered pointsText;
    for(int i = 1; i <= playerNumber; i++){
        std::string playerId = "Player " + std::to_string(i) + ":";
        player = sdlMngr.loadFromRenderedText(playerId,playersColor[i],windowRenderer,fontResults);
        pointsText = sdlMngr.loadFromRenderedText(std::to_string(points[i-1]),playersColor[i],windowRenderer,fontResults);

        sdlMngr.render((config.getResolutionWidth()/2)-(player.width*2/3),
                       (150 + (i-1)*(player.height+40)),
                       player.width,player.height,player.texture,windowRenderer);
        sdlMngr.render((config.getResolutionWidth()/2)-(player.width*2/3) + player.width + 10,
                       (150),
                       pointsText.width,pointsText.height,
                       pointsText.texture,windowRenderer);
    }
    sdlMngr.presentRender(windowRenderer);
    if(partial) {
        SDL_Delay(6000);
        sdlMngr.clearRender(windowRenderer);
        sdlMngr.destroyFont(fontResults);
        sdlMngr.destroyTexture(result.texture);
        sdlMngr.destroyTexture(player.texture);
        sdlMngr.destroyTexture(pointsText.texture);
    }
}

int View::run() {
    sdlMngr.renderFilledQuad(windowRenderer, config.getResolutionWidth(), config.getResolutionHeight());
    int previousLevel = 1;
    std::vector<char> states;
    TextRendered waitMessage = sdlMngr.loadFromRenderedText("Waiting for the other players...", {255, 0, 0}, windowRenderer, font);
    sdlMngr.render((config.getResolutionWidth()-waitMessage.width)/2, (config.getResolutionHeight()-waitMessage.height)/4, waitMessage.width+20,waitMessage.height+20, waitMessage.texture, windowRenderer);
    sdlMngr.presentRender(windowRenderer);
    soundManager.playMusic("level 1", -1);
    while(keepRuning && serverActive) {
        if (monitor.getLevel() == 1) soundManager.runLevel1();
        else soundManager.runLevel2();
        sdlMngr.clearRender(windowRenderer);
        std::vector<Entity> entityVector;
        monitor.getInfo(entityVector, points, lives);
        std::string len = std::to_string(entityVector.size());
        logger.debugMsg("Obtengo el vector de entities con longitud: " + len, __FILE__, __LINE__);

        if(monitor.getLevel() != previousLevel){
            renderResults(true);
            changeLevel();
            logger.debugMsg("Se cambia de nivel desde la vista: ", __FILE__, __LINE__);
            previousLevel++;
            soundManager.playMusic("level 2", -1);
        }

        int pos = 0;
        int size = entityVector.size();
        int myCharacterPos = size - config.getPlayersAmount() + playerNumber -1;
        auto it = entityVector.begin();
        while (it != entityVector.end()) {
            if (pos != myCharacterPos){
                renderEntity(it, states);
            } else {
                playerID++;
            }
            renderLivesAndPoints();
            ++it;
            pos++;
        }
        playerID = playerNumber-1;
        renderEntity(entityVector.begin()+myCharacterPos, states);
        playerID = 0;
        logger.debugMsg("Fin de iteracion sobre vector de entidades", __FILE__, __LINE__);
        //soundManager.iterateStates(states);
        sdlMngr.presentRender(windowRenderer);
        sdlMngr.clearRender(windowRenderer);
    }
    if (!serverActive){
        logger.debugMsg("Inactive server", __FILE__, __LINE__);
        sdlMngr.renderWarnings("Server crashed unexpectedly", windowRenderer, window);
    }
    //renderResults(false);
    return 0;
}

View::~View(){
    sdlMngr.destroyFont(font);
    sdlMngr.destroyRenderer(windowRenderer);
    sdlMngr.destroyWindow(window);
}