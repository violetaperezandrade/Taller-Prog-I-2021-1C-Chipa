#include "Client.h"

Client::Client(char *ip, char *port, Logger& logger, Config& config) :
    skt(),
    logger(logger),
    entities(),
    ip(ip),
    port(port),
    config(config)
{}

Client::~Client(){
}

int Client::connect(char* ip, char* port){
    return skt.connect(ip, port,logger);
}

int Client::send(const char* msg, size_t len){
    return skt.send(msg, len,logger);
}

int Client::recv(char* msg, size_t len){
    return skt.receive(msg,len,logger);
}

void Client::run(){

    logger.infoMsg("Se inicia un cliente", __FILE__, __LINE__);

    SDLManager sdlMngr(logger);
    int playerNumber = 0;
    int playerAmount = config.getPlayersAmount();
    Login login(logger, sdlMngr, skt, playerNumber);
    logger.infoMsg("Soy el jugador numero " + std::to_string(playerNumber), __FILE__, __LINE__);
    int status = login.runLoginWindow(ip,port);
    if(status < 0){
        logger.errorMsg("Algo salio mal en ventana de login", __FILE__, __LINE__);
        return;
    }
    bool keepRunning = true;
    bool serverActive = true;
    bool play = true;
    int endGame = 0;

    Monitor monitor(logger);
    SoundManager soundManager(logger, play);
    View view(monitor,
              logger,
              config,
              sdlMngr,
              keepRunning,
              serverActive,
              playerNumber,
              soundManager,
              playerAmount,
              endGame);
    Input* input = new Input(skt, logger, keepRunning, serverActive, play);
    Processor* processor = new Processor(monitor,
                                         skt,
                                         logger,
                                         keepRunning,
                                         serverActive,
                                         playerAmount,
                                         endGame);

    logger.debugMsg("Se lanza thread INPUT", __FILE__, __LINE__);
    logger.debugMsg("Se lanza thread PROCESSOR", __FILE__, __LINE__);
    input->start();
    processor->start();

    view.run();

    processor->stop();
    input->stop();

    processor->join();
    input->join();

    delete input;
    delete processor;

}