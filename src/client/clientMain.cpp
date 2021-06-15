#include "Client.h"
#include "../common/Logger.h"
#include "../common/Config.h"

int main(int argc, char** argv){
    char host[10] = "localhost";
    char port[5] = "8080";
    Logger logger(argv[2]);
    Config config(argv[0], logger);
    logger.setLevel(config.getDebug());
    Client client(host, port, logger, config);
    client.run();
    return 0;
}